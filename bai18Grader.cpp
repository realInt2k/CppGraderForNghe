/**
 * Tim so nguyen to
 */

#include <bits/stdc++.h>

using namespace std;
#define ll long long

bool isPrime[2000000];
const int MAXINT = 1000000;

class Bai18Grader
{
    string _testInputFile;
public:
    Bai18Grader (string testInputFile) {
        this->_testInputFile = testInputFile;
        for(int i = 0; i < MAXINT; ++i) {
            isPrime[i] = true;
        }
        for(int i = 2; i <= MAXINT / 2; ++i) {
            if (isPrime[i]) {
                int j = i;
                while (j <= MAXINT) {
                    j += i;
                    if (j <= MAXINT)
                        isPrime[j] = false;
                }
            }
        }
    }

    /**
     * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
     * T T T T T T T T T T  T  T  T  T  T  T  T  T  T  T
     * T T T F T F T F T F  T  F  T  F  T  F  T  F  T  F
     */

    vector<string> grade(int loop) {
        cout << "Test inputs number " << loop << ": " << endl;
        vector<string> expectedAnswers;
        FILE *f = fopen(this->_testInputFile.c_str(), "w");
        int n = 10000;
        vector<int> a;
        if (loop <= 5) {
            n = rand() % 10 + 1;
        } else if (loop <= 10) {
            n = rand() % 100 + 1;
        } else if (loop <= 20) {
            n = rand() % 500 + 1;
        }
        fprintf(f, "%d\n", n);
        printf("%d\n", n);
        bool printedEtc = false;
        for(int i = 0; i < n; ++i) {
            int x = rand() % 1000000 + 1;
            if (!x&1) x += 1;
            a.push_back(x);
            fprintf(f, "%d ", x);
            if (i < 100) {
                printf("%d, ", x);
            } else if (!printedEtc) {
                printedEtc = true;
                printf("...");
            }
        }
        printf("\n");

        vector<int> res;
        for(int i = 0; i < n; ++i) {
            if (isPrime[a[i]]) {
                res.push_back(a[i]);
            }
        }

        string answerStr = "";
        for(int i = 0; i < res.size(); ++i) {
            if (i < res.size() - 1) {
                answerStr += to_string(res[i]) + ", ";
            } else {
                answerStr += to_string(res[i]);
            }
        }
        if (res.size() == 0) {
            expectedAnswers.push_back("NO");
        } else {
            expectedAnswers.push_back(answerStr);
        }
        fclose(f);
        return expectedAnswers;
    }
};