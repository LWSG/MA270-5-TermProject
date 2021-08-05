#ifndef calc_h
#define calc_h


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
//���ɾ���
void Min(vector<fraction>&, string, int, int);
//�������
void Mprint(vector<fraction>, int, int);
class signN {
public:
	//���캯��
	signN(void) :sign(1), N(e) {}
	signN(vector<char>N) :sign(1), N(N) {}
	signN(bool a, vector<char>N) :sign(a), N(N) {}
	//�ȴ�С
	bool operator>(const signN& b) const;
	bool operator==(const signN& b) const;
	bool operator!=(const signN& b) const;
	bool operator<(const signN& b) const;
	//�Ӽ��˳�ȡģ�˷�
	signN operator+(const signN& b) const;
	signN operator-(const signN& b) const;
	signN operator*(const signN& b)const;
	signN operator/(const signN& b) const;
	signN operator/(int b) const;
	signN operator%(const signN& b)const;
	signN operator^(const signN& b)const;
	signN operator^(const int& b)const;
	bool iseven(void)const;

	//��Ա����
	bool sign;
	vector<char>N;
private:
	vector<char>e{ 1 };
};
class fraction {
public:

	//���캯��
	fraction(void) : nume({ 0 }), den({ 1 }), sign(1) {}
	fraction(vector<char>a, vector<char>b) : nume(a), den(b), sign(1) {}
	fraction(bool sign, vector<char>a, vector<char>b) :sign(sign), nume(a), den(b) {}
	fraction(signN a) :sign(a.sign), nume(a.N), den({ 1 }) {}
	fraction(signN a, signN b) :sign(a.sign == b.sign), nume(a.N), den(b.N) {}

	//��ӡ���
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

	//������
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
	//�Ӽ��˳�
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

	//��Ա����
	bool sign;
	signN nume;
	signN den;
};

#endif