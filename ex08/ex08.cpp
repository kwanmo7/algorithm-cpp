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

static int calc(const string& inputfilename, const string& answerfilename) {

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

	string input;
	getline(inputFile, input);

	string strYes = "YES";
	string strNo = "NO";

	string answer;
	answer.clear();
	getline(answerFile, answer);

	int cnt = 0, i = 0;

	for (i = 0; i < input.size(); i++) {
		if (input.at(0) == ')') {
			break;
		}

		if ( i == input.size() -1 && cnt < 0 ) {
			break;
		}

		if (input.at(i) == '(') {
			cnt++;
		}
		else {
			cnt--;
		}
	}

	if ( cnt == 0 && i != 0) {
		cout << "result : " << strYes << " answer : " << answer << endl;
	}
	else {
		cout << "result : " << strNo << " answer : " << answer << endl;

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