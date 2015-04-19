#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 10010;
int num[MAXN];

int main()
{
    int TC;
    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; ++tc) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &num[i]);
        }

        int total[2] = {0, 0}, maxD = 0;

        for (int i = 1; i < N; ++i) {
            if (num[i] < num[i-1]) {
                total[0] += num[i-1]-num[i];
                maxD = max(maxD, (num[i-1]-num[i]));
            }
        }

        for (int i = 1; i < N; ++i) {
           total[1] += min(num[i-1], maxD);
        }

        printf("Case #%d: %d %d\n", tc, total[0], total[1]);
    }
    return 0;
}