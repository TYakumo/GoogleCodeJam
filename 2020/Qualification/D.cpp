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
    int B;

    cin >> TC >> B;
    vector <int> ans(B);

    for (int tc = 1; tc <= TC; tc++) {
        int r = 0;
        int c = 0;

        // initialization run
        int undetermined = B;
        int target = 0;
        int choPair[2] = {0, 0};
        int cnt = 0;

        for (int t = 0; undetermined; ++t) {
            if (t%5 == 0 && cnt == 3) { //avoid excessive queries
                break;
            }

            if (t%5 == 0 && t) {
                // determine c or r
                int v;
                cout << 1 << endl;
                cin >> v;

                cout << 1 << endl; // just waste it
                cin >> v;

                if (v != ans[0]) {
                    c = 1; // c or r doesn't matter, but c works for both
                } else {
                    c = 0;
                }
            } else {
                int ct = target++;
                cout << ct+1 << endl;
                cin >> ans[ct];
                ans[ct] ^= c; // revert

                cout << (B-ct) << endl;
                cin >> ans[B-ct-1];
                ans[B-ct-1] ^= c; // revert

                undetermined -= 2;

                if (ans[ct] != ans[B-ct-1]) {
                    choPair[0] = ct;
                    cnt |= 1;
                } else if (ans[ct] == ans[B-ct-1]) {
                    choPair[1] = ct;
                    cnt |= 2;
                }
            }
        }

        // dealing with effect
        // we need (2 + 8) * n >= undetermined
        // (100-10) / 8 => 12 times => 120 queries
        // 10 + 120 < 150

        while (undetermined > 0) {
            int rv[2];
            int ev[2] = {ans[choPair[0]], ans[choPair[1]]};

            cout << choPair[0]+1 << endl;
            cin >> rv[0];

            cout << choPair[1]+1 << endl;
            cin >> rv[1];

            if (rv[1] != ev[1]) {
                c = 1;
            } else {
                c = 0;
            }

            r = 0;

            if ((c == 1 && rv[0] == ev[0])
                || (c == 0 && rv[0] != ev[0])) {
                r = 1;
            }

            for (int i = 0; i < 8 && undetermined > 0; ++i) {
                int tmpv;
                int npos = target;

                if (r) {
                    npos = B-target-1;
                }

                cout << npos+1 << endl;
                cin >> tmpv;

                tmpv ^= c;

                ans[target++] = tmpv;
                --undetermined;
            }
        }

        string res;
        for (int i = 0; i < B; ++i) {
            int npos = r ? B-i-1 : i;
            res += ((ans[npos]^c) + '0');
        }

        cout << res << endl;

        string verdict;
        cin >> verdict;
        if (verdict == "N") {
            break;
        }
    }

    return 0;
}
