#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray {
    protected:
    class Row {
        public:
            Row(ChessBoardArray& a, int i) : c(a), row(i) { }

            int& operator [] (int i) const {
                return c.select(row, i);
            }

        private:
            ChessBoardArray& c;
            const int row;
    };

    class ConstRow {
        public:
            ConstRow(const ChessBoardArray& a, int i) : c(a), row(i) { }

            int operator [] (int i) const {
                return c.select(row, i);
            }

        private:
            const ChessBoardArray& c;
            const int row;
    };

    public:
        ChessBoardArray(unsigned size = 0, unsigned base = 0) : rootSize(size), start(base), length(size * size / 2 + size * size % 2), board(new int[length + 1] {}) { }

        ChessBoardArray(const ChessBoardArray& a) : rootSize(a.rootSize), start(a.start), length(a.rootSize * a.rootSize / 2 + a.rootSize * a.rootSize % 2), board(new int[length]) {
            for (int i = 0; i < length; i++) {
                board[i] = a.board[i];
            }

            board[length] = 0;
        }

        ~ChessBoardArray() {
            delete[] board;
        }

        ChessBoardArray& operator = (const ChessBoardArray& a) {
            if (this != &a) {
                delete[] board;

                rootSize = a.rootSize;
                start = a.start;
                length = a.length;

                board = new int[length + 1];

                for (int i = 0; i < length; i++) {
                    board[i] = a.board[i];
                }

                board[length] = 0; //represents all the black spots
            }

            return *this;
        };

        int& select(int i, int j) {
            const unsigned int index = loc(i, j);

            if (index == length) {
                throw out_of_range("Black spots cannot be reassigned");
            }

            return board[index];
        }

        int select(int i, int j) const {
            return board[loc(i, j)];
        }

        const Row operator [] (int i) {
            return Row(*this, i);
        }
        const ConstRow operator [] (int i) const {
            return ConstRow(*this, i);
        }

        friend ostream& operator << (ostream& out, const ChessBoardArray& a) {
            const int limit = a.rootSize + a.start;

            for (int i = a.start; i < limit; i++) {
                for (int j = a.start; j < limit; j++) {
                    out << setw(4) << a.select(i, j);
                }

                out << endl;
            }

            return out;
        }

    private:
        unsigned int rootSize;
        unsigned int start;
        size_t length;

        int* board;

        unsigned int loc(int i, int j) const {
            if (i >= rootSize + start || j >= rootSize + start || j < start || i < start) {
                throw out_of_range("error");
            }
            const unsigned int base1Col = j - start + 1;
            const unsigned int base1Row = i + 1 - start;

            const bool isOddRow = base1Row % 2 == 1;
            const bool isOddCol = base1Col % 2 == 1;

            if ((isOddRow && !isOddCol) || (!isOddRow && isOddCol)) {
                return length; //then select will output 0
            } else if (i == start && j == start) {
                return 0;
            } else if (j == start) { //i - 1 is safe as we first check if i == start
                return 1 + loc(i - 1, start + rootSize - 1 - rootSize % 2);
            } else if (j == start + 1) {
                return 1 + loc(i - 1, start + rootSize - 1 - (rootSize + 1) % 2);
            }

            //If this point is reached we are on a white block that is not the first of its row
            return 1 + loc(i, j - 2);
        }
};
