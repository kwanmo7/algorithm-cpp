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

int reverse(int x) {
	int num = x;
	int result = 0;
	while (num > 0) {
		result = (result * 10) + (num % 10);
		num = num / 10;
	}
	return result;
}
bool isPrime(int x) {
	if ( x == 1) {
		return false;
	}
	for (int i = 2; i < x; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}
int calc(const string& inputFileName, const string& answerFileName) {
	ifstream inputFile(inputFileName);
	ifstream answerFile(answerFileName);
	
	int n;
	inputFile >> n;
	int num;
	int result = 0;
	bool chk = false;
	cout << "Result : ";
	for (int i = 0; i < n; i++) {
		inputFile >> num;
		result = reverse(num);
		chk = isPrime(result);
		if (chk == true) {
			cout << result << " ";
		}
	}
	cout << endl;

	string answer;
	getline(answerFile, answer);
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