#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class lexicon {
    public:
        lexicon() : root(nullptr) { }

        ~lexicon() {
            delete root;
        }

        class wordNode {
            public:
                wordNode(std::string word, std::size_t d) : 
                    word(word), 
                    references(1), 
                    depth(d),
                    left(nullptr), 
                    right(nullptr) { }

                ~wordNode() {
                    delete left;
                    delete right;
                }

                friend ostream& operator << (ostream& out, wordNode& w) {

                    if (w.left != nullptr) {
                        out << *(w.left); //uses recursion
                    }

                    out << w.word << ' ' << w.references << std::endl; 
                    
                    if (w.right != nullptr) {
                        out << *(w.right);
                    }


                    return out;
                }

                friend lexicon;
            private:
                const std::string word;
                std::size_t references;
                std::size_t depth;
                wordNode* left;
                wordNode* right;
        };        

        wordNode* insertAndKeep(const string& s) {
            if (s.size() == 0) {
                throw invalid_argument("To Lexiko Den Mporei Na Exei Kenes Lejeis");
            }

            wordNode* prev = nullptr;
            wordNode* current = root;

            std::size_t depth = 0;

            bool wasLeft;

            while (current != nullptr) {
                depth++;

                if (current -> word == s) { //avoids duplication kai den psaxnei to dentro dyo fores
                    current -> references++;

                    return current;
                }

                prev = current;

                if (isSmaller(current -> word, s)) {
                    current = current -> right;
                    wasLeft = false;
                } else {
                    current = current -> left;
                    wasLeft = true;
                }
            }

            wordNode* newNode = new wordNode(s, depth);

            if (depth == 0) { //blepei an einai to prwto stoixeio
                root = newNode;
            } else if (wasLeft) { //ananewnei tous prohgoumenous
                prev -> left = newNode;
            } else {
                prev -> right = newNode;
            }

            return newNode;
        }

        void insert(const string& s) {
            insertAndKeep(s);
        }

        int lookup(const string& s) const {
            wordNode* entry = findMatch(s);

            return entry == nullptr ? 0 : entry -> references;        
        }

        int depth(const string& s) {
            wordNode* entry = findMatch(s);

            return entry == nullptr ? -1 : entry -> depth;
        }
        
        void replace(const string& s1, const string& s2) {
            if (s2.size() == 0) {
                throw invalid_argument("To Lexiko Den Mporei Na Exei Kenes Lejeis");
            }

            if (&s1 == &s2) { //an einai idia mhn kaneis tpt
                return; //edw mporei na hthele na diplasiasei ta references alla djr
            }

            if (root -> left == nullptr && root -> right == nullptr) {
                delete root; //clear memory

                root = nullptr;

                return;
            }

            wordNode* originOf1 = nullptr;
            wordNode* entry1 = root;
            bool isLeft;

            while (entry1 != nullptr && entry1 -> word != s1) {
                originOf1 = entry1;

                if (isSmaller(entry1 -> word, s1)) {
                    entry1 = entry1 -> right;
                    isLeft = false;
                } else {
                    entry1 = entry1 -> left;
                    isLeft = true;
                }
            }

            if (entry1 == nullptr) { //an den yparxei h 1 mhn kaneis tpt
                return;
            }
            
            wordNode* entry2 = findMatch(s2);

            wordNode* temp = entry1;

            if (entry1 -> left == nullptr) {
                entry1 = entry1 -> right;

                if (entry1 == root) {
                    root = root -> right;
                } else {
                    if (isLeft) {
                        originOf1 -> left = entry1;
                    } else{
                        originOf1 -> right = entry1;
                    }
                }


            } else {
                entry1 = entry1 -> left;
                entry1 -> right = entry1 -> right;

                if (entry1 == root) {
                    root = root -> left;
                } else {
                    if (isLeft) {
                        originOf1 -> left = entry1;
                    } else{
                        originOf1 -> right = entry1;
                    }
                }
            }

            entry1 -> depth--;

            if (entry2 == nullptr) {
                insertAndKeep(s2) -> references = entry1 -> references;
            } else {
                entry2 -> references += entry1 -> references;
            }
            
            return bringUp(entry1 -> left, temp -> left -> right);
        }

        wordNode* findMatch(const string& s) const { //returns nullptr if no match is found
            if (s.size() == 0) { //to lexiko den mporei na exei kenes lejeis
                return nullptr;
            }

            wordNode* c = root;

            while (c != nullptr && c -> word != s) {
                if (isSmaller(c -> word, s)) {
                    c = c -> right;
                } else {
                    c = c -> left;
                }
            }

            return c;
        }

        friend ostream& operator << (ostream& out, const lexicon& l) {
            if (l.root == nullptr) {
                return out;
            }
            
            out << *(l.root);

            return out;
        }

    private:
        wordNode* root;
        //to inline me afhnei na to dhlwsw sthn idia grammh me to static enw to static glitwnei to kathe klash na exei diko ths pinaka
        inline static  char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

        static int findInLetters(char c) {
            for (int i = 0; i < 26; i++) {
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

        void bringUp(wordNode* nodeToCorrect, wordNode* nodeLost) { //this function should never start without doing the first step manually
            if (nodeToCorrect == nullptr) {
                return; //stops
            }

            nodeToCorrect -> depth--;

            bringUp(nodeToCorrect -> left, nodeToCorrect -> right); //uses recursion

            nodeToCorrect -> right = nodeLost;
        }
};
