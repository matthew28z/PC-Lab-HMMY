#include "pzhelp"

//Pinakas me tis dynameis
int* powers = NEW(int, 9);

int numOfDigits(int num) {
    //Oloi exoun estw ena digit
    int totalDigits = 0;
    int temp = num;

    while (temp > 0) {
        totalDigits++;
        temp /= 10;
    }
    
    return totalDigits;
}

int sumDigits(int* digits, int size) {
    int sum = 0;
    
    for (int i = 0; i < size; i++) {
        //Briskei to psifio kai thn antistoixh dynamh
        sum += powers[digits[i] - 1];
    }
    
    return sum;
}

PROGRAM {
    //Briskei to elaxisto panw orio
    const int N = READ_INT();
    
    for (int i = 0; i < 9; i++) {
        powers[i] = (int)pow(i + 1, N);
    }
    
    int validDigits = 8;

    while (validDigits * pow(9, N) < pow(10, validDigits) - 1) {
        validDigits--;
    }
    
    int upper = (int)pow(10, validDigits) - 1;
    
    int* digits = NEW(int, 1);
    int tempDigits = 1;
    if (N <= 9 && N >= 0) {
        int tempDigits = 1;
        for (int i = 0; i <= upper; i++) {

            const int totalDigits = numOfDigits(i);
            
            if (tempDigits < totalDigits) {
                tempDigits = totalDigits;
            
            //Deletes the previous array    
            DELETE(digits);
            //Creates a new one
            digits = NEW(int, totalDigits);
            } else if (tempDigits == 0) {
                digits = NEW(int, 1);
            }
            
            int tempI = i;
            
            //Pernaei ta digits se enan pinaka
            for (int x = totalDigits - 1; x >= 0; x--) {
                digits[x] = tempI % 10;
                //Einai akeraia diairesh
                tempI /= 10;
            }
            const int sum = sumDigits(digits, totalDigits);
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
