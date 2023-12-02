#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>
#include <sstream>

//Day 1 of Avant of Code 2023
/*--- Day 1: Trebuchet?! ---
Something is wrong with global snow production, and you've been selected to take a look. 
The Elves have even given you a map; on it, they've used stars to mark the top fifty locations that are likely to be having problems.
You've been doing this long enough to know that to restore snow operations, you need to check all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; 
the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
You try to ask why they can't just use a weather machine ("not powerful enough") and where they're even sending you ("the sky") and w
hy your map looks mostly blank ("you sure ask a lot of questions") and hang on did you just say the sky ("of course, where do you think snow comes from") 
when you realize that the Elves are already loading you into a trebuchet ("please hold still, we need to strap you in").
As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very 
young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.
The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. 
On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

For example:
1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.
Consider your entire calibration document. What is the sum of all of the calibration values?
*/
using namespace std;

map<string, int> makeNumMap() {
    return {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"sseven", 7},
        {"eight", 8},
        {"nine", 9},
    };
}

int convertToDigit(const string& s, const map<string, int>& numberMap) {
    if (s.empty()) return 0;
    if (isdigit(s[0])) return s[0] - '0';
    auto it = numberMap.find(s);
    if (it != numberMap.end()) return it->second;
    return 0;
}

bool openFile(string& filePath, ifstream& fin) {
    fin.open(filePath);
    if (!fin.is_open()){
        cout << "Unable to open file: " << filePath << endl;
        return false;
    } else return true;
}

//ughhhh
void extractCalibrationValues(ifstream& fileStream, vector<int>& values, const map<string, int>& numberMap) {
    string line;
    while (getline(fileStream, line)) {
        int firstDigit = 0, lastDigit = 0;
        string temp;

        // Process the line for the first digit or spelled-out number
        for (size_t i = 0; i < line.length(); ++i) {
            char ch = tolower(line[i]);
            if (isalpha(ch) || isdigit(ch)) {
                temp += ch;
                auto it = numberMap.find(temp);
                if (it != numberMap.end()) {
                    firstDigit = it->second;
                }
            } else {
                temp.clear();
            }
            if (firstDigit != 0) {
                break;
            }
        }
        temp.clear(); // Reset temp to find the last digit or spelled-out number

        // Process the line backwards for the last digit or spelled-out number
        for (int i = static_cast<int>(line.length()) - 1; i >= 0; --i) {
            char ch = tolower(line[i]);
            if (isalpha(ch) || isdigit(ch)) {
                temp = ch + temp;
                auto it = numberMap.find(temp);
                if (it != numberMap.end()) {
                    lastDigit = it->second;
                    break;
                }
            } else {
                temp.clear();
            }
        }

        if (firstDigit != 0 && lastDigit != 0) {
            values.push_back(firstDigit * 10 + lastDigit);
        }
        // Debugging output
        cout << " line: " << line << endl;
        cout << "first digit: " << firstDigit << ", last digit: " << lastDigit << endl;
        cout << "combined: " << (firstDigit * 10 + lastDigit) << endl;
    }
}

int main() {
    string filePath = "aocInputDay1-2023.txt";
    ifstream file;
    vector<int> calibrationVal;
    int sum = 0;

    map<string, int> numberMap = makeNumMap();

    if (openFile(filePath, file)) {
        extractCalibrationValues(file, calibrationVal, numberMap);
        file.close();
    }
    for (int value : calibrationVal) {
        sum += value;
    }

    cout << "Sum: " << sum << endl;
    return 0;
}