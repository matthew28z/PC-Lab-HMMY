#include <iostream>
#include <string>
#include <random>
#include <vector>

class v005 : public Player {
    public:
        v005(const std::string& n) : Player(n) { }

        static int randomNum(int min, int max) {
            static std::random_device rd; 
            static std::mt19937 gen(rd()); 

            std::uniform_int_distribution<> distr(min, max);

            return distr(gen);
        }

        /*This function checks if an instant win is possible in this exact move/turn.
         *It does this by scanning to see if only one heap has any coins left.
         *If so, it returns the index of that heap, otherwise it returns -1.*/
        int canWin(const State& s) const {
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

        Move play(const State& s) override { // to override einai perisseio
            int source = -1; //represents none chosen

            int canWinIndex = canWin(s);

            if (canWinIndex != -1) { //checks for instant win (special case)
                return Move(canWinIndex, s.getCoins(canWinIndex), 0, 0);
            }

            //Tries to limit the success of its opponents
            int leastAmountOfPossibleMoves = 0;

            for (int i = 0; i < s.getHeaps(); i++) {
                if (s.getCoins(i) > 0) {
                    leastAmountOfPossibleMoves++;
                }
            }

            //We want leastAmountOfPossible moves to be as close to s.getPlayers() after our move

            if (leastAmountOfPossibleMoves > s.getPlayers()) {
                //Bring the amount down by removing coins from a random heap
                std::vector<int> sources;
                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 0) {
                        sources.push_back(i);
                    }
                }

                if (sources.size() > 0) { //redundant because of the check from canWin() yet good to have just in case
                    source = sources[randomNum(0, sources.size() - 1)];

                    return Move(source, s.getCoins(source), 0, 0); //Removes all the coins from that heap
                }
            } else if (leastAmountOfPossibleMoves == s.getPlayers()) { 
                //Try to not tamper with LAOPM
                std::vector<int> sources;

                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 1) {
                        sources.push_back(i);
                    }
                }

                if (sources.size() > 0) { //at least one heap has more than 1 coin
                    source = sources[randomNum(0, sources.size() - 1)];
                    return Move(source, s.getCoins(source) - 1, 0, 0); //leaves that heap with just one coin
                }
            } else { //< 
                /*Here the tactic is to split the coins from two random heaps coins
                  so that LAOPM will be incremented and two heaps will have many coins so that 
                  the game is prolonged*/
                std::vector<int> targets;
                std::vector<int> sources;
                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 1) {
                        sources.push_back(i);
                    } 


                    if (s.getCoins(i) < 1) { //== 0
                        targets.push_back(i);
                    }
                }

                if (sources.size() > 0 && targets.size() > 0) { //there is at least one empty heap and at least one heap with more than one coin
                    source = sources[randomNum(0, sources.size() - 1)];

                    int amount = s.getCoins(source) / 2;
                    /*2n + 1, 0 -> n, n (one coin lost)
                      2n, 0 -> n, n - 1 (one coin lost)*/
                    if (s.getCoins(source) % 2 == 0) {
                        return Move(source, amount, targets[randomNum(0, targets.size() - 1)], amount - 1);
                    }

                    /*Valid as for this point to be reached, source has 2n + 1 coins
                      with (int)n >= 1*/
                    return Move(source, amount + 1, targets[randomNum(0, targets.size() - 1)], amount);
                } else if (sources.size() > 0) { //at least one heap has more than 1 coin but no heap is empty
                    //We do the work here to save time
                    source = sources[randomNum(0, sources.size() - 1)];

                    for (int i = 0; i < s.getHeaps(); i++) {
                        if (i != source) {
                            targets.push_back(i);
                            /*2n + 1, 1 -> n + 1, n (one coin lost)
                              2n, 1 -> n, n (one coin lost)*/

                            if (s.getCoins(i) == 1) {
                                int amount = s.getCoins(source) / 2;

                                return Move(source, amount, i, amount - 1); 
                            }
                        }
                        //+ 1 so that if max - min = 1 -> amount = 1
                        int target = targets[randomNum(0, targets.size() - 1)];
                        
                        int amount = (s.getCoins(source) - s.getCoins(target) + 1) / 2;

                        if (amount > 0) { // max > min
                            return Move(source, amount, target, amount - 1);
                        }
                    }
                }       
            }

            //If this point is reached the program gives up on tactics and just plays the simplest legal move it can
            for (int i = 0; i < s.getHeaps(); i++) {
                if (s.getCoins(i) > 0) {
                    source = i;
                    break;
                }
            }

            return Move(source, 1, 0, 0);
        }

        const std::string& getType() const override {
            return type;
        }
    private:
        std::string type = std::string("\033[1;34mmatthew28z-v0.0.5\033[0m");
};
