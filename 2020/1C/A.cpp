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

pair <int, int> dir(char ch) {
    switch (ch) {
        case 'N': return {0, 1};
        case 'S': return {0, -1};
        case 'E': return {1, 0};
        default: return {-1, 0};
    }
}

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
        int ans = INF;

        for (int i = 0; i < S.size(); ++i) {
            pair <int, int> d = dir(S[i]);
            X += d.first;
            Y += d.second;

            if (i+1 >= abs(X)+abs(Y)) {
                ans = i+1;
                break;
            }
        }

        if (ans == INF) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << tc << ": " << ans << endl;
        }


    }

    return 0;
}
