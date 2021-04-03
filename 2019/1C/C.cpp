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

using MSI = unordered_map<int, int>;
using VS = vector <string>;
using VI = vector <int>;
using VVI = vector <VI>;
const int VTYPE = 0;
const int HTYPE = 1;

inline int getAreaCnt(const VVI& precal, int sr, int er, int sc, int ec) {
    int ret = precal[er][ec];

    if  (sr-1 >= 0) {
        ret -= precal[sr-1][ec];
    }

    if (sc-1 >= 0) {
        ret -= precal[er][sc-1];
    }

    if (sr-1 >= 0 && sc-1 >= 0) {
        ret += precal[sr-1][sc-1];
    }

    return ret;
}

bool checkOK(const VVI& precal, int SR, int ER, int SC, int EC, int r, int c, int type) {
    if (type == VTYPE) {
        return getAreaCnt(precal, SR, ER, c, c) == 0;
    } else {
        return getAreaCnt(precal, r, r, SC, EC) == 0;
    }
}

int solve(int& ans, MSI& dp, const VVI& precal, int SR, int ER, int SC, int EC, int turn, int init) {
    if (SC > EC || SR > ER) {
        return 0;
    }

    int state = SR*(1LL<<16) + ER*(1LL<<8) + SC*(1LL<<4) + EC;

    if (dp.count(state)) {
        return dp[state];
    }

    VI child;

    int R = precal.size();
    int C = precal[0].size();

    for (int cr = SR; cr <= ER; ++cr) {
        if (checkOK(precal, SR, ER, SC, EC, cr, SC, HTYPE)) {
            int res1 = solve(ans, dp, precal, SR, cr-1, SC, EC, turn^1, 0);
            int res2 = solve(ans, dp, precal, cr+1, ER, SC, EC, turn^1, 0);

            if (init && (res1 ^ res2) == 0) {
                ans += (EC-SC+1);
            }

            child.push_back(res1^res2);
        }
    }

    for (int cc = SC; cc <= EC; ++cc) {
        if (checkOK(precal, SR, ER, SC, EC, SR, cc, VTYPE)) {
            int res1 = solve(ans, dp, precal, SR, ER, SC, cc-1, turn^1, 0);
            int res2 = solve(ans, dp, precal, SR, ER, cc+1, EC, turn^1, 0);

            if (init && (res1 ^ res2) == 0) {
                ans += (ER-SR+1);
            }

            child.push_back(res1^res2);
        }
    }

    sort(child.begin(), child.end());
    if (!child.empty() && child[0] != 0) {
        return dp[state] = 0;
    }

    for (int i = 1; i < child.size(); ++i) {
        if (child[i] > child[i-1]+1) {
            return dp[state] = child[i-1]+1;
        }
    }

    if (child.size()) {
        return dp[state] = child.back()+1;
    }

    return dp[state] = 0;
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
        VVI precal(R, VI(C));

        for (int i = 0; i < R; ++i) {
            cin >> colony[i];
        }

        for (int i = 0; i < R; ++i) {
            int acc = 0;
            for (int j = 0; j < C; ++j) {
                if (colony[i][j] == '#') {
                    ++acc;
                }

                precal[i][j] = acc;

                if (i) {
                    precal[i][j] += precal[i-1][j];
                }
            }
        }

        MSI dp;
        int ans = 0;
        solve(ans, dp, precal, 0, R-1, 0, C-1, 0, 1);

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
