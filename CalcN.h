#pragma once
#include <iostream>
#include <string.h>
#include<string>
#include<vector>
using namespace std;

class signN;
class fraction;

void RevsN(vector<char>&);
void FomN(vector<char>&, string);
void PrintN(vector<char>);
vector<char> PlusN(vector<char>, vector<char>);
vector<char> MultiN(vector<char>, vector<char>);
vector<char> DvidN(vector<char>, vector<char>);
vector<char> PowN(vector<char>, vector<char>);
signN MinusN(const signN&, const signN&);
signN GcdN(const signN&, const signN&);

//生成矩阵
void Min(vector<fraction>&, string, int, int);
//输出矩阵
void Mprint(vector<fraction>, int, int);

class signN {
public:

	//构造函数
	signN(void) :sign(1), N(e) {}
	signN(vector<char>N) :sign(1), N(N) {}
	signN(bool a, vector<char>N) :sign(a), N(N) {}

	//比大小
	bool operator>(const signN& b) const
	{
		if (this->sign != b.sign) {
			if (this->sign)return true;
			if (b.sign)return false;
		}
		else {
			if (this->sign) {
				if ((this->N).size() == b.N.size())
					return this->N > b.N;
				else return (this->N).size() > b.N.size();
			}
			else {
				if ((this->N).size() == b.N.size())
					return this->N < b.N;
				else return (this->N).size() < b.N.size();
			}
		}
	}
	bool operator==(const signN& b) const
	{
		if (this->sign == b.sign) {
			if (this->N == b.N) {
				return true;
			}
		}
		return false;
	}
	bool operator!=(const signN& b) const
	{
		return !(*this==b);
	}
	bool operator<(const signN& b) const
	{
		if (*this == b)return false;
		return !(*this > b);
	}

	//加减乘除取模乘方
	signN operator+(const signN& b) const
	{
		signN a;
		signN tb = b;
		signN tt = *this;
		if (this->sign == b.sign) {
			a.N = PlusN(this->N, b.N);
			a.sign = this->sign;
			return a;
		}
		else {
			if (this->sign) {
				tb.sign = 1;
				a = MinusN(*this, tb);
			}else{
				tt.sign = 1;
				a = MinusN(tt, tb);
				a.sign = !a.sign;
			}
		}
		return a;
	}
	signN operator-(const signN& b) const
	{
		signN tb = b;
		tb.sign = !b.sign;
		return *this+tb;
	}
	signN operator*(const signN& b)const
	{
		signN a;
		vector<char>zero{ 0 };
		a.N = MultiN(this->N, b.N);
		if (this->sign != b.sign) {
			a.sign = 0;
		}
		else a.sign = 1;
		if (a.N == zero)a.sign = 1;
		return a;
	}
	signN operator/(const signN& b) const
	{
		signN a;
		vector<char>zero{ 0 };
		a.N = DvidN(this->N, b.N);
		if (this->sign != b.sign) {
			a.sign = 0;
		}
		if (a.N == zero)a.sign = 1;
		return a;
	}
	signN operator/(int b) const
	{
		signN a(*this);
		vector<char>zero{ 0 };
		int t(0);
		for (int i = 0; i < a.N.size();++i ) {
			a.N[i] = (this->N[i] + t) / b;
			t = (this->N[i] + t) % b*10;
		}
		if (a.N[0] == 0) {
			RevsN(a.N);
			while(a.N[a.N.size()-1]==0)a.N.pop_back();
			RevsN(a.N);
		}
		if (this->sign != (b>=0)) {
			a.sign = 0;
		}
		if (a.N == zero)a.sign = 1;
		return a;
	}
	signN operator%(const signN& b)const
	{
		signN a;
		signN c(*this);
		signN d(b);
		vector<char>zero{ 0 };
		c.sign = 1;
		d.sign = 1;
		auto t = *this / b;
		a = *this - t* b;
		if (a.N == zero)a.sign = 1;
		return a;
	}
	signN operator^(const signN& b)const {
		if (!this->sign && !b.sign) {
			cerr << "CalcN.h:line 133 Error type" << endl;
		}
		signN ans;
		ans.N = { 1 };
		signN i(ans);
		signN e(ans);
		vector<char>zero{ 0 };
		if (b.N == zero) {
			return ans;
		}
		while (i.N != b.N) {
			ans = ans * *this;
			i = i + e;
		}
		ans = ans * *this;
		return ans;
	}
	signN operator^(const int& b)const {
		if (!this->sign && b<0) {
			cerr << "CalcN.h:line 133 Error type" << endl;
		}
		signN ans;
		ans.N = { 1 };
		int i = 1;
		if (b == 0) {
			return ans;
		}
		while (i != b) {
			ans = ans * *this;
			i = i + 1;
		}
		ans = ans * *this;
		return ans;
	}
	bool iseven(void) {
		if (this->N[this->N.size() - 1] % 2 == 0)return true;
		else return false;
	}

