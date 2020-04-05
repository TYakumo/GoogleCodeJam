#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        vector < vector <int> > mat(N, vector<int>(N));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> mat[i][j];
            }
        }

        vector< unordered_map <int, int> > rowCnt(N);
        vector< unordered_map <int, int> > colCnt(N);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ++rowCnt[i][mat[i][j]];
                ++colCnt[j][mat[i][j]];
            }
        }

        int r = 0;
        int c = 0;
        int trace = 0;

        for (int i = 0; i < N; ++i) {
            trace += mat[i][i];

            auto iter = rowCnt[i].begin();

            while (iter != rowCnt[i].end()) {
                if (iter->second > 1) {
                    ++r;
                    break;
                }
                ++iter;
            }

            iter = colCnt[i].begin();

            while (iter != colCnt[i].end()) {
                if (iter->second > 1) {
                    ++c;
                    break;
                }
                ++iter;
            }
        }

        cout << "Case #" << tc << ": " << trace << " " << r << " " << c << endl;
    }

    return 0;
}
