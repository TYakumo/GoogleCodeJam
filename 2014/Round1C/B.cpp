#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
const int MAXC = 110, MAXN = 110;
const int LEFT = 2, RIGHT = 1, MIDDLE = 0, DOUBLE = 3;
char temps[MAXC];
char str[MAXN][MAXC];
int cnt[26][4];
int mapping[26][4];
bool used[MAXN];

inline long long factorial(int n)
{
    long long ret = 1;
    for (int i = 2; i <= n; ++i) {
        ret = (ret*i)%MOD;
    }
    return ret;
}

int main()
{
    int TC;
    int len;
    int slen[MAXN];

    scanf("%d", &TC);
    for (int tc = 1; tc <= TC; ++tc) {
        int N;
        scanf("%d", &N);

        memset(used, 0, sizeof(used));
        memset(cnt, 0, sizeof(cnt));
        memset(mapping, -1, sizeof(mapping));

        for (int i = 0; i < N; ++i) {
            len = 0;
            slen[i] = 0;
            scanf("%s", temps);
            char prec = -1;

            while ('\0' != temps[len]) {
                if (temps[len] != prec) {
                    str[i][slen[i]++] = temps[len];
                    prec = temps[len];
                }
                ++len;
            }

            if (slen[i] > 1) {
                ++cnt[str[i][0]-'a'][LEFT];
                mapping[str[i][0]-'a'][LEFT] = i;
                ++cnt[str[i][slen[i]-1]-'a'][RIGHT];
                mapping[str[i][slen[i]-1]-'a'][RIGHT] = i;
                for (int j = 1; j < slen[i]-1; j++) {
                    ++cnt[str[i][j]-'a'][MIDDLE];
                }
            }
            else {
                ++cnt[str[i][0]-'a'][DOUBLE];
            }
        }

        //possibility check
        bool valid = true;
        long long res = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i][MIDDLE] && (cnt[i][LEFT] || cnt[i][RIGHT] || cnt[i][DOUBLE])) {
                valid = false;
                break;
            }

            if (cnt[i][LEFT] > 1 || cnt[i][RIGHT] > 1) {
                valid = false;
                break;
            }
        }

        //enumerating starting train
        if (valid) {
            long long totalBlock = 0;
            res = 1;
            for (int i = 0; i < N; ++i) {
                if (!used[i] && slen[i] != 1) {
                    int cur = i;
                    ++totalBlock;
                    //right =>
                    do {
                        used[cur] = true;
                        char nowc = str[cur][slen[cur]-1]-'a';
                        res = (res * factorial(cnt[nowc][DOUBLE]))%MOD;   
                        //mark all double
                        for (int j = 0; j < N; j++) {
                            if (slen[j] == 1 && str[j][0]-'a' == nowc) {
                                used[j] = true;
                            }
                        }
                        cur = mapping[nowc][LEFT];
                        if (cur == -1) {
                            break;
                        }
                        if (used[cur]) {
                            res = 0;
                            valid = false;
                            break;
                        }
                    }while(true);

                    //<= left
                    cur = i;
                    do {
                        used[cur] = true;
                        char nowc = str[cur][0]-'a';
                        res = (res * factorial(cnt[nowc][DOUBLE]))%MOD;                           
                        for (int j = 0; j < N; j++) {
                            if (slen[j] == 1 && str[j][0]-'a' == nowc) {
                                used[j] = true;
                            }
                        }
                        cur = mapping[nowc][RIGHT];
                        if (cur == -1) {
                            break;
                        }

                        if (used[cur]) {
                            res = 0;
                            valid = false;
                            break;
                        }
                    }while(true);

                    if (valid == false) {
                        break;
                    }
                }
            }

            if (valid) {
                //DOUBLE only
                for (int i = 0; i < N; ++i) {
                    if (!used[i]) {
                        ++totalBlock;
                        char nowc = str[i][0]-'a';
                        res = (res * factorial(cnt[nowc][DOUBLE]))%MOD;
                        for (int j = 0; j < N; j++) {
                            if (slen[j] == 1 && str[j][0]-'a' == nowc) {
                                used[j] = true;
                            }
                        }
                    }
                }
            }
            res = (res * factorial(totalBlock))%MOD;
        }
        printf("Case #%d: %lld\n", tc, res);
    }
}
