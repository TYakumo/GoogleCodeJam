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
using VD = vector <long double>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int L;
        cin >> N >> L;

        VI cnt(L);
        VLL cand;
        int remain = N;
        long long ans = 0;

        long long threshold = (N+1)/2;
        long long comp = N-threshold;

        for (int i = 0; i < L; ++i) {
            cin >> cnt[i];
            remain -= cnt[i];

            long long HC = cnt[i]*100;
            ans += (HC+comp)/N;

            if (HC%N < threshold) {
                cand.push_back(HC%N);
            }
        }

        sort(cand.begin(), cand.end(), greater<long long>());
        for (int i = cand.size(); i < N; ++i) {
            cand.push_back(0);
        }

        long long diff = 100%N;

        if (diff == 0) {
            ans += remain*100/N;
        } else {
            for (int i = 0; i < cand.size() && remain > 0; ++i) {
                long long mul = (threshold-cand[i]) / diff;

                while (cand[i] + mul*diff < threshold) {
                    ++mul;
                }

                if (remain >= mul) {
                    ans += (cand[i] + mul*100LL+comp) / N;
                    remain -= mul;
                } else {
                    ans += (cand[i] + remain*100LL+comp) / N;
                    remain = 0;
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
