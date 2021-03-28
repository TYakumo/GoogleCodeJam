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

VI solveOrder(VI now, int globalPivot, int LorR) {
    if (now.size() <= 1) {
        return now;
    }

    VI left;
    VI middle;
    VI right;
    int pivot = now.size()/2;
    int pivot1 = 0;

    for (int i = 0; i < now.size(); ++i) {
        if (i != pivot && i != pivot1) {
            cout << now[pivot] << " " << now[pivot1] << " " << now[i] << endl;
            int r;
            cin >> r;

            if (r == now[pivot]) {
                right.push_back(now[i]);
            } else if (r == now[pivot1]) {
                left.push_back(now[i]);
            } else { // r == now[i]
                middle.push_back(now[i]);
            }
        }
    }

    left = solveOrder(left, now[pivot1], 0);
    middle = solveOrder(middle, now[pivot1], 1);
    right = solveOrder(right, now[pivot], 1);

    int reversed = 0;

    if (globalPivot != -1) {
        if (LorR == 0) {
            cout << globalPivot << " " << now[pivot1] << " " << now[pivot] << endl;

            int r;
            cin >> r;

            if (r == now[pivot1]) {
                reversed = 1;
            }
        } else {
            cout << globalPivot << " " << now[pivot1] << " " << now[pivot] << endl;

            int r;
            cin >> r;

            if (r == now[pivot]) {
                reversed = 1;
            }
        }
    }

    if (reversed) {
        swap(left, right);
        reverse(middle.begin(), middle.end());
        reverse(left.begin(), left.end());
        reverse(right.begin(), right.end());
        swap(pivot, pivot1);
    }

    left.push_back(now[pivot1]);

    for (int i = 0; i < middle.size(); ++i) {
        left.push_back(middle[i]);
    }
    left.push_back(now[pivot]);
    for (int i = 0; i < right.size(); ++i) {
        left.push_back(right[i]);
    }

    return left;
}

int main()
{
    int TC;
    int N;
    int Q;

    cin >> TC >> N >> Q;

    for (int tc = 1; tc <= TC; tc++) {
        VI ans(N);
        for (int i = 1; i <= N; ++i) {
            ans[i-1] = i;
        }

        ans = solveOrder(ans, -1, 0);

        for (int i = 0; i < N; ++i) {
            if (i) {
                cout << " ";
            }

            cout << ans[i];
        }

        cout << endl;
        flush(cout);

        int judge;
        cin >> judge;

        if (judge == -1) {
            cout << "-1" << endl;
            break;
        }
    }

    return 0;
}
