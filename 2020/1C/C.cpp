#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VI = vector <int>;
using VVI = vector <VI>;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int D;
        cin >> N >> D;

        VLL A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        sort(A.begin(), A.end());

        long long best = D-1;
        map <pair<long long, long long>, VLL> dSet;

        for (int d = 1; d <= D; ++d) {
            for (int i = 0; i < N; ++i) {
                long long g = gcd(A[i], d);
                long long ga = A[i]/g;
                long long gd = d/g;

                if (dSet.count(make_pair(ga, gd)) == 0) {
                    dSet[make_pair(ga, gd)] = {d};
                } else {
                    dSet[make_pair(ga, gd)].push_back(d);
                }
            }
        }

        auto iter = dSet.begin();

        while (iter != dSet.end()) {
            sort(iter->second.begin(), iter->second.end());
            int chosen = 0;
            long long accLen = 0;

            for (int i = 0; i < iter->second.size(); ++i) {
                accLen += iter->second[i];
                if (accLen >= D) {
                    if (accLen == D) {
                        ++chosen;
                    }
                    break;
                }
                ++chosen;
            }


            long long cost = D - chosen;
            long long remain = D - accLen;

            for (int i = A.size()-1; i >= 0 && remain > 0; --i) {
                long long na = A[i]*iter->first.second;
                long long nm = na / iter->first.first;

                if (na % iter->first.first != 0 || nm > D) {
                    remain -= nm;
                }
            }

            if (remain <= 0) {
                best = min(best, cost);
            }

            ++iter;
        }


        cout << "Case #" << tc << ": " << best << endl;
    }

    return 0;
}
