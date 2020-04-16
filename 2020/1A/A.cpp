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
        vector <string> str(N);
        vector <bool> used(N);
        vector <string> prefix(N);
        vector <string> suffix(N);
        vector<vector <string>> middle(N);

        int cho = -1;

        for (int i = 0; i < N; ++i) {
            cin >> str[i];

            string s;
            bool first = true;

            prefix.push_back(s);

            for (int j = 0; j < str[i].size(); ++j) {
                if (str[i][j] == '*') {
                    if (first) {
                        prefix[i] = s;
                    } else {
                        middle[i].push_back(s);
                    }

                    first = false;
                    s = "";
                } else {
                    s += str[i][j];
                }
            }

            suffix[i] = s;
        }

        bool ok = true;
        string ans;

        // prefix check
        cho = -1;
        for (int i = 0; i < N; ++i) {
            if (cho == -1 || prefix[i].size() > prefix[cho].size()) {
                cho = i;
            }
        }

        ans += prefix[cho];

        for (int i = 0; i < N && ok; ++i) {
            for (int j = 0; j < prefix[i].size(); ++j) {
                if (prefix[i][j] != prefix[cho][j]) {
                    ok = false;
                    break;
                }
            }
        }

        // middle
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < middle[i].size(); ++j) {
                ans += middle[i][j];
            }
        }

        // suffix check
        cho = -1;
        for (int i = 0; i < N; ++i) {
            if (cho == -1 || suffix[i].size() > suffix[cho].size()) {
                cho = i;
            }
        }

        ans += suffix[cho];

        for (int i = 0; i < N && ok; ++i) {
            int lenDiff = suffix[cho].size() - suffix[i].size();
            for (int j = 0; j < suffix[i].size(); ++j) {
                if (suffix[i][j] != suffix[cho][j+lenDiff]) {
                    ok = false;
                    break;
                }
            }
        }

        cout << "Case #" << tc << ": " << (ok ? ans : "*") << endl;
    }

    return 0;
}
