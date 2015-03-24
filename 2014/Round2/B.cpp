#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
int num[MAXN], oriValue[MAXN];
map <int, int> numPos;

int main()
{
    int TC, N;
    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; ++tc) {
        int leftBound = 0, rightBound;

        scanf("%d", &N);
        numPos.clear();

        rightBound = N-1;

        for (int i = 0; i < N; i++) {
            scanf("%d", &oriValue[i]);
            num[i] = oriValue[i];
            numPos[ num[i] ] = i;
        }

        sort(num, num+N);

        int result = 0;
        for (int i = 0; i < N; i++) {
            int curPos = numPos[ num[i] ];
            int cost[2] = { curPos-leftBound, rightBound-curPos };
            if (cost[0] <= cost[1]) {
                result += cost[0];
                //simulation
                while (curPos > leftBound) {
                    swap(oriValue[curPos], oriValue[curPos-1]);
                    ++numPos[ oriValue[curPos] ];
                    --curPos;
                }
                ++leftBound;
            }
            else {
                result += cost[1];
                //simulation
                while (curPos < rightBound) {
                    swap(oriValue[curPos], oriValue[curPos+1]);
                    --numPos[ oriValue[curPos] ];
                    ++curPos;
                }
                --rightBound;
            }
        }
        printf("Case #%d: %d\n", tc, result);
    }
    return 0;
}
