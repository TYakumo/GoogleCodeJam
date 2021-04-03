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

using VS = vector <string>;
using VI = vector <int>;

inline int toKind(char ch) {
    switch(ch) {
        case 'R': return 0;
        case 'S': return 1;
        default: return 2;
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int K = 0;
        cin >> N;

        while ((1<<K) < N+1) {
            ++K;
        }

        VS opponents(N);

        for (int i = 0; i < N; ++i) {
            cin >> opponents[i];
        }

        bool failed = false;
        string ans;
        VI won(opponents.size());
        int remain = opponents.size();

        while (remain > 0) {
            int idx = ans.size();
            VI kind(3); //R S P

            for (int i = 0; i < opponents.size(); ++i) {
                if (won[i] == 0) {
                    int slen = opponents[i].size();
                    kind[toKind(opponents[i][idx%slen])] = 1;
                }
            }

            int tot = kind[0] + kind[1] + kind[2];
            if (tot == 3) {
                failed = true;
                break;
            } else if (tot == 2) {
                if (kind[0] == 1) { //0, 1 or 0, 2
                    if (kind[1] == 1) {
                        ans += "R";
                        for (int i = 0; i < opponents.size(); ++i) {
                            if (won[i] == 0) {
                                int slen = opponents[i].size();
                                if (opponents[i][idx%slen] == 'S') {
                                    won[i] = 1;
                                    --remain;
                                }
                            }
                        }
                    } else {
                        ans += "P";
                        for (int i = 0; i < opponents.size(); ++i) {
                            if (won[i] == 0) {
                                int slen = opponents[i].size();
                                if (opponents[i][idx%slen] == 'R') {
                                    won[i] = 1;
                                    --remain;
                                }
                            }
                        }
                    }
                } else { // 1, 2
                    ans += "S";
                    for (int i = 0; i < opponents.size(); ++i) {
                        if (won[i] == 0) {
                            int slen = opponents[i].size();
                            if (opponents[i][idx%slen] == 'P') {
                                won[i] = 1;
                                --remain;
                            }
                        }
                    }
                }
            } else { // done
                if (kind[0] == 1) {
                    ans += "P";
                } else if (kind[1] == 1) {
                    ans += "R";
                } else {
                    ans += "S";
                }

                break;
            }
        }

        if (failed) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << tc << ": " << ans << endl;
        }


    }

    return 0;
}
