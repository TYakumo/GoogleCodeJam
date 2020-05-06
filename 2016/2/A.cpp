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

inline char intToChar(int v) {
    switch(v) {
        case 0:
            return 'R';
        case 1:
            return 'P';
        default:
            return 'S';
    }
}

void genResult(int now, int level, int pos, vector<char>& str, vector<int>& needed) {
    if (level == 0) {
        str[pos] = intToChar(now);
        ++needed[now];
        return ;
    }

    if (now == 0) { // rock => rock + scissor
        genResult(0, level-1, pos, str, needed);
        genResult(2, level-1, pos+(1<<(level-1)), str, needed);
    } else if (now == 1) { // paper => paper + rock
        genResult(0, level-1, pos, str, needed);
        genResult(1, level-1, pos+(1<<(level-1)), str, needed);
    } else { // scissor => scissor + paper
        genResult(1, level-1, pos, str, needed);
        genResult(2, level-1, pos+(1<<(level-1)), str, needed);
    }
}

void sortString(string& str, int N) {
    for (int l = 0; l < N; ++l) {
        int dis = 1<<l;
        for (int i = 0; i < str.size(); i += 2*dis) {
            string l1 = str.substr(i, dis);
            string l2 = str.substr(i+dis, dis);

            if (l2 < l1) {
                for (int j = 0; j < dis; ++j) {
                    str[i+j] = l2[j];
                    str[i+dis+j] = l1[j];
                }
            }
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        vector<int> num(3);
        vector<int> needed(3);
        vector<char> str(1<<N);

        for (int i = 0; i < 3; ++i) {
            cin >> num[i];
        }

        string ans;

        for (int r = 0; r < 3; ++r) {
            fill(needed.begin(), needed.end(), 0);
            genResult(r, N, 0, str, needed);

            if (needed == num) {
                string res(str.begin(), str.end());
                sortString(res, N);
                if (ans == "" || res < ans) {
                    ans = res;
                }
            }
        }

        if (ans == "") {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << tc << ": " << ans << endl;
        }
    }

    return 0;
}
