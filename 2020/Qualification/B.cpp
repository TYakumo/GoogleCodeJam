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
        vector <char> ans;
        string s;

        cin >> s;
        int lcnt = 0;

        for (int i = 0; i < s.size(); ++i) {
            while (s[i]-'0' > lcnt) {
                ++lcnt;
                ans.emplace_back('(');
            }

            while (s[i]-'0' < lcnt) {
                --lcnt;
                ans.emplace_back(')');
            }

            ans.push_back(s[i]);
        }

        while (lcnt) {
            --lcnt;
            ans.emplace_back(')');
        }

        string res;
        for (int i = 0; i < ans.size(); ++i) {
            res += ans[i];
        }

        cout << "Case #" << tc << ": " << res << endl;
    }

    return 0;
}
