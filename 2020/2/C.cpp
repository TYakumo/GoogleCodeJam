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
// int comb = 0;

using VLL = vector <long long>;
using VVLL = vector <VLL>;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

long long abGcd(long long a, long long b) {
    long long g = gcd(a, b);
    if (g < 0) {
        g = -g;
    }

    return g;
}

bool sameLine(long long x1, long long y1, long long x2, long long y2, long long dx, long long dy) {
    long long ndx = x2 - x1;
    long long ndy = y2 - y1;
    long long g = abGcd(ndx, ndy);

    ndx /= g;
    ndy /= g;

    return ndx == dx && ndy == dy;
}

void solve(VI& mat, VVLL& coor, int now, int& ans) {
    int N = mat.size();

    if (now == N) {
        // ++comb;
        // starting direction
        set < pair<long long, long long> > tried;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                long long dx = coor[i][0] - coor[j][0];
                long long dy = coor[i][1] - coor[j][1];

                if (dx == 0 && dy == 0) {
                    continue;
                }

                long long g = abGcd(dx, dy);
                dx /= g;
                dy /= g;

                if (tried.count(make_pair(dx, dy))) {
                    continue;
                }

                tried.insert(make_pair(dx, dy));

                for (int s = 0; s < N; ++s) { //starting point
                    vector <bool> visited(N);
                    vector <bool> entered(N);
                    int res = 1;
                    int nowV = s;

                    visited[nowV] = true;

                    for (int t = 1; t < N; ++t) {
                        long long minDist = -1;
                        int np = -1;

                        entered[nowV] = true;

                        if (mat[nowV] == -1) {
                            break; // stopped
                        } else {
                            nowV = mat[nowV]; // worm hole
                        }

                        if (!visited[nowV]) {
                            visited[nowV] = true;
                            ++res;
                        }

                        // find next point
                        for (int n = 0; n < N; ++n) {
                            // check if on the same line
                            if (n != nowV && sameLine(coor[nowV][0], coor[nowV][1], coor[n][0], coor[n][1], dx, dy)) {
                                long long ndx = coor[nowV][0] - coor[n][0];
                                long long ndy = coor[nowV][1] - coor[n][1];
                                long long cdist = ndx*ndx + ndy*ndy;
                                // cout << "AT LEAST SAME LINE" << endl;

                                if (minDist == -1 || cdist < minDist) {
                                    minDist = cdist;
                                    np = n;
                                }
                            }
                        }

                        if (np == -1 || entered[np]) {
                            break;
                        }

                        nowV = np;

                        if (!visited[nowV]) {
                            visited[nowV] = true;
                            ++res;
                        }
                    }

                    ans = max(ans, res);
                }
            }
        }
        return ;
    }

    if (mat[now] == -1) {
        solve(mat, coor, now+1, ans);

        for (int i = now+1; i < N; ++i) {
            mat[now] = i;
            mat[i] = now;

            solve(mat, coor, now+1, ans);

            mat[now] = -1;
            mat[i] = -1;
        }
    } else {
        solve(mat, coor, now+1, ans);
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        int ans = 1; // at least touch one

        VVLL coor;
        VI mat(N, -1);

        for (int i = 0; i < N; ++i) {
            VLL c(2);
            cin >> c[0] >> c[1];
            coor.push_back(c);
        }

        solve(mat, coor, 0, ans);

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
