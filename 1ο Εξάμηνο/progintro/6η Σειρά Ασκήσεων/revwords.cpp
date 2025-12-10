#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool endLine(string word) {
    return word.back() == '\n';
}

int main() {
    vector<string> words;
    char temp;
    bool isChar = false;

    while (!cin.eof()) {
        string word;
        cin >> word;
        char c = getchar();

        if (!word.empty()) {
            if (isChar) {
                isChar = false;

                if (temp != ' ' && temp != '\t')
                word.insert(0, string(1, temp));
            }

            if (c == '\n') {
                temp = getchar();

                if (temp == '\n') {
                    isChar = false;
                    words.push_back(string(1, '\n'));
                } else {
                    isChar = true;
                }

                word.push_back(c);
            }

            words.push_back(word);
        }
    }

    vector<vector<string>> lines;
    lines.push_back({ });
    int l = 0;

    for (string word : words) {
        lines[l].push_back(word);

        if (word[0] == '\n') {
            lines.push_back({string(1, '\n')});
            l++;
        } else {
            if (endLine(word)) {
                lines.push_back({ });
                l++;
            }
        }

    }

    //Clears the trailing empty vector, because the input ends with '\n'
    lines.pop_back();

    for (vector<string> line : lines) {
        if (line.size() > 1) {
            line.back().erase(remove(line.back().begin(), line.back().end(), '\n'), line.back().end());
        }

        for (int i = line.size() - 1; i > 0; i--) {
            cout << line[i] << " ";
        }

        cout << line[0] << endl;
    }

    return 0;
}