	//成员函数
	bool sign;
	vector<char>N;

private:
	vector<char>e{ 1 };
};
class fraction {
public:

	//构造函数
	fraction(void) : nume({ 0 }), den({ 1 }), sign(1) {}
	fraction(vector<char>a, vector<char>b) : nume(a), den(b), sign(1) {}
	fraction(bool sign, vector<char>a, vector<char>b) :sign(sign), nume(a), den(b) {}
	fraction(signN a) :sign(a.sign), nume(a.N), den({ 1 }) {}
	fraction(signN a, signN b) :sign(a.sign == b.sign), nume(a.N), den(b.N) {}

	//打印输出
	void print() {
		if (!sign)cout << '-';
		for (auto i : nume.N) {
			cout << i - 0;
		}
		if (den.N.size() == 1 && den.N[0] == 1)return;
		cout << '/';
		for (auto i : den.N) {
			cout << i - 0;
		}
	}

	//化简函数
	void ref() {
		signN zero;
		zero.N.push_back(0);
		if (nume.N == zero.N ) {
			zero.N[0] = 1;
			den = zero;
			sign = 1;
			return;
		}
		auto gcd = GcdN(nume, den);
		nume = nume / gcd;
		den = den / gcd;
		sign = nume.sign == den.sign;
		nume.sign = 1;
		den.sign = 1;
	}
	//加减乘除
	fraction operator+(const fraction& b) const& {
		fraction ans;
		fraction templ=*this;
		fraction tempr = b;
		templ.nume.sign = this->sign;
		tempr.nume.sign = b.sign;
		ans.den = this->den * b.den;
		ans.nume = templ.nume * b.den + templ.den * tempr.nume;
		ans.ref();
		return ans;
	}
	fraction operator-(const fraction& b) const& {
		fraction ans;
		fraction templ = *this;
		fraction tempr = b;
		templ.nume.sign = this->sign;
		tempr.nume.sign = b.sign;
		ans.den = this->den * b.den;
		ans.nume = templ.nume * b.den - this->den * tempr.nume;
		ans.ref();
		return ans;
	}
	fraction operator*(const fraction& b) const& {
		fraction ans;
		fraction templ = *this;
		fraction tempr = b;
		templ.nume.sign = this->sign;
		tempr.nume.sign = b.sign;
		ans.den = this->den * b.den;
		ans.nume = templ.nume *  tempr.nume;
		ans.ref();
		return ans;
	}
	fraction operator/(const fraction& b) const& {
		fraction templ = *this;
		fraction tempr = b;
		templ.nume.sign = this->sign;
		tempr.nume.sign = b.sign;
		fraction ans;
		ans.den = this->den * tempr.nume;
		ans.nume = templ.nume * b.den;
		ans.ref();
		return ans;
	}

	//成员函数
	bool sign;
	signN nume;
	signN den;
};