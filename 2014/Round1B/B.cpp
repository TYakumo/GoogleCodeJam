#include <cstdio>

long long cal(int bitNum, bool minA, bool minB, bool minK, int A, int B, int K)
{
    if(bitNum == -1) return 1;
    long long ret = 0;
    
    bool couldSetOneA = minA || (A&(1<<bitNum))!=0,
         couldSetOneB = minB || (B&(1<<bitNum))!=0,   
         couldSetOneK = minK || (K&(1<<bitNum))!=0;  
 
    //setting all to be zero 0
    ret = cal(bitNum-1, couldSetOneA, couldSetOneB, couldSetOneK, A, B, K);

    //setting current bit 1 for A
    if (couldSetOneA) {
        ret += cal(bitNum-1, minA, couldSetOneB, couldSetOneK, A, B, K);
    }

    //setting current bit 1 for B
    if (couldSetOneB) {
        ret += cal(bitNum-1, couldSetOneA, minB, couldSetOneK, A, B, K);
    }

    //setting current bit 1 for both A and B
    if (couldSetOneA && couldSetOneB && couldSetOneK) {
       ret += cal(bitNum-1, minA, minB, minK, A, B, K); 
    }

    return ret;
}

int main()
{
    int TC;
    scanf("%d", &TC);
    
    for (int tc = 1; tc <= TC; tc++) {
        int A, B, K;
        scanf("%d%d%d", &A, &B, &K);
        printf("Case #%d: %lld\n", tc, cal(30, false, false, false, A-1, B-1, K-1));
    }
    return 0;
}
