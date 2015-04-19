#include <cstdio>
#include <cstring>

const int MAXS = 1010;
int acc[MAXS];
char str[MAXS];

int main()
{
    int TC, S;
    scanf("%d", &TC);

    for (int tc = 1; tc <= TC; ++tc) {
        memset(acc, 0, sizeof(acc));   
        scanf("%d", &S);
        scanf("%s", str);

        acc[0] = str[0]-'0';
        int cost = 0;
        for (int s = 1; s <= S; ++s) {
            
            if (acc[s-1] <= s) {
                cost += s-acc[s-1];
                acc[s-1] = s;
            }

            acc[s] = acc[s-1] + str[s]-'0';
        }

        printf("Case #%d: %d\n", tc, cost);
    }
    return 0;
}