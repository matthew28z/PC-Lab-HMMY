#include <iostream>  
#include <string>  
  
class lexicon {  
    public:  
        lexicon() : root(nullptr) { }  
        ~lexicon() {  
            delete root;  
        }  
          
        void insert(const std::string& s) {  
            if (root == nullptr) {  
                root = new node(s);  
                  
                return;  
            }  
              
            node* prev = nullptr;  
            node* current = root;  
            bool wasLeft;  
              
            while (current != nullptr) {  
                if (s == current -> word) {  
                    current -> ref++;

                    return;  
                }  
                  
                prev = current;  
                  
                if (s < current -> word) {  
                    wasLeft = true;  
                    current = current -> left;  
                      
                    continue;  
                }  
                  
                wasLeft = false;  
                current = current -> right;  
            }  
              
            if (wasLeft) {  
                prev -> left = new node(s);  
                  
                return;  
            }  
              
            prev -> right = new node(s);  
        }  
          
        int lookup(const std::string& s) const {  
            node* current = root;  
              
            while (current != nullptr) {  
                if (current -> word == s) {  
                    return current -> ref;  
                }  
                  
                if (s < current -> word) {  
                    current = current -> left;  
                      
                    continue;  
                }  
                  
                current = current -> right;  
            }  
              
            return 0;  
        }  
      
        int depth(const std::string& s) const {  
            node* current = root;  
            int depth = 0;  
              
            while (current != nullptr) {  
                if (current -> word == s) {  
                    return depth;  
                }  
                  
                depth++;  
                  
                if (s < current -> word) {  
                    current = current -> left;  
                      
                    continue;  
                }  
                  
                current = current -> right;  
            }  
              
            return -1;  
        }  
          
        void replace(const std::string& s1, const std::string& s2) {  
            node* prev1 = nullptr;  
            node* entry1 = root;  
            bool wasLeft;  
              
            while (entry1 != nullptr) {  
                if (entry1 -> word == s1) {  
                    break;  
                }  
                  
                prev1 = entry1;  
                  
                if (s1 < entry1 -> word) {  
                    entry1 = entry1 -> left;  
                    wasLeft = true;  
                      
                    continue;  
                }  
                  
                entry1 = entry1 -> right;  
                wasLeft = false;  
            }  
              
            if (entry1 == nullptr) {  
                return;  
            }  

            int ref1 = entry1 -> ref;
            
            if (entry1 -> left == nullptr && entry1 -> right == nullptr) {
                if (prev1 == nullptr) {
                    root = nullptr;
                } else {
                    if (wasLeft) {
                        prev1 -> left = nullptr;
                    } else {
                        prev1 -> right = nullptr;
                    }
                }

                delete entry1;
            } else if (entry1 -> left == nullptr) {  
                if (prev1 == nullptr) {  
                    root = root -> right;  
                } else {  
                    if (wasLeft) {  
                        prev1 -> left = entry1 -> right;
                    } else {  
                        prev1 -> right = entry1 -> right;  
                    }  
                }

                delete entry1;
            } else if (entry1 -> right == nullptr) {  
                if (prev1 == nullptr) {  
                    root = root -> left;  
                } else {  
                    if (wasLeft) {  
                        prev1 -> left = entry1 -> left;  
                    } else {  
                        prev1 -> right = entry1 -> left;  
                                    
                    }  
                }

                delete entry1;
            } else {  
                node* replacement = entry1 -> right;

                while (replacement -> left != nullptr) {
                    replacement = replacement -> left;
                }

                entry1 -> word = replacement -> word;
                entry1 -> ref = replacement -> ref;

                delete replacement;
            }

            node* entry2 = find(s2);

            if (entry2 == nullptr) {
                insert(s2);

                find(s2) -> ref += ref1;

                return;
            } 

            entry2 -> ref += ref1;
        }

        friend std::ostream& operator << (std::ostream& out, const lexicon& l) {
            if (l.root == nullptr) {
                return out;
            }

            return out << *l.root;
        }
    private:  
        struct node {  
                node(const std::string& s) : word(s), ref(1), left(nullptr), right(nullptr) { }  
                ~node() {  
                    delete left;  
                    delete right;  
                }      
                
                friend std::ostream& operator << (std::ostream& out, const node& n) {
                    if (n.left != nullptr) {
                        out << *n.left;
                    }

                    out << n.word << ' ' << n.ref << std::endl;

                    if (n.right != nullptr) {
                        return out << *n.right;
                    }

                    return out;
                }
                  
                std::string word;  
                std::size_t ref;  
                node* left;  
                node* right;  
        };  

        node* find(const std::string& s) {
            node* current = root;
              
            while (current != nullptr) {  
                if (current -> word == s) {  
                    return current;  
                }   
                  
                if (s < current -> word) {  
                    current = current -> left;    
                      
                    continue;  
                }  
                  
                current = current -> right;  
            }

            return nullptr;
        }
          
        node* root;  
};  

