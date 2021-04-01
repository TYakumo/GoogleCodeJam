#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
#include <random>
#include <sstream>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VC = vector <char>;

const int UPPER = 10000;

void genRnd(long long UP, VVI& pattern, VVI& pattern2) {
    random_device seed_gen;
    mt19937_64 engine(seed_gen());

    unordered_map <char, int> cnt;
    unordered_map <int, int> leCnt;
    for (int i = 0; i < UPPER; ++i) {
        stringstream ss;
        string v;
        string v2;
        long long rndVal = (engine()%UP) + 1;
        long long rndVal2 = (engine()%rndVal) + 1;

        ss << rndVal << " " << rndVal2;
        ss >> v >> v2;

        if (v2.size() == 16) {
            ++leCnt[v2[0]-'0'];
        }

        for (int j = 0; j < v2.size(); ++j) {
            ++cnt[v2[j]];
        }
    }

    auto leIter = leCnt.begin();

    while (leIter != leCnt.end()) {
        pattern.push_back({leIter->second, leIter->first});
        ++leIter;
    }
    sort(pattern.begin(), pattern.end());

    auto iter = cnt.begin();
    while (iter != cnt.end()) {
        pattern2.push_back({iter->second, iter->first-'0'});
        ++iter;
    }
    sort(pattern2.begin(), pattern2.end());

    // for (int i = 0; i < pattern.size(); ++i) {
    //     cout << pattern[i][1] << " " << pattern[i][0] << endl;
    // }

    // for (int i = 0; i < pattern2.size(); ++i) {
    //     cout << pattern2[i][1] << " " << pattern2[i][0] << endl;
    // }
}

int main()
{
    VVI pattern;
    VVI pattern2;
    genRnd(100000000LL*100000000LL-1, pattern, pattern2);

    int TC;
    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int U;
        cin >> U;
        string D;
        string S;

        unordered_map <char, int> cnt;
        VVI notLink(26, VI(10));
        VI appear(26);
        int tot = 0;

        for (int i = 0; i < UPPER; ++i) {
            cin >> D >> S;

            if (S.size() == 16) {
                ++cnt[S[0]];
            }

            for (int j = 0; j < S.size(); ++j) {
                appear[S[j]-'A'] = 1;
            }

            if (D[0] != '-' && D.size() == S.size()) {
                ++tot;
                for (int j = D[0]-'0'+1; j < 10; ++j) {
                    notLink[S[0]-'A'][j] = 1;
                }
            }

            if (S.size() != 1) {
                notLink[S[0]-'A'][0] = 1;
            }
        }

        auto iter = cnt.begin();
        VVI cho;
        while (iter != cnt.end()) {
            cho.push_back({iter->second, iter->first});
            ++iter;
        }

        sort(cho.begin(), cho.end());
        VC ans(10, -1);
        VI used(26);

        if (U == 16) {
            int cnt = 1;
            for (int i = cho.size()-1; i >= 0; --i) {
                ans[cnt] = cho[i][1];
                used[cho[i][1]-'A'] = 1;
                ++cnt;
            }
        }

        for (int j = 0; j < 26; ++j) {
            if (notLink[j][0] == 0 && appear[j] && used[j] == 0) {
                used[j] = 1;
                ans[0] = j + 'A';
                break;
            }
        }

        for (int i = 9; i >= 0; --i) {
            if (ans[i] == -1) {
                for (int j = 0; j < 26; ++j) {
                    if (notLink[j][i] == 0 && appear[j] && used[j] == 0) {
                        used[j] = 1;
                        ans[i] = j + 'A';
                        break;
                    }
                }
            }
        }

        string res;
        for (int i = 0; i < ans.size(); ++i) {
            res += ans[i];
        }

        cout << "Case #" << tc << ": " << res << endl;
    }

    return 0;
}
