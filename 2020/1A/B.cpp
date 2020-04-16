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

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int remain;

        cin >> N;
        remain = N;

        cout << "Case #" << tc << ": "  << endl;

        vector <int> cho(31);
        int m = -1;

        for (int i = 30; i >= 0; --i) {
            int offset = m == -1 ? (i+1) : 0;

            if (N >= ((1<<i)-1)+offset) {
                N -= ((1<<i) - 1);
                N -= offset;
                m = i;
                cho[i] = 1;
            }
        }

        int dir = 1;
        int level = 31;
        for (int i = 0; i < 31 && remain > 0; ++i) {
            if (cho[i] == 1) {
                if (dir == 1) {
                    for (int j = 0; j <= i; ++j) {
                        cout << i+1 << " " << j+1 << endl;
                    }
                } else {
                    for (int j = i; j >= 0; --j) {
                        cout << i+1 << " " << j+1 << endl;
                    }
                }

                dir *= -1;
                remain -= (1<<i);
            } else {
                if (dir == 1) {
                    cout << i+1 << " " << 1 << endl;
                } else {
                    cout << i+1 << " " << i+1 << endl;
                }
                --remain;
            }
        }

        if (dir == -1) {
            while (remain > 0) {
                --remain;
                cout << level+1 << " " << level+1 << endl;
                level++;
            }
        } else {
            while (remain > 0) {
                --remain;
                cout << level+1 << " " << 1 << endl;
                level++;
            }
        }
    }

    return 0;
}
