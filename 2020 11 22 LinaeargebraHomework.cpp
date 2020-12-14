#include"CalcN.h"
constexpr auto MaxLength = 100;
const double Accuracy = 0.001;

using namespace std;

void Mswitch(vector<fraction>&, int, int, int);
//交换矩阵两行
void MHStep1(vector<fraction>&, int, int, int);
//将矩阵某一行最左端第一个非零数除到这一整行，返回值是最左端非零数的值
void MHStep2(vector<fraction>&, int, int, int, int, bool = 0);
//将矩阵的某一行乘以k倍加到其余行
void MHerimite(vector<fraction>&, int, int);
//将矩阵化为hermite标准型
void Det(vector<fraction>&, int, fraction&);
//计算矩阵行列式
void MSummit(const vector<fraction>&, vector<fraction>&, int m = 25, int n = 28);
fraction VMulti(const vector<fraction>&, const vector<fraction>&, int);
int main()
{
	/*
	vector<char> la{ 7,8};
	vector<char> lb{ 2,6 };
	signN lam (la);
	signN lbm(lb);
	lam = GcdN(lam, lbm);
	fraction flam(lam);
	flam.print();
	*/

	int czn(1);
	string x;
	signN zero;
	cout << "线代大作业" << endl;
	while (czn) {
		fraction D(zero);
		vector<fraction>* a;
		a = new vector<fraction>(31 * 31);
		vector<fraction>* b;
		b = new vector<fraction>(25 * 28);
		vector<fraction>* c;
		c = new vector<fraction>(25 * 3);
		switch (czn)
		{
		case 1:
			cout << "输入学号：";
			cin >> x;
			cin.get();
			break;
		case 2:
			Min(*a, x, 31, 31);
			Mprint(*a, 31, 31);
			cout << endl;
			D.nume.N.push_back(1);
			Det(*a, 31, D);
			D.print();
			cout << endl;
			break;
		case 3:
			Min(*b, x, 25, 28);
			MHerimite(*b, 25, 28);
			cout << endl;
			Mprint(*b, 25, 28);
			cout << endl;
			break;
		case 4:
			Min(*b, x, 25, 28);
			MSummit(*b, *c);
			Mprint(*c, 25, 3);
			break;
		}
		delete a;
		delete b;
		delete c;
		cout << endl;
		cout << "1：修改学号" << endl << "2：计算行列式" << endl << "3：求规范型阶梯阵" << endl << "4：求标准正交组" << endl;
		cin >> czn;
	}
	return 0;
}

void Mswitch(vector<fraction>& a, int n, int i, int j)
{
	int l;
	if (i != j) {
#pragma omp parallel for
		for (l = 0; l < n; ++l) {
			auto m = a[n * i + l];
			a[n * i + l] = a[n * j + l];
			a[n * j + l] = m;
		}
	}
}

void MHStep1(vector<fraction>& a, int n, int l, int x)
{
	int i;
	fraction m = a[l * n + x];

#pragma omp parallel for
	for (i = x; i < n; ++i) {
		a[l * n + i] = a[l * n + i] / m;
	}
}
void MHStep2(vector<fraction>& a, int m, int n, int l, int x, bool w)
{
	int  i, j;
	fraction p;
	if (!w) {
	auto* t = &a;
#pragma omp parallel for
		for (i = 0; i < m; ++i) {
			if (i != l) {
				p = a[i * n + x] / (*t)[l * n + x];
				for (j = x; j < n; ++j) {
					
					a[i * n + j] = a[i * n + j] - (*t)[l * n + j] * p;
//					a[i * n + j] = a[i * n + j] - a[l * n + j] * p;
				}
			}
			cout << '.';
		}
		cout << endl;
	}
	if (w) {
#pragma omp parallel for
		for (i = l; i < m; ++i) {
			if (i != l) {
				p = a[i * n + x] / a[l * n + x];
				for (j = x; j < n; ++j) {
					a[i * n + j] = a[i * n + j] - a[l * n + j] * p;
				}
			}
			cout << '.';
		}
		cout << endl;
	}

}

void MHerimite(vector<fraction>& a, int m, int n) {
	int i1, i2, flag, flag_x(0);
	signN zero;
	zero.N.push_back(0);
	for (i1 = 0; i1 < m && flag_x < n; ++i1) {

		flag = -1;

		for (i2 = i1; i2 < m; ++i2) {
			if (a[i2 * n + flag_x].nume != zero) {
				flag = i2;
				break;
			}
		}
		if (flag != -1 && flag >= i1) {
			Mswitch(a, n, i1, flag);
			MHStep1(a, n, i1, flag_x);
			MHStep2(a, m, n, i1, flag_x);
			Mprint(a, m, n);
			cout << endl;
		}
		else --i1;
		++flag_x;
	}
}

void Det(vector<fraction>& a, int m, fraction& D) {
	int i1, i2, flag, flag_x(0), n(m);
	signN zero;
	zero.N.push_back(0);
	for (i1 = 0; i1 < m && flag_x < n; ++i1) {

		flag = -1;

		for (i2 = i1; i2 < m; ++i2) {
			if (a[i2 * n + flag_x].nume != zero) {
				flag = i2;
			}
		}
		if (flag != -1 && flag >= i1) {
			if (flag - i1) {
				D.sign = !D.sign;
			}
			Mswitch(a, n, i1, flag);
			//MHStep1(a, n, i1, flag_x,1);
			MHStep2(a, m, n, i1, flag_x,1);
			Mprint(a, m, n);
			cout << endl;
		}
		else --i1;
		++flag_x;
	}
	for (int i = 0; i < n; ++i) {
		D.nume = D.nume * a[i * n + i].nume;
		D.den = D.den * a[i * n + i].den;
		D.sign = D.sign==a[i * n + i].sign;
		cout << "DONE" << endl;
	}
	D.nume.sign = D.sign;
	D.ref();
}
void MSummit(const vector<fraction>& b, vector<fraction>& c, int m, int n) {
	/*vector<fraction> tb = b;

	signN e({ 1 });
	fraction fe(e);
	MHerimite(tb, m, n);
	int flag;
	int i,j,w(min(m,n));
	for (i = 0; i < min(m, n); ++i) {
		flag = 0;
		for (j = 0; j < n; ++j) {
			if (tb[n * i + j].nume == e && tb[n * i + j].den == e) {
				--w;
				flag = j;
				break;
			}

		}
	}*/
	vector<vector<fraction>>p(3);

	for (decltype(p.size()) i = 0; i + 25 < n; ++i) {
		for (decltype(p.size()) j = 0; j < m; ++j) {
			p[i].push_back(b[j * n + i + 25]);
		}
	}
	fraction(*q)[3] = new fraction[3][3];

	for (int i = 0; i < 3; ++i) {
		int j;
		for (j = 0; j < i; ++j) {
			q[i][j] = VMulti(p[i], p[j], m) / VMulti(p[j], p[j], m);
		}
		for (j = 0; j < i; ++j) {
			for (int k = 0; k < m; ++k) {
				p[i][k] = p[i][k] - q[i][j] * p[j][k];
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		auto temp = VMulti(p[i], p[i], 25);
		temp.print();
		cout <<"^-0.5"<< ' ';
	}
	cout << endl;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 3; ++j) {
			c[i * 3 + j] = p[j][i];
		}
	}
}
fraction VMulti(const vector<fraction>& a, const vector<fraction>& b, int n) {
	fraction ans;
	for (int i = 0; i < n; ++i) {
		ans = ans + a[i] * b[i];
	}
	return ans;
}