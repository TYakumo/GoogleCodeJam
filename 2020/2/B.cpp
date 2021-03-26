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
using VVI = vector <VI>;
using VVVI = vector <VVI>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int C;
        int D;

        cin >> C >> D;

        const int INF = 10001000;
        VI dist(C, INF);
        VI cost(D);
        VI timing(C);

        for (int i = 1; i < C; ++i) {
            cin >> timing[i];
            if (timing[i] > 0) {
                dist[i] = timing[i];
            }
        }

        dist[0] = 0;

        const int UPPER = 1200;
        for (int nowDist = 1; nowDist <= UPPER; ++nowDist) {
            int smaller = 0;

            for (int i = 0; i < C; ++i) {
                if (dist[i] < nowDist) {
                    ++smaller;
                }
            }

            for (int i = 0; i < C; ++i) {
                if (timing[i] == -smaller && dist[i] == INF) {
                    dist[i] = nowDist;
                }
            }
        }

        for (int i = 0; i < D; ++i) {
            int f;
            int t;

            cin >> f >> t;
            --f;
            --t;

            if (dist[f] < dist[t]) {
                cost[i] = dist[t] - dist[f];
            } else if (dist[t] < dist[f]) {
                cost[i] = dist[f] - dist[t];
            } else { // anyway
                cost[i] = 5566;
            }
        }


        cout << "Case #" << tc << ":";

        for (int i = 0; i < D; ++i) {
            cout << " " << cost[i] ;
        }

        cout << endl;
    }

    return 0;
}
