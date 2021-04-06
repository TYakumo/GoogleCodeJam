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
#include <sstream>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VS = vector <string>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VS S(N);
        for (int i = 0; i < N; ++i) {
            cin >> S[i];
        }

        unordered_map <string, int> strMap;
        VVI cho;
        VI used(N);

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                int minLen = min(S[i].size(), S[j].size());
                int common = 0;

                for (int k = 0; k < minLen; ++k) {
                    if (S[i][S[i].size()-1-k] == S[j][S[j].size()-1-k]) {
                        ++common;
                    } else {
                        break;
                    }
                }

                if (common > 0) {
                    cho.push_back({-common, i, j});
                }
            }
        }

        sort(cho.begin(), cho.end());
        int ans = 0;

        for (int i = 0; i < cho.size(); ++i) {
            int fir = cho[i][1];
            int sec = cho[i][2];
            int len = -cho[i][0];

            if (used[fir] == 0 && used[sec] == 0) {
                string choStr;
                for (int k = 0; k < len; ++k) {
                    choStr += S[sec][S[sec].size()-1-k];
                }

                reverse(choStr.begin(), choStr.end());
                while (choStr.size() > 1 && strMap.count(choStr)) {
                    choStr = choStr.substr(1, choStr.size()-1);
                }

                if (strMap.count(choStr) == 0) {
                    strMap[choStr] = 1;
                    used[fir] = used[sec] = 1;
                    ans += 2;
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
