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

int calc(const string& inputFileName, const string& answerFileName) {
	ifstream inputFile(inputFileName);
	ifstream answerFile(answerFileName);

	char input[100];

	inputFile >> input;

	int cnt[10];
	memset(cnt, 0, sizeof(cnt));
	int num = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		num = input[i] - '0';
		if (num >= 0 || num <= 9) {
			cnt[num]++;
		}
	}

	int rlt = 0;
	int result = 0;
	for (int i = 0; i < 10; i++) {
		if (rlt <= cnt[i]) {
			rlt = cnt[i];
			result = i;
		}
	}
	
	string answer;
	answerFile >> answer;

	cout << "Result : " << result << endl;
	cout << "Answer : " << answer << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	fs::path directory = "./input";

	vector<string> inputfiles;
	vector<string> answerfiles;

	try {
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (entry.is_regular_file()) {
				string name = entry.path().filename().string();
				if (name.find("in") == 0 && name.length() > 4 && name.substr(name.length() - 4) == ".txt") {
					inputfiles.push_back(entry.path().string());
				}
				if (name.find("out") == 0 && name.length() > 4 && name.substr(name.length() - 4) == ".txt") {
					answerfiles.push_back(entry.path().string());
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
	sort(answerfiles.begin(), answerfiles.end());

	for (int i = 0; i < inputfiles.size(); i++) {
		calc(inputfiles.at(i), answerfiles.at(i));
	}

	return 0;
}