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

int calc(const string& inputfilename, const string& answerfilename) {

	ifstream inputFile(inputfilename);
	ifstream answerFile(answerfilename);

	if (!inputFile) {
		cerr << "Error open file : " << inputfilename << endl;
		return 0;
	}
	if (!answerFile) {
		cerr << "Error open file : " << answerfilename << endl;
		return 0;
	}

	int n;
	int temp, cnt = 0;
	inputFile >> n;

	for (int i = 1; i <= n; i++) {
		temp = i;
		while (temp > 0) {
			temp = temp / 10;
			cnt++;
		}
	}

	int answer;
	answerFile >> answer;
	if (cnt == answer) {
		cout << "result : " << cnt << " answer : " << answer << " correct" << endl;
	}
	else {
		cout << "result : " << cnt << " answer : " << answer << " incorrect" << endl;
	}

	inputFile.close();
	answerFile.close();

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