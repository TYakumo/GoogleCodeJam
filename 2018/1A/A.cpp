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
using DI = deque <int>;

int getArea(const VVI& precal, int sr, int er, int sc, int ec) {
    int ret = precal[er][ec];

    if (sr-1 >= 0) {
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

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        int C;
        int H;
        int V;
        cin >> R >> C >> H >> V;

        VS cake(R);
        VVI precal(R, VI(C));
        int tot = 0;

        for (int i = 0; i < R; ++i) {
            cin >> cake[i];
            int acc = 0;

            for (int j = 0; j < C; ++j) {
                if (cake[i][j] == '@') {
                    ++acc;
                    ++tot;
                }

                precal[i][j] = acc;
                if (i > 0) {
                    precal[i][j] += precal[i-1][j];
                }
            }
        }

        bool ans = false;
        int diner = (V+1) * (H+1);
        int target = tot / diner;

        if (tot % diner == 0 && target != 0) {
            bool ok = true;
            VI hp;
            VI vp;

            int rowTarget = target * (V+1);
            hp.push_back(0);

            for (int r = 0; r < R && ok; ++r) {
                if (hp.size() == H+1) {
                    r = R-1;
                }

                if (getArea(precal, hp.back(), r, 0, C-1) >= rowTarget) {
                    if (getArea(precal, hp.back(), r, 0, C-1) == rowTarget) {
                        hp.push_back(r+1);
                    } else {
                        ok = false;
                        break;
                    }
                }
            }

            if (hp.back() != R || hp.size() != H+2) {
                ok = false;
            }

            vp.push_back(0);

            for (int c = 0; c < C && ok; ++c) {
                int eqCnt = 0;
                int greaterCnt = 0;

                if (vp.size() == V+1) {
                    c = C-1;
                }

                for (int i = 0; i < hp.size()-1; ++i) {
                    if (getArea(precal, hp[i], hp[i+1]-1, vp.back(), c) == target) {
                        ++eqCnt;
                    }

                    if (getArea(precal, hp[i], hp[i+1]-1, vp.back(), c) > target) {
                        ++greaterCnt;
                        break;
                    }
                }

                if (greaterCnt) {
                    ok = false;
                    break;
                }

                if (eqCnt == H+1) {
                    vp.push_back(c+1);
                }
            }

            if (vp.back() != C || vp.size() != V+2) {
                ok = false;
            }

            if (ok) {
                ans = true;
            }
        }

        if (tot == 0) {
            ans = true;
        }

        cout << "Case #" << tc << ": " << (ans ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }

    return 0;
}
