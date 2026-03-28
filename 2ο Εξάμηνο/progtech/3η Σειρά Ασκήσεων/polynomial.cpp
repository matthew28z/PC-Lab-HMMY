#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
    protected:
    class Term {
        protected:
            int exponent;
            int coefficient;
            Term* next;
            Term(int exp, int coeff, Term* n) : exponent(exp), coefficient(coeff), next(n) { }
            friend class Polynomial;

            //O compiler elege oti prepei na nai kai edw 
            friend Polynomial operator + (const Polynomial& p, const Polynomial& q);
            friend Polynomial operator * (const Polynomial& p, const Polynomial& q);
            friend ostream& operator << (ostream& out, const Polynomial& p);

        public:
            friend ostream& operator << (ostream& out, const Term& t) {
                if (std::abs(t.coefficient) != 1 && t.exponent != 0) { //dont push 1
                    out << std::abs(t.coefficient);
                }

                if (t.exponent == 0) {
                    if (t.coefficient > 0) {
                        return out << " + " << std::abs(t.coefficient);
                    }

                    return out << " - " << std::abs(t.coefficient);
                }

                out << 'x';

                if (t.exponent == 1) {
                    return out;
                }

                out << '^' << t.exponent;

                if (t.next != nullptr) {
                    if (t.next -> exponent > 0) {
                        if (t.next -> coefficient > 0) {
                            return out << " + ";
                        }

                        return out << " - "; //terms with coeff 0 are intended to not be stored
                    }
                }


                return out;
            }

        private:
            double termValue(int x) {

                return std::pow(x, exponent) * coefficient;
            }
    };

    public:
        Polynomial() : first(nullptr) { }

        Polynomial(const Polynomial& p) {
            if (p.first != nullptr) {
                first = new Term(p.first -> exponent, p.first -> coefficient, nullptr);
                Term* pr = first;
                Term* n = nullptr;

                Term* t = p.first -> next;

                while (t != nullptr) {
                    n = new Term(t -> exponent, t -> coefficient, nullptr);

                    pr -> next = n;
                    pr = n;

                    t = t -> next;
                }                
            } else {
                first = nullptr;
            }
        }

        Polynomial(Term *f) : first(f) { } // helps later

        ~Polynomial() {
            if (first != nullptr) {
                Term* t = first;
                Term* n = first -> next;

                while (t != nullptr) {
                    delete t;

                    t = n;
                    
                    if (n != nullptr) {
                        n = n -> next;
                    }
                }
            }
        }

        Polynomial& operator = (const Polynomial& p) {
            if (this != &p) {
                Term* temp = first;

                while (temp != nullptr) {
                    Term* t = temp -> next;

                    delete temp;

                    temp = t;
                }
                
                if (p.first != nullptr) {
                    first = new Term(p.first -> exponent, p.first -> coefficient, nullptr);
                    Term* pr = first;
                    Term* n = nullptr;

                    Term* t = p.first -> next;

                    while (t != nullptr) {
                        n = new Term(t -> exponent, t -> coefficient, nullptr);

                        pr -> next = n;
                        pr = n;

                        t = t -> next;
                    }  
                } else {
                    first = nullptr;
                }
            }

            return *this;
        }

        void addTerm(int expon, int coeff) {
            if (coeff != 0) { //does nothing if the term is 0
                if (first != nullptr) { //checks if the polynomial is empty
                    Term* t = first;
                    Term* p = nullptr;

                    while (t != nullptr && t -> exponent > expon) {
                        p = t;
                        t = t -> next;
                    }

                    if (p == nullptr) { //checks if the value added should be the new first
                        if (first -> exponent == expon) {
                            int res = first -> coefficient + coeff;

                            if (res != 0) {
                                first -> coefficient = res;
                            } else {
                                Term* temp = first;
                                first = first -> next;

                                delete temp;
                            }
                        } else {
                            first = new Term(expon, coeff, first);
                        }
                    } else if (t == nullptr) { //checks if the value added should be the new last
                        p -> next = new Term(expon, coeff, nullptr); //no need for a check  
                    } else {
                        if (t -> exponent == expon) {
                            int res = t -> coefficient + coeff;

                            if (res != 0) {
                                t -> coefficient = res;
                            } else {
                                p -> next = t -> next; //remove the empty Term

                                delete t; //free the memory
                            }
                        } else {
                            p -> next = new Term(expon, coeff, t);
                        }
                    }
                } else {
                    first = new Term(expon, coeff, nullptr);
                }
            }
        }

        double evaluate(double x) {
            if (first == nullptr) {
                return 0;
            }

            double res = 0;

            Term* t = first;

            while (t != nullptr) {
                res += t -> termValue(x);

                t = t -> next;
            }

            return res;
        }

        friend Polynomial operator + (const Polynomial& p, const Polynomial& q) {
            if (q.first == nullptr) { //covers the case of both being nullptr
                return Polynomial(p);
            } else if (p.first == nullptr) {
                return Polynomial(q);
            }

            Term* t1 = p.first;
            Term* t2 = q.first;

            adjust(t1, t2);

            Term* newFirst = new Term(t1 -> exponent, t1 -> coefficient, nullptr); //creates the first Term

            if (t1 -> exponent == t2 -> exponent) { 
                newFirst -> coefficient += t2 -> coefficient;
                t2 = t2 -> next;
            }

            Term* n = nullptr;
            Term* pr = newFirst;

            t1 = t1 -> next;

            adjust(t1, t2);

            while (t1 != nullptr) {
                n = new Term(t1 -> exponent, t1 -> coefficient, nullptr);
                pr -> next = n;

                Term* temp = pr; //back-up
                pr = n;

                if (t2 != nullptr) {
                    if (t1 -> exponent == t2 -> exponent) {
                        int res = n -> coefficient + t2 -> coefficient;

                        if (res != 0) {
                            n -> coefficient += t2 -> coefficient;                        
                        } else {
                            delete n;

                            n = nullptr;
                            pr = temp;
                            pr -> next = nullptr;
                        }

                        t2 = t2 -> next;
                    }
                }

                t1 = t1 -> next;

                adjust(t1, t2);
            }

            if (newFirst -> coefficient == 0) {
                Term* temp = newFirst;

                delete newFirst;

                newFirst = temp -> next;
            }

            return Polynomial(newFirst);
        }

        friend Polynomial operator * (const Polynomial& p, const Polynomial& q) {
            if (p.first == nullptr || q.first == nullptr) {
                return Polynomial();
            }

            Term* t = p.first;

            Polynomial a = Polynomial();

            cout << endl;
            while(t != nullptr) {
                Polynomial b(q);
                Term* bT = b.first;

                while (bT != nullptr) {
                    bT -> coefficient *= t -> coefficient;
                    bT -> exponent += t -> exponent;

                    bT = bT -> next;
                }

                a = a + b;
                t = t -> next;
            }

            return a;
        }

        friend ostream& operator << (ostream& out, const Polynomial& p) {
            Term* t = p.first;

            if (t == nullptr) {
                return out << 0;
            }

            while (t != nullptr) {
                out << *t;

                t = t -> next;
            }

            return out;
        }

    private:
        Term* first;

        static void adjust(Term*& a, Term*& b) {
            if (a != nullptr && b != nullptr) {
                if (a -> exponent < b -> exponent) { //a must be the bigger one
                    Term* temp = a;

                    a = b;
                    b = temp;
                } 
            } else if (a == nullptr) {
                a = b;
                b = nullptr;
            }
        }
};
