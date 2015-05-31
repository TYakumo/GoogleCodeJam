#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

const int MAXR = 110, MAXC = 110, INF = 10000000;
const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1}; //down up, right, left
char oriGrid[MAXR][MAXC];
int used[MAXR][MAXC];
int TC, R, C;

int decodeD(char c)
{
    switch(c)
    {
        case 'v': return 0;
        case '^': return 1;
        case '>': return 2;
        case '<': return 3;
        default: return 0;
    }
}

bool valid(int r, int c)
{
    return r >= 0 && r < R && c >= 0 && c < C;
}

int main()
{
    cin >> TC;

    for (int tc = 1; tc <= TC; ++tc) {
        cin >> R >> C;
        memset(used, 0, sizeof(used));
        for (int r = 0; r < R; ++r) {
            cin >> oriGrid[r];
        }

        int ans = 0;
        for(int r = 0; r < R && ans != INF; ++r)
            for(int c = 0; c < C; ++c)
                if (oriGrid[r][c] != '.') {
                    bool ok = false;
                    for(int d = 0; d < 4 && !ok; ++d)
                    {
                        int dir = ( decodeD(oriGrid[r][c])+d ) % 4;
                        int newr = r+dr[dir], newc = c+dc[dir];
                        while(valid(newr, newc)) {
                            if(oriGrid[newr][newc] != '.') {
                                ok = true;
                                if (d) ++ans;
                                break;
                            }
                            newr = newr+dr[dir], newc = newc+dc[dir];
                        }
                    }
                    if (!ok) {
                        ans = INF;
                        break;
                    }
              }

        if(ans == INF) {
            printf("Case #%d: IMPOSSIBLE\n", tc);
        }
        else { 
            printf("Case #%d: %d\n", tc, ans);
        }
    }
}
