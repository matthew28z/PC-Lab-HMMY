#include <iostream>
#include <unordered_map> //exei O(1) search
#include <string>
#include <vector>
#include <algorithm>
#include <cctype> //brhka oti exei to std::tolower gia ta grammata

class Movie {
    public:
        Movie(const std::string& s) : name(s) { }
        
        std::string getName() const {
            return name;
        }

        int getAverageRating() const {
            if (totalReviews == 0) {
                return 0;
            }

            return totalScore / totalReviews;
        }

        void addReview(int rating) {
            if (rating < 0 || rating > 100) {
                return;
            }

            totalScore += rating;
            totalReviews++;
        }

        friend bool operator < (Movie& a, Movie& b) {
            const int A = a.getAverageRating();
            const int B = b.getAverageRating();

            if (A == B) {
                return isSmaller(a.name, b.name); //ta mikra pane pisw
            }

            if (A < B) {
                return false;// einai anapoda gia na mhn emfanizontai ta mikra mprosta
            } 

            return true;
        }

        friend std::ostream& operator << (std::ostream& out, const Movie& m) {
            return out << m.name << ' ' << m.getAverageRating();
        }

    private:
        std::size_t totalScore = 0;
        std::size_t totalReviews = 0;
        std::string name; //oxi const gia na leitourgei to sort

        //Ta phra apo to lexicon.cpp kai ta peiraja
        inline static char letters[36] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                                            'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                            'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4',
                                            '5', '6', '7', '8', '9', '_' }; //ebala tous epipleon xarakthres den nmz na yparxei thema me ta kefalaia
        static int findInLetters(char c) {
            c = std::tolower(c);

            for (int i = 0; i < 36; i++) {
                if (letters[i] == c) {
                    return i;
                }
            }

            throw std::invalid_argument("To Gramma Den Einai Mikro Latiniko");
        };

        static bool isSmaller(std::string A, std::string B) { //this function assumes A and B are not the same
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
            if (findInLetters(a) > findInLetters(b)) {
                return false;
            }

            return true;
        }
};

int main() {
    int K;
    std::cin >> K;

    std::unordered_map<std::string, Movie> movies;

    char c = ' ';

    while (c != EOF) {
        std::string movieName;
        std::cin >> movieName;

        std::string trash;
        std::cin >> trash; //we dont need to track the user's name, ara sbhston

        int rating;
        std::cin >> rating;

        if (movies.count(movieName) == 1) { //gyrnaei 1 h 0 gt einai monadika den me afhne na balw to .contains()
            movies.find(movieName) -> second.addReview(rating); //to find gyrnaei iterator gia ta pairs tou xarti me to second na einai h timh
        } else {
            Movie m = Movie(movieName);
            m.addReview(rating);

            movies.insert({ movieName, m }); //thetw kleidi to onoma ths tainia kai timh to Movie instance
        }

        c = getchar(); //an ta exw skeftei kala tha einai h \n h EOF
    }

    int tracker = 0;

    const size_t moviesFound = movies.size();

    std::vector<Movie> mVector;
    mVector.reserve(moviesFound);

    for (const std::pair<std::string, Movie> entry : movies) {
        mVector.push_back(entry.second);
    }

    std::sort(mVector.begin(), mVector.end());

    const size_t border = moviesFound < K ? moviesFound : K;

    for (int i = 0; i < border; i++) {
        std::cout << mVector[i] << std::endl;
    }
}
