/*
 * 知识点：兄弟字符串分组
 * 编译命令：gcc group.cpp -o group.o -std=c++11 -lstdc++
 *
 */ 

#include<vector>
#include<iostream>
#include<string>
#include<map>

#include <algorithm>

using namespace std;

vector<vector<string> > group(const vector<string> &vect) {
	vector<vector<string> > result;
        map<string, vector<string> > m;

	int size = vect.size();
	for(int i = 0; i < size; ++i) {
		string s = vect[i];
		sort(s.begin(), s.end());
		if(m.count(s) == 0) {
			vector<string> v;
 			v.push_back(vect[i]);
			m[s] = v;
			
		}
		else {
			m[s].push_back(vect[i]);
		}
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
	group(vect);
	return 0;
}

