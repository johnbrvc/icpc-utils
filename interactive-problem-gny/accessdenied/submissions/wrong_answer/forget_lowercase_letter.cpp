#include <bits/stdc++.h>
using namespace std;

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz0123456789";

int query(string s) {
	cout << s << endl;
	cin >> s >> s;
	if (s == "GRANTED") exit(0);
	char c; cin >> c;
	int t; cin >> t;
	cin >> s;
	return t;
}

int main() {
	for (int len = 1; len <= 20; len++) {
		string s(len, 'A');
		if (query(s) == 5) continue;
		
		for (int i = 0; i < len; i++) {
			int tmax = 0;
			char best = '?';
			for (char c: alphabet) {
				s[i] = c;
				int tcur = query(s);
				if (tcur > tmax) tmax = tcur, best = c;
			}
			s[i] = best;
		}
	}
}
