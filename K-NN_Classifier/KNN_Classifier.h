#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
class KNN_Classifier
{
public:
	KNN_Classifier();
	~KNN_Classifier();
	vector<int> get_k_neighbors(int k, vector<vector<float>> train, vector<float> test_row);
	float KNN_classifier(int k, vector<vector<float>> test, vector<vector<float>> train);
	float distance(vector<float> feat1, vector<float> feat2);
};

int main() {
	ifstream trainf("hw2train.txt"); //785 x 2000
	ifstream testf("hw2test.txt");   // 785 x 1000
	ifstream validatef("hw2validate.txt");  // 785 x 1000

	vector<vector<float>> train(2000,vector<float>(785)), test(1000, vector<float>(785)), validate(1000, vector<float>(785));
	string line_test, line_validate, line;
	for(int i = 0; i < 1000; i++) {
		getline(testf, line_test);		//getsline before \n
		getline(validatef, line_validate);

		istringstream s_val(line_validate);
		istringstream s_test(line_test); // makes string a input stream

		float test_feat, val_feat;
		for (int j = 0; j < 785; j++) { //get feature vector of size 784 + 1 for label
			s_test >> test_feat;
			s_val >> val_feat;
			test[i].push_back(test_feat);
			validate[i].push_back(val_feat);
		}
	}
	for (int i = 0; i < 2000; i++) {
		getline(trainf, line);
		istringstream stream(line);
		float feat;
		for (int j = 0; j < 785; j++) {
			stream >> feat;
			train[i].push_back(feat);
		}
	}
	KNN_Classifier c;
	cout << c.KNN_classifier(3, train, train) << endl;
	cout << c.KNN_classifier(4, train, train) << endl;
	cout << c.KNN_classifier(5, train, train) << endl;
};

