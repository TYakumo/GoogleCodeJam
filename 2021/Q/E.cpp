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

using VI = vector <int>;
using VD = vector <double>;
using VS = vector <string>;
const int MAXN = 100;
const int MAXQ = 10000;

double getExpectedScore(double skill) {
    return (log(1+exp(skill+3)) - log(1+exp(skill-3)))/6.0;
}

double sigmoid(double v) {
    return 1.0/(1.0+exp(-v));
}

double findSkill(double cnt) {
    double low = -3;
    double up = 3;
    double ret = -3;

    for (int i = 0; i < 50; ++i) {
        double mid = (low+up) / 2;
        double val = getExpectedScore(mid);

        if (val <= cnt) {
            low = mid;
            ret = mid;
        } else {
            up = mid;
        }
    }

    return ret;
}

double findDifficulty(double cnt, const VD& skills) {
    double low = -3;
    double up = 3;
    double ret = -3;

    for (int i = 0; i < 30; ++i) {
        double mid = (low+up) / 2;
        double res = 0;
        for (int j = 0; j < skills.size(); ++j) {
            res += sigmoid(skills[j] - mid);
        }

        res /= skills.size();

        if (res >= cnt) {
            low = mid;
            ret = mid;
        } else {
            up = mid;
        }
    }

    return ret;
}

int main()
{
    int TC;
    int P;

    cin >> TC >> P;


    for (int tc = 1; tc <= TC; tc++) {
        VS S(MAXN);

        for (int i = 0; i < MAXN; ++i) {
            cin >> S[i];
        }

        VD skills;
        VI acnt(MAXQ);
        VD difficulty(MAXQ);

        for (int i = 0; i < MAXN; ++i) {
            int cnt = 0;

            for (int j = 0; j < MAXQ; ++j) {
                if (S[i][j] == '1') {
                    ++cnt;
                    ++acnt[j];
                }
            }

            // sum of 1.0/(1.0+exp(-x)) = cnt
            // ln(1+e^x) = cnt
            // ln(1+e^(s+3)) - ln(1+e^(s-3)) = cnt
            const double eps = 1e-15;
            skills.push_back(findSkill(cnt/(double)MAXQ));
        }

        for (int i = 0; i < MAXQ; ++i) {
            difficulty[i] = findDifficulty(acnt[i]/(double)(MAXN), skills);
        }

        int cheater = 1;
        int ncheater = -1;
        double worstRatio = -1.0;
        double nworstRatio = -1.0;

        for (int i = 0; i < MAXN; ++i) {
            const double THRESHOLD = 0.8;
            const double NTHRESHOLD = 0.6;

            int ntot = 0;
            int pass = 0;
            double navg = 0;

            for (int j = 0; j < MAXQ; ++j) {
                double v = skills[i] - difficulty[j];

                if (sigmoid(v) < NTHRESHOLD) {
                    ++ntot;
                    navg += sigmoid(v);

                    if (S[i][j] == '1') {
                        ++pass;
                    }
                }
            }

            navg /= ntot;

            double nratio = ntot <= 5 ? 0.0 : (double) pass / ntot;
            double ratiodiff = nratio - navg;
            if (ratiodiff > worstRatio) {
                worstRatio = ratiodiff;
                cheater = i+1;
            }
        }

        cout << "Case #" << tc << ": " << cheater << endl;
    }

    return 0;
}
