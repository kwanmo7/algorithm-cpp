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

int cnt[50001];

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

	int input = 0;
	inputFile >> input;
	
	cout << "input : " << input << endl;
	memset(cnt , 0 , sizeof(cnt)); // 배열 초기화

	// input까지의 수에 대한 약수 갯수 구하기
	for (int i = 1; i <= input; i++) {
		for (int j = i; j <= input; j=j+i) {
			cnt[j]++;
		}
	}
	
	string result;
	result.clear();
	string answer;
	getline(answerFile, answer);

	// getline으로 답을 받아올 때 너무 길어지면 줄바꿈이 포함되므로 삭제 시켜줌.
	answer.erase(answer.find_last_not_of(" \n\r\t")+1);
	
	// 답 체크를 위한 string 변환
	for (int i = 1; i <= input; i++) {
		if ( i == input ) {
			result += to_string(cnt[i]);
			break;
		}
		result += to_string(cnt[i]) + " ";
	}

	cout << "result : " << result << endl;
	cout << "answer : " << answer << endl;

	if (result.compare(answer) == 0) {
		cout << "correct" << endl;
	}
	else {
		cout << "incorrect" << endl;
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