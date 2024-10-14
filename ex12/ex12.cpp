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

	int input;
	int sum = 0, cnt = 1, d = 9, res = 0;

	inputFile >> input;

	while (sum + d < input) {
		res = res + (cnt * d); // 자릿수 * 9의 10배수
		sum = sum + d; // 0 ~ 9 , 9 ~ 99 , 100 ~ 999 로 계속해서 누적
		cnt++; // 자릿수 증가
		d = d * 10;
	}

	res = res + ((input - sum) * cnt);

	int answer;
	answerFile >> answer;

	if (res == answer) {
		cout << "result : " << res << " answer : " << answer << " correct" << endl;
	}
	else {
		cout << "result : " << res << " answer : " << answer << " incorrect" << endl;
	}

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