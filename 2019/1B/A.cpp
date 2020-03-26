#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int findMaxHead(vector< pair<int,int> >& pnts) {
    int ans = 0;
    int maxCnt = 0;
    int lcnt = 0;

    sort(pnts.begin(), pnts.end());

    for (int i = 0; i < pnts.size(); ++i) {
        if (pnts[i].second == 0) {
            ++lcnt;
            if (lcnt > maxCnt) {
                maxCnt = lcnt;
                ans = pnts[i].first;
            }
        } else {
            --lcnt;
        }
    }

    return ans;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int P;
        int Q;
        cin >> P >> Q;

        vector< pair <int, int> > xline; //coor, endFlag
        vector< pair <int, int> > yline;

        for (int i = 0; i < P; ++i) {
            int px;
            int py;
            char dir;

            cin >> px >> py >> dir;

            if (dir == 'N' || dir == 'S') {
                if (dir == 'N') {
                    yline.emplace_back(make_pair(py+1, 0));
                    yline.emplace_back(make_pair(Q, 1));
                } else {
                    yline.emplace_back(make_pair(0, 0));
                    yline.emplace_back(make_pair(py-1, 1));
                }
            } else {
                if (dir == 'E') {
                    xline.emplace_back(make_pair(px+1, 0));
                    xline.emplace_back(make_pair(Q, 1));
                } else {
                    xline.emplace_back(make_pair(0, 0));
                    xline.emplace_back(make_pair(px-1, 1));
                }
            }
        }

        cout << "Case #" << tc << ": " << findMaxHead(xline) << " " << findMaxHead(yline) << endl;
    }

    return 0;
}
