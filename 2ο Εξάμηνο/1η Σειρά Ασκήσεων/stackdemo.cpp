#include <iostream>

using namespace std;

template <typename T>
class stack {
    public:
        stack(int size) : data(new T[size]), s(size), end(-1) { }

        stack(const stack& s) : data(new T[s.s]), s(s.s), end(s.end) { //copier
            if (s.end != -1) { //to problhma mallon einai epeidh leei const
                for (int i = 0; i <= s.end; i++) { //copies up to the last supplied element of s
                    data[i] = s.data[i];
                }
            }
        }

        ~stack() {
            delete[] data;
        }

        const stack& operator = (const stack& s) {
            //return stack(s);
            //checks if s !== this
            if (this != &s) {
                //Clears past data
                delete[] this -> data;

                this -> data = new T[s.s];
                this -> end = s.end;
                this -> s = s.s;

                if (s.end != -1) { //kapoio problhma yparxei an balv to .empty()
                    for (int i = 0; i <= s.end; i++) {
                        this -> data[i] =  s.data[i];
                    }
                }
            }
            return *this;
        }

        bool empty() {
            return end == -1;
        }

        void push(const T& x) {
            //Den ginetai elegxos opws leei h askhsh
            data[end + 1] = x;
            end++;
        }

        T pop() {
            //pali xwris elegxo
            end--;

            return data[end + 1];
        }

        int size() {
            return s;
        }

        friend ostream& operator << (ostream& out, const stack& s) {
            out << '[';

            if (s.end != -1) { //Den ebala const meta ta size kai empty gt h askhsh den ta xe an kai pisteyw auto ftaiei
                for (int i = 0; i < s.end; i++) {
                    out << s.data[i] << ',' << ' ';
                }

                out << s.data[s.end];
            }

            out << ']';

            return out;
        }
    private:
        T* data;
        int s;
        int end; //index of the last element
};

#ifndef CONTEST
int main () {
// let’s play with integers...
stack<int> s(10);
cout << "s is empty: " << s << endl;
s.push(42);
cout << "s has one element: " << s << endl;
s.push(17);
s.push(34);
cout << "s has more elements: " << s << endl;
cout << "How many? " << s.size() << endl;
stack<int> t(5);
t.push(7);
cout << "t: " << t << endl;
t = s;
cout << "popping from s: " << s.pop() << endl;

s.push(8);
stack<int> a(s);
t.push(99);
a.push(77);
cout << "s: " << s << endl;
cout << "t: " << t << endl;
cout << "a: " << a << endl;
// now with doubles...
stack<double> c(4);
c.push(3.14);
c.push(1.414);
cout << "c contains doubles " << c << endl;
// and with characters...
stack<char> k(4);
k.push('$');
cout << "k contains a character " << k << endl;
}
#endif
