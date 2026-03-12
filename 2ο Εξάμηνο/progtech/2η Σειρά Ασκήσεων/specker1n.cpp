#include <stdexcept> //for logic_error  
#include <iostream>  
  
using namespace std;  
  
class Move {  
    public:  
        //constructor  
        Move(int sh, int sc, int th, int tc) : source(sh),sourceAmount(sc), target(th), targetAmount(tc) { }  
  
        int getSource() const {  
            return source;  
        }  
  
        int getSourceCoins() const { //ypothetw ennoei to sc kai oxi posa exei ontws mesa  
            return sourceAmount;  
        }  
  
        int getTarget() const {  
            return target;  
        }  
  
        int getTargetCoins() const { //ypothetw ennoei to tc kai oxi posa exei ontws mesa  
            return targetAmount;  
        }  
  
        friend ostream& operator << (ostream& out, const Move& move) {  
            out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts ";  
  
            if (move.getTargetCoins() == 0) {  
                out << "nothing";  
                return out;  
            }  
  
            out << move.getTargetCoins() << " coins to heap " << move.getTarget();  
  
            return out;  
        }  
  
    private:  
        int source;  
        int sourceAmount;  
        int target;  
        int targetAmount;  
};  
  
class State {  
    public:  
        //constructor  
        State(int h, int c[], int n) : heaps(h), players(n), currentPlayer(0) {  
            heapCoins = new int[heaps];  
  
            for (int i = 0; i < heaps; i++) {  
                heapCoins[i] = c[i];  
            }  
        }  
  
        //destructor  
        ~State() {  
            delete[] heapCoins;  
        }  
  
        void next(const Move& move) {  
            //Checks source and target validities  
            int moveSource = move.getSource();  
            bool validSource = moveSource >= 0 && moveSource < heaps;  
  
            int moveTarget = move.getTarget();  
            bool validTarget = moveTarget >= 0 && moveTarget < heaps;  
  
            if (validSource && validTarget) { //prwta elegxos oriwn  
                //Checks the amounts  
                int amountSource = move.getSourceCoins();  
                bool validSAmount = amountSource > 0 && amountSource <= heapCoins[moveSource];  
  
                int amountTarget = move.getTargetCoins();  
                bool validTAmount = amountTarget >= 0 && amountTarget < amountSource;  
  
                if (validSAmount && validTAmount) { //Ypothetw oti thelei apla na allajw ta dedomena m  
                    heapCoins[moveSource] -= amountSource;  
                    heapCoins[moveTarget] += amountTarget;  
  
                    if (currentPlayer == players - 1) {  
                        currentPlayer = 0;  
                    } else {  
                        currentPlayer++;  
                    }  
                } else {  
                    throw logic_error("invalid heap");  
                }  
            } else {  
                throw logic_error("invalid heap");  
            }  
        }   
  
        bool winning() const { //Ypothetw oti thelei na dw an einai adeio to heapCoins  
            //Check if no heap has any coins left  
            for (int i = 0; i < heaps; i++) {  
                if (heapCoins[i] != 0) {  
                    return false;  
                }  
            }  
  
            return true;  
        }  
  
        int getHeaps() const {  
            return heaps;  
        }  
  
        int getCoins(int h) const {  
            if (h < 0 || h >= heaps) {  
                throw logic_error("invalid heap");  
            }  
  
            return heapCoins[h];  
        }  
  
        int getPlayers() const {  
            return players;  
        }  
  
        int getPlaying() const {  
            return currentPlayer;  
        }  
  
        friend ostream& operator << (ostream& out, State& state) {  
            int heapsN = state.getHeaps();  
  
            for (int i = 0; i < heapsN - 1; i++) {  
                out << state.getCoins(i) << ", ";  
            }  
  
            out << state.getCoins(heapsN - 1) << " with " << state.getPlaying() << '/' << state.getPlayers() << " playing next";  
  
            return out;  
        }  
    private:  
        int* heapCoins;  
        int heaps;  
        int players;  
        int currentPlayer; //sthn pragmatikothta einai nextPlayer alla brm na to allajw  
};  
