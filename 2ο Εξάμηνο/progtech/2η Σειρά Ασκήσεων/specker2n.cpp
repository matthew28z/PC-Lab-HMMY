#include <iostream>
#include <string>

using namespace std;

class Player {
    public:
        //constructor
        Player(const string& n) : name(n) { }

        virtual ~Player() { }

        virtual const string& getType() const = 0;

        virtual Move play(const State& s) = 0;

        friend ostream& operator << (ostream& out, Player& player) {
            out << player.getType() << " player " << player.name;

            return out;
        }

    protected: //oxi private gia na to blepoun kai oi ypoloipoi
        string name;
};

class GreedyPlayer : public Player {
    public:
        GreedyPlayer(const string& n) : Player(n) { }

        Move play(const State& s) override { // to override einai perisseio
            int source = 0;
            int max = s.getCoins(0);

            for (int i = 1; i < s.getHeaps(); i++) {
                int coins = s.getCoins(i);

                if (coins > max) {
                    max = coins;
                    source = i;
                }
            }

            return Move(source, max, 0, 0);
        }

        const string& getType() const override {
            return type;
        }
    private:
        string type = string("Greedy");
};

class SpartanPlayer : public Player {
    public:
        SpartanPlayer(const string& n) : Player(n) { }

        Move play(const State& s) override { // to override einai perisseio
            int source = 0;
            int max = s.getCoins(0);

            for (int i = 1; i < s.getHeaps(); i++) {
                int coins = s.getCoins(i);

                if (coins > max) {
                    max = coins;
                    source = i;
                }
            }

            return Move(source, 1, 0, 0);
        }

        const string& getType() const override {
            return type;
        }
    private:
        string type = string("Spartan");
};

class SneakyPlayer : public Player {
    public:
        SneakyPlayer(const string& n) : Player(n) { }

        Move play(const State& s) override { // to override einai perisseio
            int source = 0;
            int min = s.getCoins(0);

            for (int i = 1; i < s.getHeaps(); i++) {
                int coins = s.getCoins(i);

                if ((coins < min || min == 0) && coins > 0) { //does not allow k to be 0
                    min = coins;
                    source = i;
                }
            }

            return Move(source, min, 0, 0);
        }

        const string& getType() const override {
            return type;
        }
    private:
        string type = string("Sneaky");
};

class RighteousPlayer : public Player {
    public:
        RighteousPlayer(const string& n) : Player(n) { }

        Move play(const State& s) override { // to override einai perisseio
            int sourceMin = 0;
            int min;

            int sourceMax = 0;
            int max;

            if (s.getHeaps() > 1) {
                if (s.getCoins(0) < s.getCoins(1)) {
                    sourceMax = 1;
                } else if (s.getCoins(0) > s.getCoins(1)) {
                    sourceMin = 1;             
                }

                max = s.getCoins(sourceMax);
                min = s.getCoins(sourceMin);

                for (int i = 2; i < s.getHeaps(); i++) {
                    int coins = s.getCoins(i);

                    if (coins < min) {
                        min = coins;
                        sourceMin = i;
                    }
                    //oxi else if gt mporei na exoume min == max
                    if (coins > max) {
                        max = coins;
                        sourceMax = i;
                    }
                }

                return Move(sourceMax, max / 2, sourceMin, max / 2 - 1);
            }

            return Move(0, s.getCoins(0) / 2, 0, s.getCoins(0) / 2 - 1);
        }

        const string& getType() const override {
            return type;
        }
    private:
        string type = string("Righteous");
};
