#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000100;
int N;
long long sum[MAXN];
long long P, Q, R, S;

inline long long sumOfRange(int s, int t)
{
    if(s > t) {
        return 0;
    }
    long long from = s ? sum[s-1] : 0, to = sum[t];
    return to-from;
}

inline long long ArnarGet(int s, int t)
{
    long long Solveig = max(sumOfRange(s, t), max(sumOfRange(0, s-1), sumOfRange(t+1, N-1)));
    return sum[N]-Solveig;
}

int main()
{
    int TC;
    scanf("%d", &TC);

    for(int tc = 1; tc <= TC; ++tc) {
        scanf("%d%lld%lld%lld%lld", &N, &P, &Q, &R, &S);
        for(int i = 0; i < N; i++) {
            long long val = (i * P + Q) % R + S;
            sum[i] = val;
            if(i) {
                sum[i] += sum[i-1];
            }
        }

        sum[N] = sum[N-1];
        long long ans = 0, halfSum = sum[N]/2, thirdSum = sum[N]/3; 
        int rightBound = 0;

        for(int i = 0; i < N; ++i) {
            while( rightBound < N) {
                ans = max(ans, ArnarGet(i, rightBound));
                ++rightBound;
                if(rightBound < N && sumOfRange(i, rightBound) >= thirdSum) {
                    ans = max(ans, ArnarGet(i, rightBound));
                    rightBound = max(i+1, rightBound-1);
                    break;
                }
            }
            if(sum[i] > halfSum) break;
        }

        printf("Case #%d: %.12f\n", tc, (double)ans/(double)sum[N]);
    }
    return 0;
}
