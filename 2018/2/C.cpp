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

using VI = vector<int>;
using VVI = vector <VI>;

class BipartiteGraph {
    int lVertex;
    int rVertex;
    VVI adja;
    VI used;
    VI mat;

    bool _extend(int now) {
        for(int i = 0; i < adja[now].size(); i++) {
            int nextn = adja[now][i];

            if(used[nextn] == 0) {
                used[nextn] = 1;
                if(mat[nextn] == -1 || _extend(mat[nextn])) {
                    mat[nextn] = now;
                    return true;
                }
            }
        }
        return false;
    }

public:
    BipartiteGraph (int lv, int rv) {
        lVertex = lv;
        rVertex = rv;
        adja = move(VVI(lVertex));
        used = move(VI(lVertex));
        mat = move(VI(rVertex));
    }

    void addEdge(int lv, int rv) {
        adja[lv].push_back(rv);
    }

    int getMaximumMatch() {
        int ans = 0;
        fill(mat.begin(), mat.end(), -1);
        for(int i = 0; i < lVertex; i++) {
            fill(used.begin(), used.end(), 0);
            if(_extend(i)) {
                ans++;
            }
        }
        return ans;
    }
};

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        int ans = 0;
        VVI mat(N, VI(N));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> mat[i][j];
            }
        }

        for (int v = -N; v <= N; ++v) {
            if (v == 0) {
                continue;
            }

            BipartiteGraph bg(N, N);
            int cnt = 0;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (mat[i][j] == v) {
                        ++cnt;
                        bg.addEdge(i, j);
                    }
                }
            }

            int res = bg.getMaximumMatch();
            ans += (cnt-res);
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
