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

	int n= 0;
	int sum = 1;

	string answer;
	cin >> n;
	getline(cin2, answer);

	string ans = "1";

	cout << "Input : " << n << endl;

	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			sum += i;
			ans.append(" + " + to_string(i));
		}
	}

	ans.append(" = " + to_string(sum));

	if (ans.compare(answer) == 0) {
		cout << "ans : " << ans << endl;
		cout << "answer : " << answer << endl;
		cout << "correct" << endl;
	}
	else {
		cout << "ans : " << ans << endl;
		cout << "answer : " << answer << endl;
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