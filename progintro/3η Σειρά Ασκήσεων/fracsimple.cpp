#include "pzhelp"

void simplify(int a, int b) {
    //Krataei temp times
    int numerator = a;
    int denumerator = b;
    
    //Briskei gcd
    while (numerator > 0 && denumerator > 0) {
        if (numerator > denumerator) {
            numerator = numerator % denumerator;
        } else {
            denumerator = denumerator % numerator;
        }
    }
    
    int gcd = numerator + denumerator;
    
    //Pernaei to aplopoihmeno klasma
    numerator = a / gcd;
    denumerator = b / gcd;
    
    //Symfwna me thn askhsh
    if (numerator == 0) {
        denumerator = 1;
    }
    
    WRITELN(numerator, denumerator);
}

PROGRAM {
    int N = READ_INT();
    SKIP_LINE();
    
    for (int i = 0; i < N; i++) {
        char operation = getchar();
        //First
        int a = READ_INT();
        int b = READ_INT();
        
        //Second
        int c = READ_INT();
        int d = READ_INT();        
        
        SKIP_LINE();
        
        int num;
        int denum = b * d;
        
        if (operation == '+') {
            num = a * d + c * b;
        } else if (operation == '-') {
            num = a * d - c * b;
        } else if (operation == '*') {
            num = a * c;
        } else if (operation == '/') {
            num = a * d;
            denum = b * c;
        }
        
        simplify(num, denum);
        
    }
}
