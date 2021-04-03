#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
using namespace std;

using MSI = unordered_map<string, int>;
using VS = vector <string>;
using VI = vector <int>;
using VVI = vector <VI>;
const int VTYPE = 0;
const int HTYPE = 1;
const int CHECKMODE = 0;
const int PUTMODE = 1;

bool handler(VS& colony, int ir, int ic, int type, int mode) {
    int R = colony.size();
    int C = colony[0].size();
    VS temp = colony;
    VS &handle = mode == CHECKMODE ? temp : colony;

    deque <VI> que;
    que.push_back({ir, ic});
    handle[ir][ic] = 'X';

    while (!que.empty()) {
        int r = que.front()[0];
        int c = que.front()[1];
        que.pop_front();
        int sign = 1;

        for (int d = 0; d < 2; ++d) {
            int nr = r;
            int nc = c;

            if (type == VTYPE) {
                nr += sign;
            } else {
                nc += sign;
            }

            if (nr >= 0 && nr < R
                && nc >= 0 && nc < C) {
                if (handle[nr][nc] == '#') {
                    return false;
                } else if (handle[nr][nc] == '.') {
                    handle[nr][nc] = 'X';
                    que.push_back({nr, nc});
                }
            }

            sign *= -1;
        }
    }

    return true;
}

int solve(int& ans, MSI& dp, VS colony, int turn, int init) {
    string str;
    // cout << "-----DEBUG------" << endl;
    for (int i = 0; i < colony.size(); ++i) {
        str += colony[i];
        // cout << colony[i] << endl;
    }

    // cout << "-----DEBUG END------" << endl;

    if (dp.count(str)) {
        return dp[str];
    }

    int res = 0;
    int R = colony.size();
    int C = colony[0].size();

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (colony[r][c] == '.') {
                // put V
                if (handler(colony, r, c, VTYPE, CHECKMODE)) {
                    VS newcolony = colony;
                    handler(newcolony, r, c, VTYPE, PUTMODE);

                    if (solve(ans, dp, newcolony, turn^1, 0) == 0) {
                        if (init) {
                            res = 1;
                            ++ans;
                        } else {
                            return dp[str] = 1;
                        }
                    }
                }

                // put H
                if (handler(colony, r, c, HTYPE, CHECKMODE)) {
                    VS newcolony = colony;
                    handler(newcolony, r, c, HTYPE, PUTMODE);

                    if (solve(ans, dp, newcolony, turn^1, 0) == 0) {
                        if (init) {
                            res = 1;
                            ++ans;
                        } else {
                            return dp[str] = 1;
                        }
                    }
                }
            }
        }
    }

    return dp[str] = res;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        int C;
        cin >> R >> C;

        VS colony(R);
        for (int i = 0; i < R; ++i) {
            cin >> colony[i];
        }

        MSI dp;
        int ans = 0;
        solve(ans, dp, colony, 0, 1);


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
