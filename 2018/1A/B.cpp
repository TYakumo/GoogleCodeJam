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
#include <unordered_set>
#include <sstream>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        long long B;
        int C;
        cin >> R >> B >> C;

        VVLL cashier(C, VLL(3));

        for (int i = 0; i < C; ++i) {
            cin >> cashier[i][0] >> cashier[i][1] >> cashier[i][2];
        }

        long long low = 0;
        long long up = 8000000000LL * 1000000000LL;
        long long ans = up;

        while (low <= up) {
            long long mid = (low+up) / 2;

            VLL cover(C);

            for (int i = 0; i < C; ++i) {
                cover[i] = max(0LL, min(cashier[i][0], (mid-cashier[i][2])/cashier[i][1]));
            }

            long long tot = 0;

            sort(cover.begin(), cover.end(), greater<long long>());
            for (int i = 0; i < C && i < R && tot < B; ++i) {
                tot += cover[i];
            }

            if (tot >= B) {
                up = mid-1;
                ans = mid;
            } else {
                low = mid+1;
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
