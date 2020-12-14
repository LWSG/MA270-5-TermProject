#include"CalcN.h"

void RevsN(vector<char>& D) {
    vector<char>E = D;
    for (decltype(D.size()) i = 0; i != D.size(); ++i) {
        D[i] = E[D.size() - 1 - i];
    }

}
void FomN(vector<char>& D, string n) {
    for (auto i : n) {
        D.push_back((char)(i - '0'));
    }
}
void PrintN(vector<char>D) {
    for (auto i : D) {
        cout << i - 0;
    }
}
vector<char> PlusN(vector<char>a, vector<char>b) {
    vector<char>A(a.size() > b.size() ? a.size() : b.size());
    RevsN(a);
    RevsN(b);
    A = a.size() < b.size() ? b : a;
    for (decltype(a.size())i = 0; i != a.size() && i != b.size(); ++i) {
        A[i] += a.size() < b.size() ? a[i] : b[i];
    }
    int p(0);
    for (decltype(a.size())i = 0; i != A.size(); ++i) {
        A[i] += p;
        p = A[i] / 10;

        A[i] = A[i] % 10;

    }
    if (p) {
        A.push_back((char)p);
    }
    RevsN(A);
    return A;

}
vector<char> MultiN(vector<char>a, vector<char>b) {
    vector<char>c;
    vector<char>e;
    e.push_back(1);
    vector<char>f;
    vector<char>Tf;
    vector<char>Tc;
    auto p = a.size();
    auto bs = b.size();
    vector<char>zero{ 0 };
    if (a==zero|| b==zero)return zero;
    for (auto i = a.begin(); i != a.end(); ++i) {
        b.push_back(0);
        e.push_back(0);
    }
    --p;
    e.erase(e.begin() + 1 + p);

    b.erase(b.begin() + bs + p);
    while (c != a) {

        Tf = PlusN(b, f);
        Tc = PlusN(c, e);

        if (Tc.size()==a.size()&&Tc > a||Tc.size()>a.size()) {
            --p;
            b.erase(b.begin() + bs + p);
            e.erase(e.begin() + 1 + p);

        }
        else if (Tc.size() == a.size() && Tc < a || Tc.size() < a.size()) {
            c = Tc;
            f = Tf;
        }
        else {
            f = Tf;
            c = Tc;
        }
    }
    return f;
}
vector<char> DvidN(vector<char>a, vector<char>b) {

    int p = a.size() - b.size();
    if (p >= 0) {
        ++p;
        vector<char>T;
        vector<char>A;
        vector<char>w(p);
        w[0] = 1;
        vector<char>ans{ 0 };


        while (A.size() < a.size() || w.size()) {
            T = PlusN(A, MultiN(b, w));

            if (T.size() == a.size() && T > a||T.size()>a.size()) {
                if (w.size() == 1)break;
                w.erase(w.begin() + p - 1);
                --p;
            }
            else if (T == a) {
                ans = PlusN(ans, w);
                break;
            }
            else {
                ans = PlusN(ans, w);
                A = T;
            }

        }
        return ans;
    }
    else {
        vector<char>A{ 0 };
        return A;
    }
}
vector<char> PowN(vector<char>a, vector<char>b) {
    vector<char>i{ 1 };
    vector<char>e{ 1 };
    vector<char>ans(a);
    while (i != b) {
        ans = MultiN(ans, a);
        i = PlusN(i, e);
    }
    return ans;
}
signN MinusN(const signN& a, const signN& b) {
    signN t;
    signN ta(a);
    signN tb(b);
    vector<char>zero{ 0 };
    if (ta.N.size() < tb.N.size() || ta.N.size() == tb.N.size() && ta.N < tb.N) {
        auto temp = ta;
        ta = tb;
        tb = temp;
        t.sign = !t.sign;
    }
    if (ta == tb) {
        t.N = zero;
        return t;
    }
    if (ta.sign != tb.sign) {
        tb.sign = !(b.sign);
        t.N = PlusN(a.N, b.N);
        t.sign = a.sign;
        return t;
    }
    else {
        if (!t.sign) {
            ta = b; tb = a;
        }


        RevsN(ta.N);
        RevsN(tb.N);
        t.N = ta.N;
        int temp(0);
        decltype(b.N.size()) i;
        for (i = 0; i < tb.N.size(); ++i) {
            if (ta.N[i] >= (tb.N[i]+temp)) {
                t.N[i] = ta.N[i] - tb.N[i]-temp;
                temp = 0;
            }
            else {
                t.N[i] = 10 + ta.N[i] - tb.N[i]-temp;
                temp = 1;
            }
        }
        while (temp) {
            if (ta.N[i] >= 1) {
                t.N[i] = ta.N[i] - 1;
                temp = 0;
            }
            else {
                t.N[i] = 10 + ta.N[i] - 1;
                temp = 1;
                ++i;
            }
        }
    }
    
    while (t.N[t.N.size() - 1] == 0&&t.N.size())t.N.pop_back();
    RevsN(t.N);
    return t;
}
signN GcdN(const signN&a, const signN&b) {
    signN ta = a;
    signN tb = b;
    ta.sign = 1;
    tb.sign = 1;
    /*
    signN ans;
    ans.N.push_back(1);
    signN zero;
    zero.sign = 1;
    zero.N = { 0 };
    if (ta == zero || tb == zero) {
        zero.N[0] = 1;
        return zero;
    }
    zero.N[0] = 2;
    while (ta.iseven() && tb.iseven()) {
        ta = ta / 2;
        tb = tb / 2;
        ans = ans * zero;
    }
    while (ta != tb) {
        if (ta > tb) {
            ta = ta - tb;
        }
        else {
            tb = tb - ta;
        }
    }
    return ans*ta;*/
    signN zero;
    zero.sign = 1;
    zero.N = { 0 };
    if (ta < tb) {
        auto t = ta;
        ta = tb;
        tb = t;
    }
    if (ta == tb)return ta;
    if (ta % tb==zero) {
        return tb;
    }
    else {
        ta = ta % tb;
        return GcdN(ta, tb);
    }
}


void Min(vector<fraction>& a, string x, int m, int n) {
    signN pb;
    //b.N.pop_back();
    FomN(pb.N, x);
    signN npb;
    vector<signN>b(pb.N.size(),npb);
    for (int i = 0; i < pb.N.size(); ++i) {
        b[i].N.push_back(pb.N[i]);
    }
    vector<char>en{ 1 };
    signN D;
    signN e{ en };
    for (int i = 0, j = 0, k = 0, d = 0; j < m * n;) {
        D = b[k % 12] ^ ((int)k / 12 + 1);
        d = D.N.size();
        for (int k = 0, t = 0; k < d; ++k) {
            t = (j + k) / n;
            if (k + j >= m * n)break;
            a[t * n + (j + k) % n].nume.N[0] = D.N[k];
        }
        k += 1;
        j += d;
    }
}
void Mprint(vector<fraction>a, int m, int n) {

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i * n + j].print();
            cout << ' ';
        }
        cout << endl;
    }
}