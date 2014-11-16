#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110, MAXL = 110;
int len[MAXN], rlen[MAXN], startp[MAXN][MAXL];
char str[MAXN][MAXL], reduced[MAXN][MAXL];

int main()
{
    int TC, N;

    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; tc++) {

        scanf("%d", &N);

        for (int i = 0; i < N; i++) {
            scanf("%s", str[i]);
            len[i] = strlen( str[i]);
            rlen[i] = 0;
            char prec = -1;
            for (int j = 0; j < len[i]; j++) {
                if (prec != str[i][j]) {
                    startp[i][rlen[i]] = j;
                    reduced[i][rlen[i]++] = str[i][j];
                    prec = str[i][j];
                }
            }
        }

        bool chk = true;
        
        //checking pattern is the same
        for (int i = 1; i < N; i++) 
            if (rlen[i] != rlen[0]) {
                chk = false;
                break;
            }

        int cost = 0;
        if (chk) {
            //checking string patterns
            for (int i = 1; i < N; i++) {
                for (int j = 0; j < rlen[0]; j++) 
                    if (reduced[i][j] != reduced[0][j]) {
                        chk = false;
                        break;
                    }
               if (chk == false) break; 
            }
            
            if (chk) {
                for (int i = 0; i < N; i++)
                    startp[i][ rlen[0] ] = len[i];
            
                for (int j = 0; j < rlen[0]; j++) {
                    int centroid = 0;
                    int val[MAXN], cnt =0;
                
                    for (int i = 0; i < N; i++) {
                        val[cnt++] = (startp[i][j+1]-startp[i][j]);
                    }

                    sort(val, val+N);
                    centroid = val[N/2];
                    for (int i = 0; i < N; i++) {
                        cost += abs(val[i] - centroid);
                    }
                }
            }
        }
         
        if (chk) {
            printf("Case #%d: %d\n", tc, cost);
        }
        else {
            printf("Case #%d: Fegla Won\n", tc);
        }
    }

    return 0;
}
