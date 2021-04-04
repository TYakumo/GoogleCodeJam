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
using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using UMLL = unordered_map<long long, int>;

long long toState(int r, int c, int state) {
    long long ret = r*(1LL<<40) + c * (1LL<<32) + state;
    return ret;
}

void solve(UMLL& used, VVI& step, VVI& ans, int r, int c, int R, int C, int state) {
    int target = (1<<(R*C)) - 1;
    long long ustate = toState(r, c, state);

    used[ustate] = 1;

    if (ans.size()) {
        return ;
    }

    if (state == target) {
        ans = step;
        return ;
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            int offset = i*C + j;
            int st = 1 << offset;

            if (i != r && j != c
            && i+j != r+c && i-j != r-c
            && (state&st) == 0) {
                int newst = state | st;
                long long newust = toState(i, j, newst);

                if (used[newst] == 0) {
                    step.push_back({i, j});
                    solve(used, step, ans, i, j, R, C, newst);
                    step.pop_back();
                }
            }
        }
    }
}

void getAns(VVI& ans, int R, int C) {
    int UPPER = 1<<(R*C);
    VVI steps;
    UMLL used;

    for (int i = 0; i < R && ans.empty(); ++i) {
        for (int j = 0; j < C && ans.empty(); ++j) {
            int st = 1<<(i*C+j);
            long long ust = toState(i, j, st);

            if (used[ust] == 0) {
                steps.push_back({i, j});
                solve(used, steps, ans, i, j, R, C, st);
                steps.pop_back();
            }
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    VVVI comb2(21);
    VVVI comb3(21);

    //(2, 5) => (2,5) ~ (2,9)
    for (int c = 5; c <= 9; ++c) {
        VVI ans;
        getAns(ans, 2, c);
        comb2[c] = ans;
    }

    for (int c = 10; c <= 20; ++c) {
        int r = c-c/2;
        VVI cur = comb2[c/2];
        comb2[c] = comb2[r];

        reverse(cur.begin(), cur.end());
        int offset = r;
        for (int j = 0; j < cur.size(); ++j) {
            cur[j][0] = 1-cur[j][0];
            cur[j][1] += offset;
            comb2[c].push_back({cur[j][0], cur[j][1]});
        }
    }

    //(3, 4) => (3,4) ~ (3,7)
    for (int c = 4; c <= 7; ++c) {
        VVI ans;
        getAns(ans, 3, c);
        comb3[c] = ans;
    }

    for (int c = 8; c <= 20; ++c) {
        int r = c-c/2;
        VVI cur = comb3[c/2];
        comb3[c] = comb3[r];

        reverse(cur.begin(), cur.end());
        int offset = r;
        for (int j = 0; j < cur.size(); ++j) {
            cur[j][0] = 2-cur[j][0];
            cur[j][1] += offset;
            comb3[c].push_back({cur[j][0], cur[j][1]});
        }
    }

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        int C;
        bool changed = false;

        cin >> R >> C;

        if (R > C) {
            swap(R, C);
            changed = true;
        }

        VVI ans;

        if (R >= 5) {
            if (R%2 == 0) {
                for (int i = 0; i < R/2; ++i) {
                    for (int j = 0; j < comb2[C].size(); ++j) {
                        VI now = comb2[C][j];
                        ans.push_back({now[0]+i*2, now[1]});
                    }
                }
            } else {
                for (int i = 0; i < R/2-1; ++i) {
                    for (int j = 0; j < comb2[C].size(); ++j) {
                        VI now = comb2[C][j];
                        ans.push_back({now[0]+i*2, now[1]});
                    }
                }

                int offset = 2*(R/2-1);
                for (int j = 0; j < comb3[C].size(); ++j) {
                    VI now = comb3[C][j];
                    ans.push_back({now[0]+offset, now[1]});
                }
            }
        } else if (R == 4) {
            if (C == 4) {
                getAns(ans, R, C);
            } else if (C >= 5) {
                for (int i = 0; i < R/2; ++i) {
                    for (int j = 0; j < comb2[C].size(); ++j) {
                        VI now = comb2[C][j];
                        ans.push_back({now[0]+i*2, now[1]});
                    }
                }
            }
        } else if (R == 2 && C >= 5) {
            ans = comb2[C];
        } else if (R == 3 && C >= 4) {
            ans = comb3[C];
        }

        if (changed) {
            for (int i = 0; i < ans.size(); ++i) {
                swap(ans[i][0], ans[i][1]);
            }
        }

        if (ans.size()) {
            cout << "Case #" << tc << ": POSSIBLE" << endl;
            for (int i = 0; i < ans.size(); ++i) {
                cout << ans[i][0]+1 << " " << ans[i][1]+1 << endl;
            }
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
