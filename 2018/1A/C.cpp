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
#include <iomanip>
#include <sstream>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using VUMI = vector <UMI>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

using UMID = unordered_map <int, double>;
using VUMID = vector <UMID>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int P;
        cin >> N >> P;

        VVI L(N, VI(2));
        VUMI cand(N+1);
        // max = 250*4*100 = 10^5
        cand[0][0] = 1;

        for (int i = 0; i < N; ++i) {
            cin >> L[i][0] >> L[i][1];
        }

        VUMID dp(N+1);
        dp[0][0] = 0;

        double ans = 0;

        for (int i = 0; i < N; ++i) {
            auto iter = cand[i].begin();
            int allbase = 2*(L[i][0] + L[i][1]);
            int sallbase = 2*(L[i][0] + L[i][1]) + 2*min(L[i][0], L[i][1]);
            double plus = 2*sqrt(L[i][0]*L[i][0] + L[i][1]*L[i][1]) - 2*min(L[i][0], L[i][1]);

            while (iter != cand[i].end()) {
                int base = iter->first;
                // not split
                cand[i+1][base+allbase] = 1;
                dp[i+1][base+allbase] = max(dp[i+1][base+allbase], dp[i][base]);

                // split
                cand[i+1][base+sallbase] = 1;
                dp[i+1][base+sallbase] = max(dp[i+1][base+sallbase], dp[i][base]+plus);

                ++iter;
            }
        }

        auto iter = cand[N].begin();
        while (iter != cand[N].end()) {

            if (iter->first <= P) {
                double upper = iter->first + dp[N][iter->first];

                if (upper >= P) {
                    ans = P;
                    break;
                } else {
                    ans = max(ans, upper);
                }
            }

            ++iter;
        }

        cout << setprecision(15) << fixed << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
