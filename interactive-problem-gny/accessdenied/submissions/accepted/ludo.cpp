#include<iostream>
#include<string>
using namespace std;

int interact(const string &s) {
	(cout << s << endl).flush();
	string line;
	getline(cin, line);
	if (line == "ACCESS GRANTED")
		exit(0);
	int num = 0;
	for (int i = 15; '0' <= line[i] && line[i] <= '9'; i++)
		num = 10*num + (line[i] - '0');
	return num;
}

int main() {
	int len = 1;
	while (len < 20 && interact(string(len, 'A')) == 5)
		len++;
	string res(len, 'A');
	for (int pos = 0; pos < len; pos++) {
		for (char ch : "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") {
			res[pos] = ch;
			if (interact(res) > 14 + 9*pos)
				break;
		}
	}
	return 0;
}
