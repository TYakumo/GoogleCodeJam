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

int main()
{
    int TC;
    int F;
    VI fact(6);
    fact[0] = 1;

    for (int i = 1; i <= 5; ++i) {
        fact[i] = fact[i-1]*i;
    }

    cin >> TC >> F;

    for (int tc = 1; tc <= TC; tc++) {
        const int UPPER = 120;

        VI cand;
        VI used(5);
        string ans;

        for (int i = 0; i < UPPER-1; ++i) {
            cand.push_back(i*5);
        }

        for (int offset = 0; offset < 5; ++offset) {
            VVI round(5);

            int target = fact[4-offset];

            for (int i = 0; i < cand.size(); ++i) {
                cout << (cand[i]+offset+1) << endl;
                flush(cout);

                string S;
                cin >> S;

                round[S[0]-'A'].push_back(cand[i]);
            }

            int cho = 0;
            cand.clear();

            for (int i = 0; i < 5; ++i) {
                if (round[i].size() != target && !used[i]) {
                    cho = i;
                    for (int j = 0; j < round[i].size(); ++j) {
                        cand.push_back(round[i][j]);
                    }
                }
            }

            ans += (cho+'A');
            used[cho] = 1;
        }

        cout << ans << endl;
        string V;
        cin >> V;

        if (V == "N") {
            break;
        }
    }

    return 0;
}
