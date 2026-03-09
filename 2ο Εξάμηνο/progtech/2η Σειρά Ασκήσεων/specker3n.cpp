#include <iostream>
#include <stdexcept> //for logic_error

using namespace std;

class Game {
    public:
        Game(int heaps, int players) : totalHeaps(heaps), totalPlayers(players), heapCoins(new int[heaps]), pl(new Player*[players]) { }
        
        ~Game() {
            delete[] heapCoins;

            for (int i = 0; i < totalPlayers; i++) {
                delete pl[i];
            }

            delete[] pl;
        }

        void addHeap(int coins) {
            if (coins >= 0 && currentHeap <= totalHeaps) { //theorisa eulogo oti den mporei na yparxei arnhtiko plhthos nomismatwn
                heapCoins[currentHeap] = coins;
                currentHeap++;
            } else {
                throw logic_error("invalid heap");
            }
        }

        void addPlayer(Player* player) {
            if (currentPlayer <= totalPlayers) {
                pl[currentPlayer] = player;
                currentPlayer++;
            } else {
                throw logic_error("invalid heap");
            }
        }

        void play(ostream& out) {
            State state(totalHeaps, heapCoins, totalPlayers);
            Player* nextPlayer;

            while(!state.winning()) {
                nextPlayer = pl[state.getPlaying()];

                out << "State: " << state << endl;

                const Move nextMove = nextPlayer -> play(state);
                out << *nextPlayer << " " << nextMove << endl;

                state.next(nextMove);
            }

            out << "State: " << state << endl;
            out << *nextPlayer << " wins" << endl;
        }

        int getPlayers() const {
            return totalPlayers;
        }

        const Player* getPlayer(int p) const {
            if (p < 0 || p >= totalPlayers) {
                throw logic_error("invalid heap");
            } 

            return pl[p];
        }
   private:
       Player** pl; //array of pointers pointing to a player
       int* heapCoins; //array of ints
       int totalPlayers;
       int totalHeaps;
       int currentHeap = 0; //keeps track of which heap is next
       int currentPlayer = 0; //keeps track of which player is next
};
