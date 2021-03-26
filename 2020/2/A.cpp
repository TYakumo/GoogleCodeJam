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

long long upperBound(long long d) {
    // c(c+1)/2 <= d
    const long long INF = 2000000000LL;
    long long ret = 0;
    long long low = 0;
    long long up = INF;

    while (low <= up) {
        long long mid = (low+up) / 2;

        if (mid*(mid+1) <= 2*d) {
            ret = mid;
            low = mid+1;
        } else {
            up = mid-1;
        }
    }

    return ret;
}

long long getSum(long long st, long long len, long long diff) {
    return ((st + (st + (len-1)*diff)) * len) / 2;
}

vector <long long> getCost(long long st, long long len) {
    vector <long long> res(2);

    long long l[2] = {(len+1)/2, 0};
    l[1] = len-l[0];

    res[0] = getSum(st, l[0], 2);
    res[1] = getSum(st+1, l[1], 2);

    return res;
}

long long solve(long long st, long long& L, long long& R) {
    const long long UPPER = 2000000010LL;
    long long low = 1;
    long long up = UPPER;
    long long ans = 0;

    while (low <= up) {
        long long mid = (low+up) / 2;
        vector <long long> res = getCost(st, mid);

        if (res[0] <= L && res[1] <= R) {
            ans = mid;
            low = mid+1;
        } else {
            up = mid-1;
        }
    }

    vector <long long> res = getCost(st, ans);
    L -= res[0];
    R -= res[1];

    return ans;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        long long L;
        long long R;
        bool sw = false;
        cin >> L >> R;

        if (L < R) {
            swap(L, R);
            sw = true;
        }

        long long cnt = 0;
        long long diff = (L-R);

        cnt = upperBound(diff);
        L -= (cnt*(cnt+1)) / 2;
        ++cnt;

        if (L == R) { // cancelling
            sw = false;
        }

        cnt += solve(cnt, L, R);

        if (sw) {
            swap(L, R);
        }

        cout << "Case #" << tc << ": " << (cnt-1) << " " << L << " " << R << endl;
    }

    return 0;
}
