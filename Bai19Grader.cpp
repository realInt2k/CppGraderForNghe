/**
 * Tim so nguyen to
 */

#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int MAX_N = 1000000;
/**
 * 1 <= n <= 1000000
 * -1000000000 <= a[i] <= 1000000000
 * Dòng 1: Output ra số lượng số lẻ, số lượng số chẵn. vd: "3, 5" hay là "0, 4"
 * Dòng 2: Output ra số lẻ lớn nhất, số lẻ bé nhất, số chẵn lớn nhất, số chẵn bé nhất. vd: "101, -3, 202, -4"
 * Dòng 2 mà ko có số thích hợp thì ghi ra NaN vd: "NaN, NaN, 202, -4"
 */

class Bai19Grader
{
    string _testInputFile;
public:
    Bai19Grader (string testInputFile) {
        this->_testInputFile = testInputFile;
    }

    vector<string> grade(int loop) {
        cout << "Test inputs number " << loop << ": " << endl;
        vector<string> expectedAnswers;
        FILE *f = fopen(this->_testInputFile.c_str(), "w");
        int n = MAX_N;
        vector<int> a;
        if (loop <= 5) {
            n = rand() % 1000 + 1;
        } else if (loop <= 10) {
            n = rand() % 10000 + 1;
        } else if (loop <= 20) {
            n = rand() % 500000 + 1;
        }
        fprintf(f, "%d\n", n);
        printf("%d\n", n);
        bool printedEtc = false;
        for(int i = 0; i < n; ++i) {
            int x = rand() % 2000000001 - 1000000000;
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

        int nOdds = 0, nEvens = 0;
        int minOddIndex = -1;
        int maxOddIndex = -1;
        int minEvenIndex = -1;
        int maxEvenIndex = -1;
        for(int i = 0; i < n; ++i) {
            nOdds += a[i] & 1;
            nEvens += !(a[i] & 1);
            if (a[i] & 1) {
                if (minOddIndex == -1 || (minOddIndex != -1  && a[i] < a[minOddIndex])) {
                    minOddIndex = i;
                } 
                if (maxOddIndex == -1 || (maxOddIndex != -1 && a[i] > a[maxOddIndex])) {
                    maxOddIndex = i;
                } 
            } else {
                if (minEvenIndex == -1 || (minEvenIndex != -1 && a[i] < a[minEvenIndex])) {
                    minEvenIndex = i;
                } 
                if (maxEvenIndex == -1 || (maxEvenIndex != -1 && a[i] > a[maxEvenIndex])) {
                    maxEvenIndex = i;
                } 
            }
        }
        string maxOdd = maxOddIndex == -1 ? "NaN" : to_string(a[maxOddIndex]);
        string minOdd = minOddIndex == -1 ? "NaN" : to_string(a[minOddIndex]);

        string maxEven = maxEvenIndex == -1 ? "NaN" : to_string(a[maxEvenIndex]);
        string minEven = minEvenIndex == -1 ? "NaN" : to_string(a[minEvenIndex]);

        string nOddsResult = to_string(nOdds);
        string nEvensResult = to_string(nEvens);

        expectedAnswers.push_back(nOddsResult + ", " + nEvensResult);
        expectedAnswers.push_back(maxOdd + ", " + minOdd + ", " + maxEven + ", " + minEven);

        fclose(f);
        return expectedAnswers;
    }
};