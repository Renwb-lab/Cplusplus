/*
 * 知识点：兄弟字符串分组
 * 编译命令：gcc group2.cpp -o group2.o -std=c++11 -lstdc++
 *
 */ 

#include<vector>

#include<vector>
#include<iostream>
#include<string>
#include<map>

using namespace std;

const int length = 256;
int global_arr[length];

string itos(int num) {
	string s;
	while (num) {
		int m = num % 10;
		char c = '0' + m;
		s += c;
		num /= 10; 
	}
	return s;
}

string transform(const string &s) {
	memset(global_arr, 0, length);
	for(unsigned int i = 0; i < s.size(); ++i) {
		++global_arr[s[i]];
	}

	string result;
	for(int i = 0; i < length; ++i) {
		if(global_arr[i] != 0) 	{
			result += (char)i + itos(global_arr[i]);
		}
	}
	return result;	
}

vector<vector<string> > group(const vector<string> &words) {
	vector<vector<string> > result;
        map<string, vector<string> > m;
	
	unsigned int size = words.size();
	for(unsigned int i = 0; i < size; ++i) {
		string s = transform(words[i]);
		m[s].push_back(words[i]);
	}

	map<string, vector<string> >::iterator iter;
	for(iter = m.begin(); iter != m.end(); ++iter) {
		result.push_back(iter->second);
	}

	for(int i = 0; i < result.size(); ++i) {
		for(int j = 0; j < result[i].size(); ++j) {
			cout << result[i][j] << " ";
		}
		cout << "\n";
	}
	return result;
}

int main() {
	vector<string> vect;
	vect.push_back("123");
	vect.push_back("213");
	vect.push_back("312");

	vect.push_back("23");
	vect.push_back("32");
	vect.push_back("322");
	group(vect);
	return 0;
}

