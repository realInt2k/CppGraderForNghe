#include <bits/stdc++.h>

using namespace std;
#define ll long long

class Bai17Grader
{
    string _testInputFile;
public:
    Bai17Grader (string testInputFile) {
        this->_testInputFile = testInputFile;
    }

    vector<string> grade(int loop) {
        cout << "Test inputs number " << loop << ": " << endl;
        vector<string> expectedAnswers;
        vector<string> inputLines;
        FILE *f = fopen(this->_testInputFile.c_str(), "w");
        ll x = rand() % 10000 + 1;
        ll y = rand() % 10000 + 1;
        if (loop <= 5) {
            x = rand() % 20 + 1;
            y = rand() % 16 + 1;
        } else if (loop <= 10) {
            x = rand() % 100 + 1;
            y = rand() % 50 + 1;
            if (!x&1) x += 1;
            if (!y&1) y += 1;
        } else if (loop <= 24) {
            x = rand() % 5000 + 1;
            y = rand() % 2500 + 1;
            if (x&1) x += 1;
            if (y&1) y += 1;
        }
        fprintf(f, "%d %d\n", x, y);
        cout << x << " " << y << endl;
        ll oriX = x, oriY = y;
        ll tmp = x;
        if (x < y) {
            tmp = x;
            x = y;
            y = tmp;
        } 
        while (y != 0) {
            ll mod = x % y;
            x = y;
            y = mod;
        }
        fclose(f);
        expectedAnswers.push_back(to_string(x));
        expectedAnswers.push_back(to_string((oriX * oriY) / x));
        return expectedAnswers;
    }
};