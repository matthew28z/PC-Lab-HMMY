#include <iostream>
#include <vector>
#include <string>

using namespace std;

int remaining(vector<string> words, int index) {
    int res = 0;

    for (int i = index; i < words.size(); i++) {
        res += words[i].size() + 1;
    }

    return res - 1;
}

int findSpace(string line, int lastIndex, int spaces) {
    int result = -1;

    for (int i = 0; i < lastIndex; i++) {
        bool isOkay = true;

        for (int j = i; j < i + spaces; j++) {
            if (line[j] != ' ') {
                isOkay = false;
                break;
            }
        }

        if (isOkay) {
            result = i;
        }
    }

    return result;
}

int main() {
    vector<string> words;

    int totalLength = 0;

    while (!cin.eof()) {
        string word;

        cin >> word;

        if (!word.empty()) {
            words.push_back(word);
            totalLength += 1 + word.size();
        }
    }

    int i = 0;

    while (remaining(words, i) > 60) {
        string line = words[i];
        j++;

        while (line.size() < 60) {
            string nextWord = words[i];
            size_t nextSize = nextWord.size();

            if (line.size() + nextSize + 1 <= 60) {
                line += string(" ") + nextWord;
                i++;
            } else {
                break;
            }
        }

        if (line.size() < 60) {
            int spaces = 1;
            int lastIndex = line.size();

            while(line.size() != 60) {
                int index = findSpace(line, lastIndex, spaces);

                if (index != -1) {
                    line.insert(index + 1, 1, ' ');
                    lastIndex = index;
                } else {
                    spaces++;
                    lastIndex = line.size();
                }
            }
        } 

        cout << line << endl;
    }

    for (i; i < words.size() - 1; i++) {
        cout << words[i] << " ";
    }

    cout << words[words.size() - 1] << endl;

    return 0;
}
