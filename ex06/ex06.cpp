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

static int calc(const string& inputfilename, const string& outputfilename) {

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

	char input[100];
	cin.getline(input, 100);
	
	int i = 0, rlt = 0, cnt = 0;
	while (input[i] != '\0') {
		if (input[i] >= 48 && input[i] <= 57) {
			rlt = rlt * 10 + (input[i] - 48);
		}
		i++;
	}
	
	for (i = 1; i <= rlt; i++) {
		if ( rlt % i == 0) {
			cnt++;
		}
	}
	
	int ansRlt, ansCnt;
	cin2 >> ansRlt;
	cin2 >> ansCnt;

	if ( rlt == ansRlt && cnt == ansCnt ) {
		cout << "rlt : " << rlt << " cnt : " << cnt << endl;
		cout << "ansRlt : " << ansRlt << " ansCnt : " << ansCnt << endl;
		cout << "correct" << endl;
	}
	else {
		cout << "rlt : " << rlt << " cnt : " << cnt << endl;
		cout << "ansRlt : " << ansRlt << " ansCnt : " << ansCnt << endl;
		cout << "incorrect" << endl;
	}

	cin.close();
	cin2.close();

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