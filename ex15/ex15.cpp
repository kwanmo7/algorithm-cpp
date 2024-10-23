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

	int n, flag, cnt = 0;
	inputFile >> n;
	
	for (int i = 2; i <= n; i++) {
		flag = 1;
		// ex) 36 인경우 1 x 36 / 2 x 18 / 3 * 12 / 4 * 9 / 6 * 6 으로 소수가 아님을 알 수 있다. 
		// 확인하려는 숫자의 제곱근으로 확인하면 빠르게 확인할 수 있다.
		for (int j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			cnt++;
		}
	}

	int answer;
	answerFile >> answer;

	cout << "Result : " << answer << endl;
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