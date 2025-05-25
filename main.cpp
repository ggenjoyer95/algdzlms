#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;
static size_t cmp = 0;

bool cmpClassic(const string &a, const string &b) {
    int i = 0, na = a.size(), nb = b.size();
    while (i < na && i < nb) {
        ++cmp;
        if (a[i] != b[i]) break;
        ++i;
    }
    if (i == na && i == nb) return false;
    if (i == na)          return true;
    if (i == nb)          return false;
    ++cmp;
    return a[i] < b[i];
}

void msClassic(vector<string> &v, int l, int r, vector<string> &tmp) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    msClassic(v, l,     m, tmp);
    msClassic(v, m + 1, r, tmp);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (cmpClassic(v[i], v[j])) tmp[k++] = move(v[i++]);
        else                         tmp[k++] = move(v[j++]);
    }
    while (i <= m) tmp[k++] = move(v[i++]);
    while (j <= r) tmp[k++] = move(v[j++]);
    for (int p = l; p <= r; ++p) v[p] = move(tmp[p]);
}

bool cmpA1m(const string &a, const string &b) {
    int i = 0, na = a.size(), nb = b.size();
    while (i < na && i < nb) {
        ++cmp;
        if (a[i] != b[i]) break;
        ++i;
    }
    if (i == na && i == nb) return false;
    if (i == na)          return true;
    if (i == nb)          return false;
    ++cmp;
    return a[i] < b[i];
}

void msA1m(vector<string> &v, int l, int r, vector<string> &tmp) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    msA1m(v, l,     m, tmp);
    msA1m(v, m + 1, r, tmp);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (cmpA1m(v[i], v[j])) tmp[k++] = move(v[i++]);
        else                     tmp[k++] = move(v[j++]);
    }
    while (i <= m) tmp[k++] = move(v[i++]);
    while (j <= r) tmp[k++] = move(v[j++]);
    for (int p = l; p <= r; ++p) v[p] = move(tmp[p]);
}

void sortA1m(vector<string> &a) {
    if (a.empty()) return;
    vector<string> tmp(a.size());
    msA1m(a, 0, a.size() - 1, tmp);
}

inline int charAtQ(const string &s, int d) {
    return d < (int)s.size() ? (unsigned char)s[d] : -1;
}

void sortA1q_rec(vector<string> &a, int lo, int hi, int d) {
    if (lo >= hi) return;
    int lt = lo, gt = hi;
    int v = charAtQ(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int c = charAtQ(a[i], d);
        ++cmp;
        if (c < v)      { swap(a[lt++], a[i++]); }
        else {
            ++cmp;
            if (c > v)   { swap(a[i], a[gt--]); }
            else         { ++i; }
        }
    }
    sortA1q_rec(a, lo, lt - 1, d);
    if (v >= 0) sortA1q_rec(a, lt, gt, d + 1);
    sortA1q_rec(a, gt + 1, hi, d);
}

void sortA1q(vector<string> &a) {
    if (a.empty()) return;
    sortA1q_rec(a, 0, a.size() - 1, 0);
}

const int krR = 256;
inline int charinR(const string &s, int d) {
    ++cmp;
    return d < (int)s.size() ? (unsigned char)s[d] + 1 : 0;
}

void rsA1r(vector<string> &a, vector<string> &aux, int lo, int hi, int d) {
    if (lo >= hi) return;
    array<int, krR + 2> cnt{};
    for (int i = lo; i <= hi; ++i) ++cnt[ charinR(a[i], d) + 1 ];
    for (int r = 0; r <= krR; ++r) cnt[r + 1] += cnt[r];
    auto start = cnt;
    for (int i = lo; i <= hi; ++i) aux[start[ charinR(a[i], d) ]++] = move(a[i]);
    for (int i = lo; i <= hi; ++i) a[i] = move(aux[i - lo]);
    for (int r = 0; r <= krR; ++r) {
        int l2 = lo + cnt[r];
        int r2 = lo + cnt[r + 1] - 1;
        if (l2 < r2) rsA1r(a, aux, l2, r2, d + 1);
    }
}

void sortA1r(vector<string> &a) {
    if (a.empty()) return;
    vector<string> aux(a.size());
    rsA1r(a, aux, 0, a.size() - 1, 0);
}

const int krRQ = 256;
inline int charinRQ(const string &s, int d) {
    ++cmp;
    return d < (int)s.size() ? (unsigned char)s[d] + 1 : 0;
}

