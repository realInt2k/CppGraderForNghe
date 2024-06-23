#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <algorithm>
#include <vector>

#include <thread>
#include <future>
#include <chrono>


using namespace std;

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

const int N_TESTS = 25;
const string TEST_INPUT_FILE = "test_inputs.txt";
const string TARGET_PROGRAM_OUTPUT_FILE = "output.txt";
const string PROGRAM_NAME = "grader";
const int TIME_LIMIT = 500;

class TestFramework {
public:
    string customFileName = "";
    TestFramework (string fileName = "") {
        this->customFileName = fileName;
    }

    string inputFileName = "";
    virtual vector<string> printTestInputs(int loop) = 0;

    vector<string> readOutputFromFile(const string& filename) {
        ifstream file(filename);
        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    string inputTargetProgram() {
        string inputFileName;
        if (this->customFileName == "") {
            cout << "Enter the C++ source file name (e.g., ex1 without cpp): ";
            cin >> inputFileName;
            return inputFileName;
        } else {
            return this->customFileName;
        }
    }

    bool compileTargetProgram(string inputFileName) {
        string compileCommand = "g++ " + inputFileName + ".cpp -o " + inputFileName;

        if (system(compileCommand.c_str()) != 0) {
            return false;
        }

        return true;
    }

    bool runTargetProgram(string inputFileName, int timeoutSeconds) {
        string runCommand = "cat " + TEST_INPUT_FILE + " | ./" + inputFileName + ".exe > " + TARGET_PROGRAM_OUTPUT_FILE;
        

        std::future<int> resultFuture = std::async(std::launch::async, [=]() {
            return system(runCommand.c_str());
        });

        std::future_status status;

        if (resultFuture.wait_for(std::chrono::milliseconds(timeoutSeconds)) == std::future_status::timeout) {
            //std::cout << "Program time limit exceeded  " << timeoutSeconds << " .\n";
            printf("Program time limit exceeded %d. ⚠️\n", timeoutSeconds);
            system(("taskkill /im " + inputFileName + ".exe" + " /f > nul 2>&1").c_str());
            return false;
        } else {
            int commandResult = resultFuture.get();
            if (commandResult != 0) {
                std::cerr << "Program failed with error code: " << commandResult << std::endl;
                return false;
            }
            return true;
        }

        return true;
    }

    void run() {
        this->inputFileName = inputTargetProgram();
        bool resultCompile = compileTargetProgram(inputFileName);
        if (!resultCompile) {
            cerr << "Compilation failed!" << endl;
            return;
        }
        int correct = 0;
        for (int loop = 0; loop < N_TESTS; ++loop) {
            cout << "\n-------\n";
            vector<string> expectedAnswers = printTestInputs(loop);
            if (expectedAnswers.size() <= 0) {
                cout << "Grading not supported !\n";
                return;
            }
        
            bool resultRun = runTargetProgram(inputFileName, TIME_LIMIT);
            if (!resultRun) {
                continue;
            }

            vector<string> targetAnswers = readOutputFromFile(TARGET_PROGRAM_OUTPUT_FILE);

            printf("Comparision Outputs:\n");
            if (expectedAnswers.size() != targetAnswers.size()) {
                printf("Test %d Incorrect\n", loop);
            } else {
                bool isCorrect = true;
                for (int i = 0; i < targetAnswers.size(); ++i) {
                    ltrim(targetAnswers[i]);
                    rtrim(targetAnswers[i]);
                    ltrim(expectedAnswers[i]);
                    rtrim(expectedAnswers[i]);
                    //cout << "Candidate output Line (" << i << "): \"" << targetAnswers[i] << "\"" << endl;
                    printf("Candidate output Line (\"%d\"): %s\n", i, targetAnswers[i].c_str());
                    //cout << "Expected output Line (" << i << "): \"" << expectedAnswers[i] << "\"" << endl;
                    printf("Expected output Line (\"%d\"): %s\n", i, expectedAnswers[i].c_str());
                    if (strcmp(targetAnswers[i].c_str(), expectedAnswers[i].c_str()) != 0) {
                        isCorrect = false;
                        break;
                    }
                }
                if (isCorrect) {
                    correct += 1;
                    // cout << "Test " << loop << " CORRECT ✅" << endl;
                    printf("Test %d CORRECT ✅\n", loop);
                } else {
                    // cout << "Test " << loop << " Incorrect ❌" << endl;
                    printf("Test %d Incorrect ❌\n");
                }
            }
        }

        // cout << endl << "---RESULT---" << endl;
        printf("\n---RESULT---\n");
        // cout << correct << "/" << N_TESTS << endl;
        printf("%d/%d\n", correct, N_TESTS);

        remove(TARGET_PROGRAM_OUTPUT_FILE.c_str());
        remove(inputFileName.c_str());
        remove(TEST_INPUT_FILE.c_str());
        remove(PROGRAM_NAME.c_str());
    }
};
