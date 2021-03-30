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

const int MAXV = 2*1000000000;
const int MAXCOOR = 1000000000;
const int XDIR = 0;
const int YDIR = 1;
using VI = vector <int>;

pair <int, int> askBoundary(int X, int Y, int coor, bool& pass) {
    int low = -MAXCOOR;
    int up = MAXCOOR;
    int minRet = MAXV;
    int maxRet = -MAXV;

    cout << X << " " << Y << endl;
    string res;
    cin >> res;

    if (res == "MISS") {
        return {minRet, maxRet};
    } else if (res == "CENTER") {
        pass = true;
        return {X, Y};
    }

    minRet = maxRet = coor == YDIR ? Y : X;
    up = coor == YDIR ? Y-1 : X-1;

    while (low <= up) {
        int mid = (low + up) / 2;
        int newX = coor == XDIR ? mid : X;
        int newY = coor == YDIR ? mid : Y;

        cout << newX << " " << newY << endl;
        string res;
        cin >> res;

        if (res == "MISS") {
            low = mid+1;
        } else if (res == "CENTER") {
            pass = true;
            return {X, Y};
        } else {
            minRet = mid;
            up = mid-1;
        }
    }

    low = coor == YDIR ? Y+1 : X+1;
    up = MAXCOOR;
    while (low <= up) {
        int mid = (low + up) / 2;
        int newX = coor == XDIR ? mid : X;
        int newY = coor == YDIR ? mid : Y;

        cout << newX << " " << newY << endl;
        string res;
        cin >> res;

        if (res == "MISS") {
            up = mid-1;
        } else if (res == "CENTER") {
            pass = true;
            return {X, Y};
        } else {
            maxRet = mid;
            low = mid+1;
        }
    }

    return {minRet, maxRet};
}

int main()
{
    int TC;
    int A;
    int B;

    cin >> TC >> A >> B;

    for (int tc = 1; tc <= TC; tc++) {
        bool pass = false;
        VI candX = {0, MAXCOOR/2, -MAXCOOR/2, MAXCOOR/2, -MAXCOOR/2, 0, MAXCOOR/2, 0, -MAXCOOR/2};
        VI candY = {0, MAXCOOR/2, MAXCOOR/2, -MAXCOOR/2, -MAXCOOR/2, MAXCOOR/2, 0, -MAXCOOR/2, 0};

        for (int i = 0; i < candX.size() && !pass; ++i) {
            auto res = askBoundary(candX[i], candY[i], YDIR, pass);
            if (res.first == MAXV) {
                continue;
            }

            int CY = (res.first + res.second) / 2;
            if (!pass) {
                auto resX = askBoundary(candX[i], CY, XDIR, pass);
                int CX = (resX.first + resX.second) / 2;

                if (!pass) {
                    cout << CX << " " << CY << endl;
                    string S;
                    cin >> S;
                    pass = true;
                    break;

                    if (S == "WRONG") {
                        break;
                    }
                }
             }
        }


    }

    return 0;
}
