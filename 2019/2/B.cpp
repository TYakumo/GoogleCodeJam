#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

using VVI = vector< vector <int> >;
using VD = vector < double >;
const int MAXD = 100;
const int MAXV = 20;
const double expTokenTurn = 1.0 / MAXV;

void probeVase(int vaseNum, int day, VVI& vase, VD& expToken) {
    int dayRemain = MAXD - day;
    cout << (vaseNum+1) << " " << 0 << endl;

    int N;
    cin >> N;
    vase[vaseNum] = move(vector<int>(N));

    for (int i = 0; i < N; ++i) {
        cin >> vase[vaseNum][i];
    }

    expToken[vaseNum] = N + (expTokenTurn * dayRemain);
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {

        VVI vase(MAXV);
        VD expToken(MAXV); // expected tokens in the end, index

        int cho = -1;
        int prob = 0;
        int D;

        const int TARGETD = 13;
        int now = 0;

        // with 0.0005% that first TARGETD >= 7 tokens
        const int UPPER = TARGETD*6;
        for (int d = 1; d <= UPPER; ++d) {
            cin >> D;

            if (D == -1) {
                break;
            }

            // putting to
            cout << (now+1) << " " << 1 << endl;
            now = (now+1)%TARGETD;
        }

        // (MAXV - TARGETD) with average 5 tokens
        const int THRESHOLD = UPPER+1 + (MAXV - TARGETD);
        for (int d = UPPER+1; d < MAXD; ++d) {
            cin >> D;

            if (D == -1) {
                break;
            }

            // keep probing
            if (d <= THRESHOLD) {
                probeVase(prob+TARGETD, d, vase, expToken);
                prob = (prob+1) % (MAXV-TARGETD);
            } else {
                // put greedily against lowest target
                int target = -1;

                for (int i = TARGETD; i < MAXV; ++i) {
                    if (i != cho) {
                        if (target == -1 || expToken[i] < expToken[target]) {
                            target = i;
                        }
                    }
                }

                expToken[target] += 1;
                cout << (target+1) << " " << 1 << endl;
            }

            // select final target
            if (d == THRESHOLD) {
                int best = -1;

                for (int i = TARGETD; i < MAXV; ++i) {
                    if (best == -1 || expToken[i] < expToken[best]) {
                        best = i;
                    }
                }

                cho = best;
            }
        }

        // final put
        cin >> D;

        if (D == -1) {
            break;
        }
        cout << (cho+1) << " " << 100 << endl;
    }

    return 0;
}
