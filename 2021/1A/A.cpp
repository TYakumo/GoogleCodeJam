#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

string ItoS(long long val) {
    stringstream ss;
    string ret;
    ss << val;
    ss >> ret;

    return ret;
}

string smallest(string pre, string now) {
    if (now.size() > pre.size() || (now.size() == pre.size() && now > pre)) {
        return now;
    }

    if (pre.size() == now.size()) {
        return now + "0";
    }

    string tmp = now;
    int notNine = -1;
    for (int i = pre.size()-1; i >= 0; --i) {
        if (pre[i] != '9') {
            notNine = i;
            break;
        }
    }

    int prefixCmp = 0;

    for (int i = 0; i < now.size(); ++i) {
        if (pre[i] < now[i]) {
            prefixCmp = 1;
            break;
        } else if (pre[i] > now[i]) {
            prefixCmp = -1;
            break;
        }
    }

    if (prefixCmp == 1) {
        for (int i = now.size(); i < pre.size(); ++i) {
            now += "0";
        }

        return now;
    } else if (prefixCmp == 0 && notNine >= (int)now.size()) {
        for (int i = now.size(); i < notNine; ++i) {
            now += pre[i];
        }

        now += pre[notNine]+1;

        for (int i = notNine+1; i < pre.size(); ++i) {
            now += "0";
        }

        return now;
    } else {
        for (int i = now.size(); i <= pre.size(); ++i) {
            now += "0";
        }
        return now;
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VLL val(N);
        VS vals(N);

        for (int i = 0; i < N; ++i) {
            cin >> val[i];
            vals[i] = ItoS(val[i]);
        }

        int ans = 0;
        for (int i = 1; i < N; ++i) {
            string newVal = smallest(vals[i-1], vals[i]);
            ans += newVal.size() - vals[i].size();
            vals[i] = newVal;
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
