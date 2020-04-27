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

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int C;
        cin >> C;

        vector <int> nowSt(C);
        vector <int> finalSt(C);
        int sum = 0;
        for (int i = 0; i < C; ++i) {
            nowSt[i] = 1;
            cin >> finalSt[i];
            sum += finalSt[i];
        }

        vector<vector <char>> moves;
        bool failed = sum != C;

        while (!failed && finalSt != nowSt) {
            vector <char> dir(C, ' ');
            vector <int> needed(finalSt);

            for (int i = 0; i < C; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (dir[j] != ' ') {
                        continue;
                    }

                    // special case 1
                    if (j == 0 && i != 0) {
                        continue;
                    }
                    // special case 2
                    if (j == C-1 && i != C-1) {
                        continue;
                    }

                    if (needed[i] >= nowSt[j]) {
                        needed[i] -= nowSt[j];

                        if (j > i) {
                            dir[j] = '/';
                        } else if (j < i) {
                            dir[j] = '\\';
                        } else {
                            dir[j] = '.';
                        }
                    }

                    if (needed[i] == 0) {
                        break;
                    }
                }
            }

            for (int i = 0; i < C; ++i) {
                if (needed[i] > 0) {
                    failed = true;
                    break;
                }
            }

            vector <int> newSt(C);

            for (int i = 0; i < C; ++i) {
                if (dir[i] == '/') {
                    newSt[i-1] += nowSt[i];
                } else if (dir[i] == '\\') {
                    newSt[i+1] += nowSt[i];
                } else {
                    newSt[i] += nowSt[i];
                }
            }


            nowSt = newSt;
            moves.push_back(dir);
        }

        if (failed) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            moves.emplace_back(vector<char>(C, '.'));
            cout << "Case #" << tc << ": " << moves.size() << endl;

            for (int i = 0; i < moves.size(); ++i) {

                for (int j = 0; j < moves[i].size(); ++j) {
                    cout << moves[i][j] ;
                }
                cout << endl;
            }
        }
    }

    return 0;
}
