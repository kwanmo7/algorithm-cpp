#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

namespace fs = std::filesystem;
using namespace std;

int getAge(int& birth, char& flag) {
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	// 2024년 기준 --> t.tm_year = 124
	if (flag == '1' || flag == '2') {
		return (t.tm_year + 1900) - (1900 + birth);
	}
	if (flag == '3' || flag == '4') {
		return (t.tm_year + 1900) - (2000 + birth);
	}
}

int calc(const string& inputfilename, const string& outputfilename) {

	ifstream cin(inputfilename);
	ifstream cin2(outputfilename);
	if (!cin) {
		cerr << "Error open file : " << inputfilename << endl;
		return 0;
	}
	if (!cin2) {
		cerr << "Error open file : " << outputfilename << endl;
		return 0;
	}

	char regNum[15];
	cin.getline(regNum, 15);
	
	int birth = (regNum[0] - 48) * 10 + (regNum[1] - 48);
	string gender;

	if (regNum[7] == '1' || regNum[7] == '3') {
		gender = "M";
	}
	if (regNum[7] == '2' || regNum[7] == '4') {
		gender = "F";
	}
	int age = getAge(birth, regNum[7]);


	int ansAge = 0;
	string ansGender;

	cin2 >> ansAge;
	cin2 >> ansGender;


	if (ansAge == age && ansGender.compare(gender) == 0) {
		cout << "Age : " << age << " gender : " << gender << endl;
		cout << "ansAge : " << ansAge << " ansGender : " << ansGender << endl;
		cout << "correct" << endl;
	}
	else {
		cout << "Age : " << age << " gender : " << gender << endl;
		cout << "ansAge : " << ansAge << " ansGender : " << ansGender << endl;
		cout << "intcorrect" << endl;
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);

	fs::path directory = "./input";
	vector<string> inputfiles;
	vector<string> outputfiles;

	try {
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (entry.is_regular_file()) {
				string name = entry.path().filename().string();
				if (name.find("in") == 0 && name.length() > 4 && name.substr(name.length() - 4) == ".txt") {
					inputfiles.push_back(entry.path().string());
				}
				if (name.find("out") == 0 && name.length() > 4 && name.substr(name.length() - 4) == ".txt") {
					outputfiles.push_back(entry.path().string());
				}
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Filesystem error : " << e.what() << endl;
		return 1;
	}

	if (inputfiles.empty()) {
		cout << "No input files" << endl;
		return 0;
	}

	sort(inputfiles.begin(), inputfiles.end());
	sort(outputfiles.begin(), outputfiles.end());

	for (int i = 0; i < inputfiles.size(); i++) {
		calc(inputfiles.at(i), outputfiles.at(i));
	}

	return 0;
}