void rsA1rq(vector<string> &a, vector<string> &aux, int lo, int hi, int d) {
    if (lo >= hi) return;
    if (hi - lo + 1 <= krRQ) {
        sortA1q_rec(a, lo, hi, d);
        return;
    }
    array<int, krRQ + 2> cnt{};
    for (int i = lo; i <= hi; ++i) ++cnt[ charinRQ(a[i], d) + 1 ];
    for (int r = 0; r <= krRQ; ++r) cnt[r + 1] += cnt[r];
    auto start = cnt;
    for (int i = lo; i <= hi; ++i) aux[start[ charinRQ(a[i], d) ]++] = move(a[i]);
    for (int i = lo; i <= hi; ++i) a[i] = move(aux[i - lo]);
    for (int r = 0; r <= krRQ; ++r) {
        int l2 = lo + cnt[r];
        int r2 = lo + cnt[r + 1] - 1;
        if (l2 < r2) rsA1rq(a, aux, l2, r2, d + 1);
    }
}

void sortA1rq(vector<string> &a) {
    if (a.empty()) return;
    vector<string> aux(a.size());
    rsA1rq(a, aux, 0, a.size() - 1, 0);
}

struct StringGenerator {
    const string alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#%:;^&*()-.";
    mt19937 rng;
    StringGenerator() { rng.seed(time(nullptr)); }
    string RandomString() {
        uniform_int_distribution<int> dlen(10, 200);
        uniform_int_distribution<int> dalph(0, (int)alphabet.size()-1);
        int L = dlen(rng);
        string s; s.reserve(L);
        while (L--) s += alphabet[dalph(rng)];
        return s;
    }
    vector<string> RandomArr(int type) {
        constexpr int MAXN = 3000;
        vector<string> a; a.reserve(MAXN);
        for (int i = 0; i < MAXN; ++i) a.push_back(RandomString());
        if (type == 1) sort(a.begin(), a.end(), greater<>());
        else if (type == 2) {
            sort(a.begin(), a.end());
            uniform_int_distribution<int> dsw(3,7), didx(0,MAXN-2);
            int swaps = dsw(rng);
            while (swaps--) { int i = didx(rng); swap(a[i], a[i+1]); }
        }
        return a;
    }
};

enum Alg { CQ, CM, A1M, A1Q, A1R, A1RQ };
string nameOf(Alg a) {
    switch(a) {
        case CQ:   return "cq";
        case CM:   return "cm";
        case A1M:  return "a1m";
        case A1Q:  return "a1q";
        case A1R:  return "mr";
        case A1RQ: return "mrq";
    }
    return string();
}

void runOne(Alg alg, vector<string> data) {
    int sz = data.size();
    auto t0 = chrono::high_resolution_clock::now();
    cmp = 0;

    switch (alg) {
        case CQ:  sort(data.begin(), data.end(), cmpClassic); break;
        case CM:  {
            vector<string> tmp(sz);
            msClassic(data, 0, sz-1, tmp);
            break;
        }
        case A1M: sortA1m(data); break;
        case A1Q: sortA1q(data); break;
        case A1R: sortA1r(data); break;
        case A1RQ: sortA1rq(data); break;
    }

    auto t1 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t1-t0).count();
    string base = nameOf(alg);
    ofstream ft(base + "t.txt", ios::app);
    ofstream fc(base + "c.txt", ios::app);
    ft << ms << '\n';
    fc << cmp << '\n';
}

int main() {
    StringGenerator gen;
    vector<int> sizes;
    for (int x = 100; x <= 3000; x += 100) sizes.push_back(x);
    vector<int> types = {0,1,2};
    vector<Alg> algs = {CQ,CM,A1M,A1Q,A1R,A1RQ};
    for (auto &alg : algs) {
        string base = nameOf(alg);
        remove((base + "t.txt").c_str());
        remove((base + "c.txt").c_str());
    }

    for (auto alg : algs)
      for (auto sz : sizes)
        for (auto tc : types)
          for (int run = 0; run < 10; ++run) {
            auto base = gen.RandomArr(tc);
            vector<string> data(base.begin(), base.begin() + sz);
            runOne(alg, data);
          }

    cout << fixed << setprecision(3);
    for (auto alg : algs) {
        string base = nameOf(alg);
        ifstream it(base + "t.txt");
        ifstream ic(base + "c.txt");
        double sumt=0, sumc=0, x; int cnt=0;
        while (it >> x) { sumt += x; ++cnt; }
        while (ic >> x) sumc += x;
        cout << base << ": avg time = " << (cnt ? sumt/cnt : 0)
             << " ms, avg comps = " << (cnt ? sumc/cnt : 0) << "\n";
    }
    return 0;
}
