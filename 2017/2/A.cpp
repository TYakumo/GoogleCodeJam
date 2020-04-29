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
using namespace std;

inline bool allZero(vector<int>& r) {
    for (int i = 0; i < r.size(); ++i) {
        if (r[i] != 0) {
            return false;
        }
    }

    return true;
}

inline long long getHash(vector<int>& r, int stale) {
    long long res = 0;
    const int SHIFT = 101;

    for (int i = 0; i < r.size(); ++i) {
        res = (res * SHIFT) + r[i];
    }
    res = (res * SHIFT) + stale;

    return res;
}

int solve(vector<int> r, int stale, unordered_map <long long, int>& ansMap) {
    int N = r.size();
    int P = r.size()+1;

    if (allZero(r)) {
        return 0;
    }

    long long hashNum = getHash(r, stale);

    if (ansMap.find(hashNum) != ansMap.end()) {
        return ansMap[hashNum];
    }

    int plus = stale == 0 ? 1 : 0;
    ansMap[hashNum] = 0;

    for (int i = 1; i <= N; ++i) {
        vector <int> newR(r);

        if (r[i-1] > 0) {
            --newR[i-1];
            int newStale = (stale - i + P) % P;

            ansMap[hashNum] = max(ansMap[hashNum], solve(newR, newStale, ansMap)+plus);
        }
    }

    return ansMap[hashNum];
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int P;
        int N;
        cin >> N >> P;
        vector <int> remain(P);
        unordered_map <long long, int> ansMap;

        for (int i = 0; i < N; ++i) {
            int num;
            cin >> num;
            ++remain[num%P];
        }

        int ans = remain[0];

        vector <int> r(P-1);
        for (int i = 1; i < P; ++i) {
            r[i-1] = remain[i];
        }

        ans += solve(r, 0, ansMap);

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
