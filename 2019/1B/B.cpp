#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

const long long MOD = 1LL << 63;

int main()
{
    int TC;
    int W;

    cin >> TC >> W;

    for (int tc = 1; tc <= TC; tc++) {
        vector <long long> ans(6);
        // 100 < 2^7 = 128
        // n/3-n/4 >= 7 => 4n-3n >= 84
        // day 56 => 2^56 R1 + 2^28 R2 + 2^18 R3 + 2^14 R4 +2^11 R5 + 2^9 R6
        long long cho = 56;
        long long v;

        cout << cho << endl;
        cin >> v;

        ans[0] = v / (1LL<<cho);
        v %= (1LL<<cho);

        ans[1] = v / (1LL<<(cho/2));
        v -= ans[1] * (1LL<<(cho/2));

        long long vRemain = v;
        // vRemain = 2^18 R3 + 2^14 R4 +2^11 R5 + 2^9 R6

        // n/4-n/5 >= 7 => n >= 140
        // n/3 >= 63 => n >= 189
        cho = 195;
        cout << cho << endl;
        cin >> v;

        ans[3] = v / (1LL<<(cho/4));
        v %= (1LL<<(cho/4));

        ans[4] = v / (1LL<<(cho/5));
        v -= ans[4] * (1LL<<(cho/5));

        // solve ans[2]
        vRemain -= ans[3]*(1LL<<14);
        vRemain -= ans[4]*(1LL<<11);

        ans[2] = vRemain / (1LL<<18);
        vRemain -= ans[2] * (1LL<<18);

        ans[5] = vRemain / (1LL<<9);

        cout << ans[0];
        for (int i = 1; i < 6; ++i) {
            cout << " " << ans[i];
        }
        cout << endl;

        // judge
        int verdict;
        cin >> verdict;

        if (verdict == -1) {
            break;
        }
    }

    return 0;
}
