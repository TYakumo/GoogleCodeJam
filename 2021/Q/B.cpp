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

using VI = vector <int>;
using VVI = vector <VI>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int X;
        int Y;
        string S;

        cin >> X >> Y >> S;

        const int INF = 1000000000;
        VI dp1(2, INF);
        VI dp2(2, INF);

        // init
        if (S[0] == '?') {
            dp1[0] = dp1[1] = 0;
        } else if (S[0] == 'C') {
            dp1[0] = 0;
        } else {
            dp1[1] = 0;
        }

        for (int i = 1; i < S.size(); ++i) {
            dp2[0] = dp2[1] = INF;

            for (int p = 0; p < 2; ++p) {
                if (S[i] == '?') {
                    if (dp1[0] != INF) {
                        dp2[0] = min(dp2[0], dp1[0]); // CC
                    }

                    if (dp1[0] != INF) {
                        dp2[1] = min(dp2[1], dp1[0]+X); // CJ
                    }

                    if (dp1[1] != INF) {
                        dp2[1] = min(dp2[1], dp1[1]); // JJ
                    }

                    if (dp1[1] != INF) {
                        dp2[0] = min(dp2[0], dp1[1]+Y); // JC
                    }
                } else if (S[i] == 'C') {
                    if (dp1[1] != INF) {
                        dp2[0] = min(dp2[0], dp1[1]+Y); // JC
                    }

                    if (dp1[0] != INF) {
                        dp2[0] = min(dp2[0], dp1[0]); // CC
                    }
                } else {
                    if (dp1[1] != INF) {
                        dp2[1] = min(dp2[1], dp1[1]); // JJ
                    }

                    if (dp1[0] != INF) {
                        dp2[1] = min(dp2[1], dp1[0]+X); // CJ
                    }
                }
            }

            dp1 = dp2;
        }

        cout << "Case #" << tc << ": " << min(dp1[0], dp1[1]) << endl;
    }

    return 0;
}
