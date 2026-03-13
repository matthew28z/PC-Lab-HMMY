#include <string>
#include <random>

class v003 : public Player {
    public:
    v003(const string& n) : Player(n) { }

    static int canWin(const State& s) {
        int res = -1; //means it can't win instantly

        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) != 0) {
                if (res != -1) {
                    return -1; //cannot win
                }

                res = i;
            }
        }

        return res;
    }

    static int randomNum(int min, int max) {
        static std::random_device rd; 
        static std::mt19937 gen(rd()); 

        std::uniform_int_distribution<> distr(min, max);

        return distr(gen);
    }

    Move play(const State& s) override {
        int cW = canWin(s);

        if (cW != -1) {
            return Move(cW, s.getCoins(cW), 0, 0);
        }


        int r = randomNum(0, s.getHeaps() - 1);

        if (s.getCoins(r) > 1) {
            return Move(r, s.getCoins(r) - 1, 0, 0);
        }

        do {
            r = randomNum(0, s.getHeaps() - 1);
        } while (s.getCoins(r) == 0);

        return Move(r, s.getCoins(r), 0, 0);
    }

    const string& getType() const override {
        return type;
    }
private:
    string type = string("\033[1;34mmatthew28z-v0.0.3\033[0m");
};
