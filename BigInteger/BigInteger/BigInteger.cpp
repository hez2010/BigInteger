#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;

struct BigInteger {
	static const int BASE = 10;
	static const int WIDTH = 1;
	vector<int> s;
	int max(int a, int b) {
		return a > b ? a : b;
	}
	int min(int a, int b) {
		return a < b ? a : b;
	}
	BigInteger(long long num = 0) { *this = num; }
	BigInteger operator = (long long num) {
		s.clear();
		do {
			s.push_back(num%BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	BigInteger operator = (const string& str) {
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;
		for (int i = 0;i < len;i++) {
			int end = str.length() - i*WIDTH;
			int start = max(0, end - WIDTH);
			sscanf_s(str.substr(start, end - start).c_str(), "%d", &x); //Dev C++ «Î”√£∫sscanf(str.substr(start, end - start).c_str(), "%d", &x);
			s.push_back(x);
		}
		return *this;
	}
	bool operator < (const BigInteger& b) const {
		if (s.size() != b.s.size()) return s.size() < b.s.size();
		for (int i = s.size() - 1;i >= 0;i--) {
			if (s[i] != b.s[i]) return s[i] < b.s[i];
		}
		return false;
	}
	bool operator > (const BigInteger& b) const { return b < *this; }
	bool operator <= (const BigInteger& b) const { return !(b < *this); }
	bool operator >= (const BigInteger& b) const { return !(*this < b); }
	bool operator != (const BigInteger& b) const { return b < *this || *this < b; }
	bool operator == (const BigInteger& b) const { return !(b < *this) && !(*this < b); }
	BigInteger operator + (const BigInteger& b) const {
		BigInteger c;
		c.s.clear();
		int x = 0, i = 0;
		while (i < s.size() || i < b.s.size()) {
			int m, n;
			if (i >= s.size()) m = 0; else m = s[i];
			if (i >= b.s.size()) n = 0; else n = b.s[i];
			c.s.push_back((m + n + x) % BASE);
			x = (m + n + x) / BASE;
			i++;
		}
		if (x != 0) c.s.push_back(x);
		c.s.reserve(c.s.size());
		return c;
	}
	BigInteger operator += (const BigInteger& b) {
		*this = *this + b;
		return *this;
	}
	BigInteger operator - (const BigInteger& b) {
		BigInteger c;
		c.s.clear();
		if (s.size() == b.s.size()) {
			int p = 0;
			for (int i = 0;i < s.size();i++) {
				if (b.s[i] == s[i]) p++;
			}
			if (p == s.size()) { c.s.push_back(0); return c; }
		}
		BigInteger d = *this;
		BigInteger e = b;
		bool isMin = false;
		if (e > d) {
			BigInteger temp = e;
			e = d;
			d = temp;
			isMin = true;
		}
		int x = 0, i = 0;
		while (d.s.size() < e.s.size()) {
			d.s.push_back(0);
		}
		while (d.s.size() > e.s.size()) {
			e.s.push_back(0);
		}
		d.s.push_back(0);
		e.s.push_back(0);
		while (i < d.s.size() || i < e.s.size()) {
			if (d.s[i] < e.s[i]) {
				d.s[i] += 10;
				d.s[i + 1]--;
			}
			c.s.push_back(d.s[i] - e.s[i]);
			i++;
		}
		for (int i = c.s.size() - 1;i >= 0;i--) {
			if (c.s[i] != 0) break;
			c.s.pop_back();
		}
		if (isMin) c.s[c.s.size() - 1] = 0 - c.s[c.s.size() - 1];
		c.s.reserve(c.s.size());
		return c;
	}
	BigInteger operator -= (const BigInteger& b) {
		*this = *this - b;
		return *this;
	}
};
ostream& operator << (ostream& out, const BigInteger& x) {
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--) {
		char buf[20];
		sprintf_s(buf, "%d", x.s[i]); //Dev C++ «Î”√£∫sprintf(buf, "%d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++) out << buf[j];
	}
	return out;
}
istream& operator >> (istream& in, BigInteger& x) {
	string s;
	if (!(in >> s)) return in;
	x = s;
	return in;
}

int main() {
	BigInteger a, b;
	cin >> a >> b;
	cout << a + b << endl;
	cout << a - b << endl;
	if (a > b) {
		cout << "a is larger than b" << endl;
	}
	if (a >= b) {
		cout << "a is larger than b or a is equal to b" << endl;
	}
	if (a < b) {
		cout << "b is larger than a" << endl;
	}
	if (a <= b) {
		cout << "b is larger than a or a is equal to b" << endl;
	}
	if (a == b) {
		cout << "a is equal to b" << endl;
	}
	if (a != b) {
		cout << "a is not equal to b" << endl;
	}
	a += b;
	a -= b;
	cout << a << endl;
	system("pause");
}