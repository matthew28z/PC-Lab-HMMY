#include "pzhelp"

void simplify(int a, int b) {
    //Krataei se apolyto gia na leitourgei h aplopoihsh
    int numerator = abs(a);
    int denumerator = abs(b);
    
    //Euclid
    while (numerator > 0 && denumerator > 0) {
        if (numerator > denumerator) {
            numerator = numerator % denumerator;
        } else {
            denumerator = denumerator % numerator;
        }
    }
    
    int gcd = numerator + denumerator;
    
    //Se apolyto giati to proshmo paei sto intPart
    numerator = abs(a) / gcd;
    denumerator = abs(b) / gcd;
    
    //Bgazei ton akeraio mesa apo to klasma
    int intPart = numerator / denumerator; //einai akeraia diairesh
    
    numerator = numerator - intPart * denumerator;
    
    
    //Symfwna me thn askhsh
    if (numerator == 0) { 
        denumerator = 1;
    } 
    
    if ((a > 0 && b < 0) || (a < 0 && b > 0)) { // einai arnhtiko
        //To WRITE() den allazei grammh
        WRITE("-");
    }
    WRITELN(intPart, numerator, denumerator);
}

PROGRAM {
    bool goodInput = true;
    
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
        
        if (b == 0 || d == 0) {
            WRITELN("error");
        } else {
            int num;
            int denum = b * d;
            
            if (operation == '+') {
                num = a * d + c * b;
            } else if (operation == '-') {
                num = a * d - c * b;
            } else if (operation == '*') {
                num = a * c;
            } else if (operation == '/') {
                if (c == 0) {
                    WRITELN("error");
                    goodInput = false;
                } else {
                    num = a * d;
                    denum = b * c;                    
                }
            }
        
            if (goodInput) {
                simplify(num, denum);                
            }

        }
        
    }    
}
