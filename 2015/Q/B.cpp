#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 10100;
int plate[MAXN];

int main()
{
    int TC;
    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; ++tc) {
        int N;
        scanf("%d", &N);
        int ans = 0, res = 0, sm = 0;

        for (int i = 0; i < N; ++i) {
            scanf("%d", &plate[i]);
            ans = max(ans, plate[i]);
        }

        for (int maxp = ans; maxp >= 1; --maxp) {
            res = 0;
            sm = 0;
            for (int i = 0; i < N; ++i) {
                int mul = (plate[i]+maxp-1)/maxp;
                sm += mul-1;
            }
            res = maxp+sm;
            ans = min(ans, res);
        }

        printf("Case #%d: %d\n", tc, ans);
    }
    return 0;
}