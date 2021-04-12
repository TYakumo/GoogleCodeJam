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
using VUMLL = vector <UMLL>;
using VS = vector <string>;
using VC = vector <char>;
const long long INF = 1000000000LL;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int M;
        cin >> M;

        VLL N(M);
        VLL P(M);
        long long sum = 0;

        for (int i = 0; i < M; ++i) {
            cin >> P[i] >> N[i];
            sum += P[i] * N[i];
        }


        long long ans = 0;
        for (long long m = 1; m <= 5000 && m < sum; ++m) {
            long long remain = sum - m;
            long long tmp = remain;

            VLL MN(M);
            long long dsum = 0;
            for  (int i = 0; i < M; ++i) {
                while (tmp % P[i] == 0) {
                    tmp /= P[i];
                    ++MN[i];
                    dsum += P[i];
                }
            }

            if (tmp == 1 && dsum == m) {
                bool ok = true;
                for  (int i = 0; i < M; ++i) {
                    if (MN[i] > N[i]) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    ans = max(ans, remain);
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
