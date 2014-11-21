#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
int fsize[MAXN], mat[MAXN];

int main()
{
    int TC, N, DSIZE;
    scanf("%d", &TC);

    for(int tc = 1; tc <= TC; ++tc)
    {
        scanf("%d%d", &N, &DSIZE);
        for(int i = 0; i < N; i++)
            scanf("%d", &fsize[i]);

        sort(fsize, fsize+N);
        int l = N-2, r = N-1, ans = 0;
        memset(mat, -1, sizeof(mat));
        for(int i = N-1; i >= 0; i--)
        {
            if(mat[i] != -1) continue;
            for(int j = i-1; j >= 0; j--)
                if(fsize[i] + fsize[j] <= DSIZE && mat[j] == -1)
                {
                    mat[i] = j;
                    mat[j] = i; 
                    break;
                }
        }        
        
        for(int i = 0; i < N; i++)
            if(mat[i] == -1 || i < mat[i])
                ++ans;
        printf("Case #%d: %d\n", tc, ans);
    }

    return 0;
}
