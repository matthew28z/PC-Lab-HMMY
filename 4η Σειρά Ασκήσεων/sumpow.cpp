#include "pzhelp"

//Pinakas me tis dynameis
int* powers = NEW(int, 10);

PROGRAM {
    //Briskei to elaxisto panw orio
    const int N = READ_INT();
    
    for (int i = 0; i <= 9; i++) {
        powers[i] = (int)pow(i, N);
    }
    
    int validDigits = 8;
    const REAL maxUpper = pow(10, validDigits) - 1;
    REAL realUpper = validDigits * pow(9, N);

    while ((realUpper < pow(10, validDigits) - 1) && validDigits > 1) {
        validDigits--;
        realUpper = validDigits * pow(9, N);
    }
    
    int upper;
    
    if (realUpper < maxUpper) {
        upper = (int)realUpper;
    } else {
        upper = (int)maxUpper;
    }

    if (N <= 9 && N >= 0) {
        for (int i = 0; i <= upper; i++) {
            int tempI = i;
            int sum = 0;
            
            while (tempI > 0) {
                sum += powers[tempI % 10];
                tempI /= 10;
            }
            
            if (sum > i) {
                //Skips some iterations
                //Einai + 9 kai oxi 10 gt sto telos janaprosthetei 1
                i += 9 -  i  % 10;
            } else if (sum == i) {
                WRITELN(i);
            }
        }    
    } 
}
