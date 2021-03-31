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

const int XDIR = 0;
const int YDIR = 1;

char toChar(int sign, int XY) {
    if (sign == -1) {
        if (XY == XDIR) {
            return 'W';
        } else {
            return 'S';
        }
    } else {
        if (XY == XDIR) {
            return 'E';
        } else {
            return 'N';
        }
    }
}

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;

string solve(int X, int Y, int XSIGN, int YSIGN, bool& failed) {
    if (X == 0 && Y == 0) {
        return "";
    }

    if  (X%2 == Y%2) {
        failed = true;
        return "IMPOSSIBLE";
    } else {
        if (X%2) {
            int YN = Y&2;
            int XN = X&2;

            if ((XN && YN) || (YN == 0 && XN == 0 && (X/2 || Y/2))) {
                return toChar(XSIGN*-1, XDIR) + solve((X+1)/2, Y/2, XSIGN, YSIGN, failed);
            } else {
                return toChar(XSIGN, XDIR) + solve((X-1)/2, Y/2, XSIGN, YSIGN, failed);
            }
        } else {
            int YN = Y&2;
            int XN = X&2;

            if ((XN && YN) || (XN == 0 && YN == 0 && (X/2 || Y/2))) {
                return toChar(YSIGN*-1, YDIR) + solve(X/2,(Y+1)/2, XSIGN, YSIGN, failed);
            } else {
                return toChar(YSIGN, YDIR) + solve(X/2, (Y-1)/2, XSIGN, YSIGN, failed);
            }
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int X;
        int Y;
        cin >> X >> Y;

        int XSIGN = X < 0 ? -1 : 1;
        int YSIGN = Y < 0 ? -1 : 1;
        bool failed = false;
        string ans = solve(abs(X), abs(Y), XSIGN, YSIGN, failed);

        if (!failed && (X || Y)) {
            cout << "Case #" << tc << ": " << ans << endl;
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
