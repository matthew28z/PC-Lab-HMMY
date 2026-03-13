#include <string>

class v004 : public Player {
    public:
        v004(const std::string& n) : Player(n) { }

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
                //Bring the amount down by removing the most amount of coins possible
                for (int i = 0; i < s.getHeaps(); i++) {
                    if ((source == -1 || s.getCoins(i) > s.getCoins(source)) && s.getCoins(i) > 0) {
                        source = i;
                    }
                }

                if (source > -1) { //redundant because of the check from canWin() yet good to have just in case
                    return Move(source, s.getCoins(source), 0, 0); //Removes the largest amount of coins possible
                }
            } else if (leastAmountOfPossibleMoves == s.getPlayers()) { 
                //We will try to remove the largest amount of coins whilst not tampering with LAOPM
                for (int i = 0; i < s.getHeaps(); i++) {
                    if ((source == -1 || s.getCoins(i) > s.getCoins(source)) && s.getCoins(i) > 1) {
                        source = i;
                    }
                }

                if (source > -1) { //at least one heap has more than 1 coin
                    return Move(source, s.getCoins(source) - 1, 0, 0); //leaves that heap with just one coin
                }
            } else { //< 
                /*Here the tactic is to split the coins from the heap with the most coins
                  so that LAOPM will be incremented and two heaps will have many coins so that 
                  the game is prolonged*/
                int target = -1;

                for (int i = 0; i < s.getHeaps(); i++) {
                    if ((source == -1 || s.getCoins(i) > s.getCoins(source)) && s.getCoins(i) > 1) {
                        source = i;
                    } 

                    /*This will put the coins to the last empty index (if it exists) hoping to hide them
                     from other players that check for the first heap that matches their conditions*/
                    if (s.getCoins(i) < 1) { //== 0
                        target = i;
                    }
                }

                if (source > -1 && target > -1) { //there is at least one empty heap and at least one heap with more than one coin
                    int amount = s.getCoins(source) / 2;
                    /*2n + 1, 0 -> n, n (one coin lost)
                      2n, 0 -> n, n - 1 (one coin lost)*/
                    if (s.getCoins(source) % 2 == 0) {
                        return Move(source, amount, target, amount - 1);
                    }

                    /*Valid as for this point to be reached, source has 2n + 1 coins
                      with (int)n >= 1*/
                    return Move(source, amount + 1, target, amount);
                } else if (source > -1) { //at least one heap has more than 1 coin
                    //No heap is empty
                    for (int i = 0; i < s.getHeaps(); i++) {
                        if (target == -1 || s.getCoins(i) < s.getCoins(target)) {
                            target = i;
                            /*2n + 1, 1 -> n + 1, n (one coin lost)
                              2n, 1 -> n, n (one coin lost)*/

                            if (s.getCoins(i) == 1) {
                                int amount = s.getCoins(source) / 2;

                                return Move(source, amount, i, amount - 1); 
                            }
                        }
                        //+ 1 so that if max - min = 1 -> amount = 1
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
        std::string type = std::string("\033[1;34mmatthew28z-v0.0.4\033[0m");
};
