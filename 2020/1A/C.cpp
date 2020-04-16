#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <list>
using namespace std;

using VVI = vector< vector <int> > ;
using PII = pair<int, int>;
inline int coorToInt(int r, int c, int C) {
    return r*C + c;
}

list<PII>::iterator listEnd(list<PII>& l) {
    auto iter = l.end();
    --iter;
    return iter;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        int C;
        cin >> R >> C;

        VVI dancer(R, vector<int>(C));

        long long total = 0;
        int remain = 0;
        long long ans = 0;

        vector<list<PII>::iterator> rowMapper(R*C);
        vector<list<PII>::iterator> colMapper(R*C);
        vector<list <PII>> rowList(R);
        vector<list <PII>> colList(C);
        vector <int> cand;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> dancer[i][j];

                total += dancer[i][j];

                if (dancer[i][j] > 0) {
                    ++remain;
                    int idx = coorToInt(i, j, C);

                    rowList[i].push_back(make_pair(dancer[i][j], idx));
                    rowMapper[idx] = listEnd(rowList[i]);
                    colList[j].push_back(make_pair(dancer[i][j], idx));
                    colMapper[idx] = listEnd(colList[j]);
                    cand.push_back(idx);
                }
            }
        }

        while (true) {
            vector <pair<int, int>> toBeRemoved;
            vector <int> newCand;

            ans += total;

            for (int a = 0; a < cand.size(); ++a) {
                int i = cand[a] / C;
                int j = cand[a] % C;
                if (dancer[i][j] <= 0) {
                    continue;
                }

                int nCnt = 0;
                int nSum = 0;
                int idx = coorToInt(i, j, C);
                vector <int> neighbors;

                auto iter = rowMapper[idx];

                if (iter != rowList[i].begin()) {
                    auto iter2 = iter;
                    --iter2;
                    ++nCnt;
                    nSum += (*iter2).first;
                    neighbors.push_back((*iter2).second);
                }

                if (iter != listEnd(rowList[i])) {
                    auto iter2 = iter;
                    ++iter2;
                    ++nCnt;
                    nSum += (*iter2).first;
                    neighbors.push_back((*iter2).second);
                }

                iter = colMapper[idx];

                if (iter != colList[j].begin()) {
                    auto iter2 = iter;
                    --iter2;
                    ++nCnt;
                    nSum += (*iter2).first;
                    neighbors.push_back((*iter2).second);
                }

                if (iter != listEnd(colList[j])) {
                    auto iter2 = iter;
                    ++iter2;
                    ++nCnt;
                    nSum += (*iter2).first;
                    neighbors.push_back((*iter2).second);
                }

                if (nCnt > 0 && dancer[i][j]*nCnt < nSum) {
                    --remain;
                    toBeRemoved.emplace_back(make_pair(i, j));

                    int offset = newCand.size() ? newCand.size()-1: 0;
                    newCand.insert(newCand.begin() + offset, neighbors.begin(), neighbors.end());
                }
            }

            for (int i = 0; i < toBeRemoved.size(); ++i) {
                pair <int, int> r = toBeRemoved[i];
                int idx = coorToInt(r.first, r.second, C);

                if (dancer[r.first][r.second] <= 0) {
                    continue;
                }

                rowList[r.first].erase(rowMapper[idx]);
                colList[r.second].erase(colMapper[idx]);
                total -= dancer[r.first][r.second];
                dancer[r.first][r.second] = 0;
            }

            cand = newCand;

            if (toBeRemoved.size() == 0) {
                break;
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
