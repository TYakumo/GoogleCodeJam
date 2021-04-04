#include <cstdio>
#include <iostream>
#include <vector>

struct GCDInfo {
    long long x;
    long long y;
    long long g;
    GCDInfo () {

    }

    GCDInfo (long long px, long long py, long long pg) : x(px), y(py), g(pg) {

    }
};

struct ModInfo
{
    // A mod p = c for a unknown A
    long long p;
    long long c;
    ModInfo() {

    }

    ModInfo(long long pp, long long pc) : p(pp), c(pc) {

    }
};

// ax + by = g
// bx' + (a-floor(a/b)*b)*y' = g
// x = y', y = x' - (floor(a/b)*b) * y'
// for ax + by = 1, x is the mod inverse of a in b
GCDInfo extendedEuc(long long a, long long b) {
    if (b == 0) {
        return GCDInfo(1, 0, a);
    }

    GCDInfo tmp = extendedEuc(b, a%b);
    GCDInfo ret = GCDInfo(tmp.y, tmp.x-(a/b)*tmp.y, tmp.g);

    // normalization to avoid overflow
    // it is ok to assume |x| <= b & |y| <= a
    ret.x -= (ret.x / b) * b;
    ret.y -= (ret.y / a) * a;
    return ret;
}

// 1. g mod p1 = c1 => gx1 + p1y1 = c1
// 2. g mod p2 = c2 => gx2 + p2y2 = c2
// 3. g mod p3 = c3 => gx3 + p3y3 = c3
// combine 1. & 2 & 3.
// we have g mod p1p2p3 = c1*(p2p3)*(p2p3)^(-1) in p1 + c2*(p1p3)*(p1p3)^(-1) in p2 + c3*(p1p2)*(p1p2)^(-1) in p3
// for example, g mod 2 = 1 and g mod 3 = 1
// we have 1 * 3 * 3^(-1) + 1 * 2 * 2^(-1)
// = 1 * 3 * 1 + 1 * 2 * 2 = 3 + 4 = 7
// 7 mod 6 = 1
long long combineEq(std::vector<ModInfo>& eqs) {
    long long combP = 1;
    long long acc = 0;

    for (int idx = 0; idx < eqs.size(); ++idx) {
        combP *= eqs[idx].p;
    }

    for (int idx = 0; idx < eqs.size(); ++idx) {
        GCDInfo g = extendedEuc(combP/eqs[idx].p, eqs[idx].p);
        long long tmp = g.x * (combP/eqs[idx].p) * eqs[idx].c;
        acc += tmp;
    }

    // to avoid negative result
    return (acc%combP + combP) % combP;
}

int main()
{
    int T, N, M;

    scanf("%d %d %d", &T, &N, &M);

    const int arr[] = {17, 16, 13, 11, 9, 7, 5};
    const int numOfWindmill = 18;

    for (int t = 0; t < T; ++t) {
        std::vector<ModInfo> eqs;

        for (int i = 0; i < N && i < 7; ++i) {
            std::cout << arr[i];
            for (int j = 1; j < numOfWindmill; ++j) {
                std::cout << " " << arr[i];
            }
            std::cout << std::endl;

            int tot = 0;

            for (int i = 0; i < numOfWindmill; ++i) {
                int tmp;
                scanf("%d", &tmp);
                tot += tmp;
            }
            eqs.push_back(ModInfo(arr[i], tot));
        }

        std::cout << combineEq(eqs) << std::endl;
        int verdict;
        scanf("%d", &verdict);

        if (verdict == -1) {
            break;
        }
    }
    return 0;
}