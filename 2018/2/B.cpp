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
using VVI = vector<VI>;
using VVVI = vector<VVI>;

bool cmp(pair<int, int>& a, pair<int, int>& b) {
    return a.first+a.second < b.first+b.second;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int B;
        int R;
        cin >> R >> B;

        vector< pair <int, int> > cho;

        for (int i = 0; i <= R; ++i) {
            for (int j = 0; j <= B; ++j) {
                if (i || j) {
                    cho.emplace_back(make_pair(i, j));
                }
            }
        }

        sort(cho.begin(), cho.end(), cmp);

        int UPPER = 200;
        VVI dp(R+1, VI(B+1, -1));

        dp[0][0] = 0;
        int ans = 0;

        for (int i = 0; i < UPPER && i < cho.size(); ++i) {
            if (cho[i].first + cho[i].second > R + B) {
                break;
            }

            for (int a = R; a >= 0; --a) {
                for (int b = B; b >= 0; --b) {
                    if (dp[a][b] >= 0 && a + cho[i].first <= R && b + cho[i].second <= B) {
                        int NR = a + cho[i].first;
                        int NB = b + cho[i].second;
                        dp[NR][NB] = max(dp[NR][NB], dp[a][b] + 1);

                        if (NR == R && NB == B) {
                            ans = max(ans, dp[R][B]);
                        }

                    }
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
