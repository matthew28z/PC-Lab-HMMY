#include "pzhelp"

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

int sumDigits(int* digits, int size, int power) {
    int sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum += (int)pow(digits[i], power);
    }
    
    return sum;
}

PROGRAM {
    //Briskei to elaxisto panw orio
    const int N = READ_INT();
    
    int validDigits = 8;
    while (validDigits * pow(9, N) < pow(10, validDigits) - 1) {
        validDigits--;
    }
    
    int upper = (int)pow(10, validDigits) - 1;
    
    if (N <= 9 && N >= 0) {
        for (int i = 0; i <= upper; i++) {
            //Creates an array
            const int totalDigits = numOfDigits(i);
            int* digits = NEW(int, totalDigits);
            int tempI = i;
            
            //Pernaei ta digits se enan pinaka
            for (int x = totalDigits - 1; x >= 0; x--) {
                digits[x] = tempI % 10;
                //Einai akeraia diairesh
                tempI /= 10;
            }
            const int sum = sumDigits(digits, totalDigits, N);
            if (sum > i) {
                //Skips some iterations
                int temp1 = i;
                //Einai + 9 kai oxi 10 gt sto telos janaprosthetei 1
                i += 9 -  i  % 10;
            } else if (sum == i) {
                WRITELN(i);
            }
            //Deletes the array
            DELETE(digits);
        }    
    } 
}
