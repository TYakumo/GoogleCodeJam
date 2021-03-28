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
using DI = deque <int>;

DI construct(int N, int C, int MAXN) {
    if (N == MAXN) {
        return {N};
    }

    int curNum = (MAXN-N+1);

    int nextSum = curNum*(curNum-1)/2;
    DI num;

    if (C-1 <= nextSum) {
        num = construct(N+1, C-1, MAXN);
        num.push_front(N);
    } else {
        num = construct(N+1, C-curNum, MAXN);
        reverse(num.begin(), num.end());
        num.push_back(N);
    }

    return num;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int C;
        cin >> N >> C;

        // N = 4
        // F(1) = 0
        // max F(N) = F(N-1) + N
        // max F(N) = N(N+1)/2-1
        // x y z 1
        // 1 z y x

        if (C > ((N+1)*N/2-1) || C < (N-1)) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            DI num = construct(1, C+1, N);

            cout << "Case #" << tc << ":";

            for (int i = 0; i < N; ++i) {
                cout << " " << num[i];
            }
            cout << endl;
        }
    }

    return 0;
}
