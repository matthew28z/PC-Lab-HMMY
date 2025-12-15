#include <iostream>
#include <vector>
#include <string>

int main() {
    char c = getchar();

    std::vector<std::string> line;
    std::string word;

    while (c != EOF) {
        if (c != ' ' && c != '\n' && c != EOF) {
            word += c;
        } else if (c == ' ') {
            if (!word.empty()) {
                line.push_back(word);
                word.clear();                
            }
        } else {
            if (!word.empty()) {
                std::cout << word;
            }

            if (!line.empty()) {  
                if (!word.empty()) {
                    std::cout << " ";
                    word.clear();
                }     

                for (int i = line.size() - 1; i > 0; i--) {
                    std::cout << line[i] << " ";
                }

                std::cout << line[0] << std::endl;

                line.clear();
            } else {
                std::cout << std::endl;
            }
        }

        c = getchar();
    }
}
