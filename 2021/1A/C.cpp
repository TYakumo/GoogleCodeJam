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
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

using PLL = pair <long long , string>;
using VPLL = vector <PLL>;
using VVPLL = vector <VPLL>;
using VVVPLL = vector <VVPLL>;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

long long solveComb(const VS& ans, const VI& score, int skip, VI based) {
    int Q = ans[0].size();

    VVVLL dp(Q+1, VVLL(Q+1, VLL(Q+1)));
    VI maxval = based;

    dp[0][based[0]][based[1]] = 1;

    int now = 1;
    for (int i = 0; i < Q; ++i) {
        if (i == skip) {
            continue;
        }

        for (int a = 0; a <= maxval[0] && a <= score[0]; ++a) {
            for (int b = 0; b <= maxval[1] && b <= score[1]; ++b) {
                if (dp[now-1][a][b] == 0) {
                    continue;
                }

                if (ans[0][i] == ans[1][i]) {
                    dp[now][a][b] += dp[now-1][a][b];
                    dp[now][a+1][b+1] += dp[now-1][a][b];
                } else {
                    dp[now][a+1][b] += dp[now-1][a][b];
                    dp[now][a][b+1] += dp[now-1][a][b];
                }
            }
        }

        ++maxval[0];
        ++maxval[1];
        ++now;
    }

    return dp[Q-1][score[0]][score[1]];
}

long long solveComb1(const VS& ans, const VI& score, int skip, VI based) {
    int Q = ans[0].size();

    VVLL dp(Q+1, VLL(Q+1));

    dp[0][based[0]] = 1;

    int now = 1;
    for (int i = 0; i < Q; ++i) {
        if (i == skip) {
            continue;
        }

        for (int a = 0;  a <= score[0]; ++a) {
                if (dp[now-1][a] == 0) {
                    continue;
                }

                dp[now][a] += dp[now-1][a];
                dp[now][a+1] += dp[now-1][a];
        }

        ++now;
    }

    return dp[Q-1][score[0]];
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        cin >> N >> Q;

        VS ans(N);
        VI score(N);
        for (int i = 0; i < N; ++i) {
            cin >> ans[i] >> score[i];
        }

        long long score1 = 0;
        long long scoreN = 1;
        string ansS = ans[0];

        if (N == 1) {
            for (int q = 0; q < Q; ++q) {
                long long Tcomb = solveComb1(ans, score, q, {ans[0][q] == 'T'});
                long long Fcomb = solveComb1(ans, score, q, {ans[0][q] == 'F'});

                long long p1 = max(Tcomb, Fcomb);
                long long pn = Tcomb + Fcomb;

                if (Tcomb > Fcomb) {
                    ansS[q] = 'T';
                } else {
                    ansS[q] = 'F';
                }

                long long g = gcd(p1, pn);
                p1 /= g;
                pn /= g;

                g = gcd(pn, scoreN);

                p1 *= scoreN/g;
                scoreN *= pn/g;
                score1 *= pn/g;
                score1 += p1;

                g = gcd(score1, scoreN);
                score1 /= g;
                scoreN /= g;
            }
        } else {
            for (int q = 0; q < Q; ++q) {
                long long Tcomb = solveComb(ans, score, q, {ans[0][q] == 'T', ans[1][q] == 'T'});
                long long Fcomb = solveComb(ans, score, q, {ans[0][q] == 'F', ans[1][q] == 'F'});

                long long p1 = max(Tcomb, Fcomb);
                long long pn = Tcomb + Fcomb;

                if (Tcomb > Fcomb) {
                    ansS[q] = 'T';
                } else {
                    ansS[q] = 'F';
                }

                long long g = gcd(p1, pn);
                p1 /= g;
                pn /= g;

                g = gcd(pn, scoreN);

                p1 *= scoreN/g;
                scoreN *= pn/g;
                score1 *= pn/g;
                score1 += p1;

                g = gcd(score1, scoreN);
                score1 /= g;
                scoreN /= g;
            }
        }



        cout << "Case #" << tc << ": " << ansS << " " << score1 << "/" << scoreN << endl;
    }

    return 0;
}
