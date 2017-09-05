#include "KNN_Classifier.h"



KNN_Classifier::KNN_Classifier()
{
}


KNN_Classifier::~KNN_Classifier()
{
}
//FINDS THE EUCLEADIAN DISTANCE OF TWO VECTORS
float KNN_Classifier::distance(vector<float> feat1, vector<float> feat2) {
	float sum = 0;
	for (vector<float>::iterator it1 = feat1.begin(), it2 = feat2.begin(); it1 != feat1.end(); it1++, it2++) {
		float var = *it1 - *it2;
		var *= var;
		sum += var;
	}
	return sqrt(sum);
}
//find nearest neighs
vector<int> KNN_Classifier::get_k_neighbors(int k, vector<vector<float>> train, vector<float> test_row) {
	vector<float> k_min(k,9999999);
	vector<int> k_min_index(k);
	float dist;
	for (int i = 0; i < 2000; i++) { //find the min distance and save the index of training data
		dist = distance(train[i], test_row);
		for (int j = 0; j < k; j++) {
			if (k_min[j] > dist) {
				k_min[j] = dist;
				k_min_index[j] = i;
				break;
			}
		}
	}
	return k_min_index;
}

float KNN_Classifier::KNN_classifier(int k, vector<vector<float>> test, vector<vector<float>> train) {
	int errors = 0;
	for (int row = 0; row < test.size(); row++) {
		vector<int> neighs = get_k_neighbors(k, train, test[row]); //indeces of training data
		map<float,int> labels;

		//find label from indicies
		for (vector<int>::iterator n_it = neighs.begin(); n_it != neighs.end(); n_it++) {
			float label = train[*n_it][785];
			if (labels.count(label) == 0)
				labels[label] = 1;
			else
				labels[label] += 1;
		}
		//find label with most counts
		int max = 0;
		float maxLabel;
		for (map<float, int>::iterator it = labels.begin(); it != labels.end(); it++) {
			if (it->second > max) {
				max = it->second;
				maxLabel = it->first;
			}
		}
		if (maxLabel != test[row][785]);
			errors += 1;
	}
	return errors = errors / test.size();
}