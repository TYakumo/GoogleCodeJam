#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXL = 20;
long long MSDAns[MAXL];
long long digit[MAXL], mul[MAXL];

inline long long solve(long long val)
{
    if(val < 10) return val;
    if(val%10==0) return solve(val-1)+1;
    int len = 0;
    long long ret = 0;
    while(val) {
        digit[len++] = val%10;
        val /= 10;
    }
    ret = MSDAns[len-1] + digit[len-1] + (digit[0]-1);

    int nonZero = digit[len-1]!=1;
    for (int i = 1; i < len/2; i++) {
        ret += (digit[i] + digit[len-1-i]) * mul[i];
        nonZero |= digit[len-1-i] != 0;
    }
    if (len%2) {
        ret += digit[len/2]*mul[len/2];
    }

    return ret+nonZero;
}

int main()
{
    int TC;
    scanf("%d", &TC);
    mul[0] = 1;
    MSDAns[0] = 1;
    MSDAns[1] = 10;

    for (int i = 1; i < MAXL; ++i) {
        mul[i] = mul[i-1] * 10;
    }

    for (int i = 2; i < MAXL; ++i) {
        MSDAns[i] = MSDAns[i-1] + 1 + (mul[i/2]-1) + (mul[(i+1)/2]-1);
    }

    for (int tc = 1; tc <= TC; ++tc) {
        long long N;
        scanf("%lld", &N);
        printf("Case #%d: %lld\n", tc, solve(N));
    }
    return 0;
}
