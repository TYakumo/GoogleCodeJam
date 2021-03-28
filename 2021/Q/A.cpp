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

bool checkSorted(const VI& num) {
    for (int i = 1; i < num.size(); ++i) {
        if (num[i] < num[i-1]) {
            return false;
        }
    }

    return true;
}

int main() {
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VI num(N);
        for (int i = 0; i < N; ++i) {
            cin >> num[i];
        }

        int ans = 0;
        for (int i = 0; i < N-1; ++i) {
            int minIdx = i;
            for (int j = i+1; j < N; ++j) {
                if (num[j] < num[minIdx]) {
                    minIdx = j;
                }
            }

            ans += (minIdx-i+1);
            reverse(num.begin()+i, num.begin()+minIdx+1);
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
