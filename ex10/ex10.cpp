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

static int digit_sum(int input) {
	int rlt = 0;
	int calc = 0;
	int n = input;
	while (n > 0) {
		calc = n % 10; // input 값의 마지막 자릿수 구함
		rlt += calc; // 자릿수 값을 더해줌
		n = n / 10; // 자릿수 하나씩 밀어줌
		if (n < 10) { // 마지막 한 자릿수가 되면 그 값을 결과값에 더해줌
			rlt += n;
			break;
		}
	}
	return rlt;
}

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

	int num = 0, input = 0;
	int sum = 0;
	int max = 0, rlt = 0;
	inputFile >> num;

	for (int i = 0; i < num; i++) {
		inputFile >> input;
		sum = digit_sum(input);
		if ( sum > max ) {
			rlt = input;
			max = sum;
		}
		else if ( sum == max && rlt < input ) {
			rlt = input;
		}
	}

	int answer = 0;
	answerFile >> answer;
	if ( rlt == answer ) {
		cout << "result : " << rlt << " answer : " << answer << " correct" << endl;
	}
	else {
		cout << "result : " << rlt << " answer : " << answer << " incorrect" << endl;
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