#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXB = 1010;
long long btime[MAXB];

int main()
{
    int TC;
    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; ++tc) {
        int B, N;
        scanf("%d%d", &B, &N);
        for (int b = 0; b < B; ++b) {
            scanf("%lld", &btime[b]);
        }

        long long low = 0, up = 100000LL * N, mid, ans = 0, ansnum = 0, totalServed = 0;

        while (low <= up) {
            mid = (low+up)/2;
            long long served = 0;
            int exactCnt = 0;

            for (int b = 0; b < B; ++b) {
                long long mul = (mid / btime[b])+1; //plus current serving

                if (mid % btime[b] == 0) {
                    ++exactCnt;
                }

                served += mul;
            }

            if (served >= N) {                
                ans = mid;
                totalServed = served-exactCnt;
                up = mid-1;
            }
            else {
                low = mid+1;
            }
        }

        for (int b = 0; b < B; ++b) {
            if (ans % btime[b] == 0) {
                ++totalServed;

                if (totalServed == N) {
                    ansnum = b;
                    break;   
                }
            }
        }

        printf("Case #%d: %lld\n", tc, ansnum+1);
    }
    return 0;
}