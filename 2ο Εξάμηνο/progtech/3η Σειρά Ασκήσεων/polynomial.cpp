#include <iostream>
#include <cmath>

class Polynomial {
    protected:
    class Term {
        protected:
            int exponent;
            int coefficient;
            Term* next;

            Term(int exp, int coeff, Term* n) : exponent(exp), coefficient(coeff), next(n) { }
            friend class Polynomial;

        public:
            friend ostream& operator << (ostream& out, Term& t) {
                if (coeffiecient == 0) {
                    return out;
                }

                out << coefficient;

                if (exponent < 2) {
                    return out;
                }

                out << '^' << exponent;

                if (next == nullptr) {
                    return out;
                } else if (next -> coefficient > 0) {
                    return out << " + ";
                }

                return out << " - ";
            }

        private:
            double termValue(int x) {
                return std::pow(coefficient * x, exponent);
            }
    };

    public:
        Polynomial() : terms(new Term[1] {Term(0, 1, nullptr)}), size(1) { }

        Polynomial(const Polynomial& p) : terms(new Term[p.size]), size(p.size) {
            for (int i = 0; i < size; i++) {
                terms[i] = p.terms[i];
            }
        }

        Polynomial(Term* t, size_t s) : terms(t), size(s) { } //helps somplify expansion logic

        ~Polynomial() {
            delete[] terms;
        }

        Polynomial& operator = (const Polynomial& p) {
            if (this != &p) {
                delete[] terms;

                size = p.size;

                terms = new Term[size];

                for (int i = 0; i < size; i++) {
                    terms[i] = p.terms[i];
                }
            }

            return *this;
        }

        void addTerm(int expon, int coeff) {
            const size_t newSize = size + 1;
            
            Term* newTerms = new Term[newSize];

            bool exists = false

            unsigned int counter = 0;

            for (int i = 0; i < size; i++) {
                if (expon < terms[i].exponent) {
                    newTerms[i] = terms[i];
                } else if (expon > terms[i].exponent) {
                    if (!exists) {
                        exists = true;

                        newTerms[i] = Term(expon, coeff, terms[i])
                        
                        if (i > 0) { //checks if the added term is the new first term
                            newTerms[i - 1].next = newTerms[i];
                        }

                        continue;
                    } 
                    
                    newTerms[i] = terms[i];
                } else { // ==
                    terms[i].coefficient += coeff;

                    if (terms[i].coefficient == 0) {
                        counter++;
                    }

                    newTerms[i] = terms[i];
                }

            }

            newTerms[size] = terms[size - 1];

            if (counter > 0) { //saves space by not storing empty polynomials
                if (counter == newSize) {
                    *this = Polynomial();

                    return;
                }

                Term* actualTerms = new Term[newSize - counter];

                for (int i = 0, j = 0; i < newSize; i++) {
                    if (newTerms[i].coefficient != 0) {
                        actualTerms[j++] = newTerms[i];
                    } else {
                        if (j > 0) {
                            actualTerms[j - 1].next = newTerms[i].next;
                        }
                    }
                }

                delete[] newTerms;

                *this = Polynomial(actualTerms, newSize - counter);

                return;
            }

            *this = Polynomial(newTerms, newSize);
        }

        double evaluate(double x) {
            double res = 0;

            for (int i = 0; i < size; i++) {
                res += terms[i].termValue(x);
            }

            return res;
        }

        friend Polynomial operator + (const Polynomial& p, const Polynomial& q) {
            if (p.terms[0].exponent < q.terms[0].exponent) {
                return q + p;
            } 

            Term* maxTerms = new Term[p.size + q.size];
            const int maxSize = p.size + q.size;

            int counter = 0;
            int remember = 0;

            for (int i = 0; i < p.size; i++) {

                for (int j = remember; j < q.size; j++) {
                    if (p.terms[i].exponent > q.terms[j].exponent) {
                        maxTerms[counter++] = p.terms[i].exponent;
                        break;
                    } else if (p.terms[i].exponent == q.terms[j].exponent) {
                        remember = j;

                        maxTerms[counter - 1].next = Term(p.terms[i].exponent, p.terms[i].coefficient + q.terms[j].coefficient, nullptr);
                        maxTerms[counter++] = maxTerms[counter - 1].next;

                        break;
                    } else {
                        remember = j; 

                        if (j == q.size - 1) {
                            maxTerms[counter - 1].next = Term(p.terms[i].exponent, p.terms[i].coefficient, nullptr);
                            maxTerms[counter++] = maxTerms[counter - 1].next;
                        }
                    }
                }
            }

            Term* actualTerms = new Term[counter];

            for (int i = 0; i < counter; i++) {
                actualTerms[i] = maxTerms[i];
            }

            delete[] maxTerms;

            return Polynomial(actualTerms, counter);
        }

        friend Polynomial operator * (const Polynomial& p, const Polynomial& q) {
            Term a = Polynomial();

            Term* t = new Term[q.size];

            for (int i = 0; i < p.size; i++) {
                t[0] = Term(p.terms[i].exponent + q.terms[0].exponent, p.terms[i].coefficient * q.terms[0].coefficient, nullptr);

                for (int j = 1; j < q.size; j++) {
                    t[j - 1].next = Term(p.terms[i].exponent + q.terms[j].exponent, p.terms[i].coefficient * q.terms[j].coefficient, nullptr);
                    t[j] = t[j - 1].next;
                }

                a = a + Polynomial(t, q.size);
            }

            delete[] t;

            return a;
        }

        friend ostream& operator << (ostream& out, const Polynomial& p) {
            for (int i = 0; i < size; i++) {
                out << terms[i];
            }

            return out;
        }

    private:
        Term* terms;
        size_t size;
};
