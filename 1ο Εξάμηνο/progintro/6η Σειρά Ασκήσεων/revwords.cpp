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

    while (!cin.eof()) {
        string word;
        cin >> word;
        char c = getchar();

        if (!word.empty()) {
            if (c == '\n') {
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

        if (endLine(word)) {
            lines.push_back({ });
            l++;
        }
    }

    //Clears the trailing empty vector, because the input ends with '\n'
    lines.pop_back();

    for (vector<string> line : lines) {
        line.back().erase(remove(line.back().begin(), line.back().end(), '\n'), line.back().end());

        for (int i = line.size() - 1; i > 0; i--) {
            cout << line[i] << " ";
        }

        cout << line[0] << endl;
    }

    return 0;
}
