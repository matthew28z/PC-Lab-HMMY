#include "pzhelp"  
  
PROGRAM {  
  const int N = READ_INT();  
    const int maxInt = N * N - 1;  
  
    int counter = 0;  
  
    int* numbers = NEW(int, maxInt + 1);  
    int* lineSums = NEW(int, N);  
  
    for (int i = 0; i <= maxInt; i++) {  
        numbers[i] = i;  
    }  
  
    int** matrix = NEW(int*, N);  
  
    for (int i = 0; i < N; i++) {  
        matrix[i] = NEW(int, N);  
  
        int lineSum = 0;  
  
        for (int j = 0; j < N; j++) {  
            matrix[i][j] = READ_INT();  
  
            lineSum += matrix[i][j];  
  
            for (int k = 0; k <= maxInt; k++) {  
                if (matrix[i][j] == numbers[k]) {  
                    counter++;  
                    numbers[k] = -1;  
                    break;  
                }  
            }  
        }  
  
        lineSums[i] = lineSum;  
    }  
  
    if (counter == maxInt + 1) {  
        //Real giati mporei na mhn bgainei akeraios  
        const int goodSum = N * (pow(N, 2) - 1) / 2;  
        bool goodInput = true;  
  
        int diagnalRSum = 0;  
        int diagnalLSum = 0;  
  
        for (int i = 0; i < N; i++) {  
            int colSum = 0;  
            int lineSum = lineSums[i];  
  
            diagnalLSum += matrix[i][i];  
            diagnalRSum += matrix[i][N - 1 - i];  
  
            for (int j = 0; j < N; j++) {  
                colSum += matrix[j][i];  
            }  
  
            if (colSum != goodSum || lineSum != goodSum) {  
                goodInput = false;  
                break;  
            }  
        }  
  
        if (goodInput && diagnalRSum == goodSum && diagnalLSum == goodSum) {  
            WRITELN("yes");  
        } else {  
            WRITELN("no");  
        }  
    } else {  
        WRITELN("no");  
    }  
}  
