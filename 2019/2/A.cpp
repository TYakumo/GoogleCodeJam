#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

struct Num {
    long long fact;
    long long deno;

    Num(long long f, long long d) : fact(f), deno(d) {
        long long g = gcd(f, d);
        fact /= g;
        deno /= g;
    }

    Num() {
    }

    bool operator<(const Num& n) const {
        long long num[2] = {fact*n.deno, n.fact*deno};

        return num[0] < num[1];
    }

    bool operator<=(const Num& n) const {
        long long num[2] = {fact*n.deno, n.fact*deno};
        return num[0] <= num[1];
    }

    bool operator==(const Num& n) const {
        long long num[2] = {fact*n.deno, n.fact*deno};
        return num[0] == num[1];
    }

    bool operator!=(const Num& n) const {
        return !(*this == n);
    }
};

vector <Num> uniqueNum(vector<Num>& nums) {
    vector <Num> ret;

    ret.push_back(nums[0]);
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[i-1]) {
            ret.push_back(nums[i]);
        }
    }

    return ret;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        vector <vector<long long>> mole(N);

        for (int i = 0; i < N; ++i) {
            long long C;
            long long J;
            cin >> C >> J;
            mole[i] = {0, i, C, J};
        }

        const long long INF = 1000000010;
        vector<Num> low;
        vector<Num> up;

        low.emplace_back(Num(-INF, 1));
        up.emplace_back(Num(INF, 1));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if ((mole[j][2] > mole[i][2] || mole[j][3] > mole[i][3])
                && (mole[j][2] < mole[i][2] || mole[j][3] < mole[i][3])) {
                    if (mole[j][2] > mole[i][2]) { // J < C
                        long long diff[2] = {mole[j][2]-mole[i][2], mole[i][3]-mole[j][3]};
                        low.emplace_back(Num(diff[0], diff[1]));
                    } else { // C < J
                        long long diff[2] = {mole[j][3]-mole[i][3], mole[i][2]-mole[j][2]};
                        up.emplace_back(Num(diff[1], diff[0]));
                    }
                }
            }
        }

        int idx = 0;
        int ans = 0;
        sort(low.begin(), low.end());
        sort(up.begin(), up.end());

        vector<Num> ulow = uniqueNum(low);
        vector<Num> uup = uniqueNum(up);

        for (int i = 0; i < ulow.size(); ++i) {
            while (idx < uup.size() && uup[idx] <= ulow[i]) {
                ++idx;
            }

            if (idx < uup.size() && ulow[i] < uup[idx]) {
                ++ans;
            }
        }

        while (idx+1 < uup.size()) {
            ++idx;
            ++ans;
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
