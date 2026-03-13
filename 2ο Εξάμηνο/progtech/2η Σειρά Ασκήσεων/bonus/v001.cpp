#include <iostream>
#include <string>
//Based on some quick calculations the program will compete with around 360 other participants

/*The algorithm follows a simple tactic, at first it checks if it can win instantly
 *by checking if only one heap has coins left. Otherwise, it tries to limit the least amount
 *amount of moves to the exact moves to exactly the amount of total players.
 *My assumption is that as the game goes on the gap between the least and most amount of possible moves
 *gets smaller and smaller. Hence, by having a program that excerts the highest control it can on each move
 *on the least amount of possible moves, it will have a higher chance of winning, especially as with the expected
 *number of opponents and thus heaps being quite high, the moves required for the game to end will be an advantage
 *for my player, or so I hope.
*/

class v001 : public Player {
    public:
        v001(const std::string& n) : Player(n) { }

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
                //Bring the amount down
                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 0) {
                        return Move(i, s.getCoins(i), 0, 0);
                    }
                }
            } else if (leastAmountOfPossibleMoves == s.getPlayers()) { 
                //Do not tamper with it if possible
                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 1) {
                        source = i;

                        if (s.getCoins(i) > 2) {
                            return Move(source, s.getCoins(i) - 1, 0, 0);
                        }

                        break;
                    }
                }

                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 0 && source > -1 && i != source) {
                        return Move(source, s.getCoins(source) - 1, i, s.getCoins(source) - 2);
                    }
                }
            } else { //<
                //Prolong the game
                int target = -1;

                for (int i = 0; i < s.getHeaps(); i++) {
                    if (s.getCoins(i) > 1) {
                        source = i;
                        break;
                    } 

                    if (s.getCoins(i) < 1) {
                        target = i;
                    }
                }

                if (source > -1) {
                    if (target > -1) {
                        return Move(source, 2, target, 1);
                    }

                    for (int i = source + 1; i < s.getHeaps(); i++) {
                        if (s.getCoins(i) < 1) {
                            return Move(source, 2, i, 1);
                        }
                    }
                }                
            }

            //If this point is reached the program gives up on tactics and just plays the first possible move it can
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
        std::string type = std::string("\033[1;34mmatthew28z-v0.0.1\033[0m");
};
