#include <bits/stdc++.h>
#include "./TestFramework.cpp"
#include "./Bai17Grader.cpp"
#include "./Bai18Grader.cpp"

using namespace std;

class MyTestFramework : public TestFramework {

    Bai17Grader *bai17Grader = NULL;
    Bai18Grader *bai18Grader = NULL;

public:
    MyTestFramework(std::string testInputFile = ""):TestFramework(testInputFile) {
        if (testInputFile == "bai17") {
            this->bai17Grader = new Bai17Grader(TEST_INPUT_FILE);
        } else if (testInputFile == "bai18") {
            this->bai18Grader = new Bai18Grader(TEST_INPUT_FILE);
        } else {
        }
    }
    
    vector<string> printTestInputs(int loop) override {
        if (this->inputFileName == "bai17") {
            if (this->bai17Grader != NULL) {
                return this->bai17Grader->grade(loop);
            } else {
                return (new Bai17Grader(TEST_INPUT_FILE))->grade(loop);
            }
        } else if (this->inputFileName == "bai18") {
            if (this->bai18Grader != NULL) {
                return this->bai18Grader->grade(loop);
            } else {
                return (new Bai18Grader(TEST_INPUT_FILE))->grade(loop);
            }
        } else {
            vector<string> empty;
            return empty;
        }
    }
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        MyTestFramework testFramework;
        testFramework.run();
    } else {
        string inputFileName = argv[1];
        MyTestFramework testFramework(inputFileName);
        testFramework.run();
    }
    return 0;
}