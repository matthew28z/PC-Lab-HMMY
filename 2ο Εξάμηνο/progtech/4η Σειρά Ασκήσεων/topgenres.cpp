#include <iostream>
#include <unordered_map> //exei O(1) search
#include <string>
#include <vector>
#include <algorithm>
#include <cctype> //brhka oti exei to std::tolower gia ta grammata

int findInCharacters(char c) {
    static char characters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                                   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                   'u', 'v', 'w', 'x', 'y', 'z' }; 

    c = std::tolower(c);

    for (int i = 0; i < 26; i++) {
        if (characters[i] == c) {
            return i;
        }
    }

    throw std::invalid_argument("To Gramma Den Einai Latiniko"); //ypothetw oti einai latinika                 
}

bool alphabeticComparison(const std::string& A, const std::string& B) {
        bool AisLengthier = false;
        int maxLength = A.size();

        if (A.size() > B.size()) {
            AisLengthier = true;
            maxLength = B.size();
        }

        int i = 0;

        char a;
        char b;

        do { //blepei ta grammata me thn seira mexri na brei diafora h na teleiwsei mia lejh
            a = A.at(i);
            b = B.at(i++);

            if (i >= maxLength && a == b) {
                if (AisLengthier) {
                    return false;
                }

                return true;
            }
        } while (a == b);
        //Elegxei pio gramma einai mikrotero
        if (findInCharacters(a) > findInCharacters(b)) {
            return true;
        }

        return false;   
}

bool compare(const std::pair<std::string, std::size_t>& a, const std::pair<std::string, std::size_t>& b) {
    if (a.second == b.second) {
        return alphabeticComparison(a.first, b.first);
    }    

    if (a.second > b.second) {
        return true;
    }

    return false;
}

int main() {
    int N, G;
    std::cin >> N >> G;

    std::unordered_map<std::string, std::size_t> genresToRatings;
    std::unordered_map<std::string, std::string> moviesToGenres;

    for (int i = 0; i < N; i++) {
        std::string movieName, genreName;

        std::cin >> movieName >> genreName;

        genresToRatings.insert({ genreName, 0 });
        moviesToGenres.insert({ movieName, genreName });
    }

    char c = ' ';

    while (c != EOF) {
        c = getchar();

        std::string movieName, trash;
        std::cin >> movieName >> trash;

        int rating;
        std::cin >> rating;

        if (rating < 0 || rating > 100 || moviesToGenres.count(movieName) == 0) {
            continue;
        }

        genresToRatings.find(moviesToGenres.find(movieName) -> second) -> second++; 
    }

    const int length = genresToRatings.size();
    std::vector<std::pair<std::string, std::size_t>> genres;
    genres.reserve(length);

    for (const std::pair<std::string, std::size_t> entry : genresToRatings) {
        genres.push_back(entry);
    }

    std::sort(genres.begin(), genres.end(), compare);

    const int max = G < length ? G : length;

    for (int i = 0; i < max; i++) {
        std::cout << genres[i].first << ' ' << genres[i].second << std::endl;
    }

    return 0;
}
