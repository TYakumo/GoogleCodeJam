#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;
        vector < pair<int, int> > tasks(N);
        vector <int> tasksAssignee(N);
        vector < vector<int> > pnts;

        for (int i = 0; i < N; ++i) {
            cin >> tasks[i].first >> tasks[i].second;
            pnts.push_back({tasks[i].first, 0, i});
            pnts.push_back({tasks[i].second, -1, i});
        }

        sort(pnts.begin(), pnts.end());
        bool failed = false;
        bool ok[2] = {true, true};
        string ans;

        for (int i = 0; i < pnts.size(); ++i) {
            if (pnts[i][1] == 0) {
                int cho = -1;

                for (int j = 0; j < 2; ++j) {
                    if (ok[j]) {
                        cho = j;
                        break;
                    }
                }

                if (cho != -1) {
                    tasksAssignee[pnts[i][2]] = cho;
                    ok[cho] = false;
                } else {
                    failed = true;
                    break;
                }
            } else {
                // free corresponding
                int cho = tasksAssignee[pnts[i][2]];
                ok[cho] = true;
            }
        }

        if (failed) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            for (int i = 0; i < N; ++i) {
                ans += (tasksAssignee[i] ? "J" : "C");
            }
            cout << "Case #" << tc << ": " << ans << endl;
        }

    }

    return 0;
}
