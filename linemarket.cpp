#include "pzhelp"    
    
const int N = READ_INT();    
const int M = READ_INT();    
    
//Heapsort Algorithm    
bool comparison(int* a,  int* b) {    
    if (a[0] < b[0]) {    
        return true;    
    }    
    
    return false;    
}    
    
void heapify(int** array, int length, int start) {    
    int largest = start;    
    int left = 2 * start + 1;    
    int right = 2 * start + 2;    
    
    if (left < length && comparison(array[largest], array[left])) {    
        largest = left;    
    }    
    
    if (right < length && comparison(array[largest], array[right])) {    
        largest = right;    
    }    
    
    if (largest != start) {    
        int* temp = array[start];    
        array[start] = array[largest];    
        array[largest] = temp;    
    
        heapify(array, length, largest);    
    }    
}    
    
void heapSort(int** arr) {    
    // Build heap (rearrange array)    
    for (int i = M / 2 - 1; i >= 0; i--) {    
        heapify(arr, M, i);    
    }    
    
    //Extract from heap    
    for (int i = M - 1; i > 0; i--) {    
        int* temp = arr[0];    
        arr[0] = arr[i];    
        arr[i] = temp;    
    
        heapify(arr, i, 0);    
    }    
}    
/* 
int placeShops(int step, int* spots, int length) {   
    int shopsPlaced = 1; //always place on shop at the left end   
   
    int spot = spots[0];   
                   
    for (int i = 1; i < length; i++) {   
        if (spots[i] >= spot + step) {   
            spot = spots[i];   
            shopsPlaced++;   
        }   
    }   
   
    return shopsPlaced;   
}  */  
  
int max(int a, int b) {  
    if (a < b) {  
        return b;  
    }  
      
    return a;  
}  
  
int placeShopsFaster(int step, int** spaces) {  
    int res = 0;  
      
    int lastSpot = -step;  
      
    for (int i = 0; i < M; i++) {  
        int start = spaces[i][0];  
        int end = spaces[i][1];  
          
        int nextPossible = lastSpot + step;  
          
        if (end >= nextPossible) {  
            int candidate = max(start, nextPossible);  
  
            res += (end - candidate) / step + 1;  
              
            lastSpot = candidate + (end - candidate) / step * step;  
        }  
    }  
      
    return res;  
}  
    
PROGRAM {    
    int** spaces = NEW(int*, M);    
    
    if (N <= pow(10, 6) && M <= pow(10, 5)) {    
        bool goodInput = true;    
    
        int sum = 0;    
    
        for (int i = 0; i < M; i++) {    
            const int si = READ_INT();    
            const int fi = READ_INT();    
    
            if (fi < si || si < 0 || fi > 15 * pow(10, 8)) {    
                goodInput = false;    
                break;    
            } else {    
                sum += fi - si + 1;    
                spaces[i] = NEW(int, 2);    
                spaces[i][0] = si;    
                spaces[i][1] = fi;    
            }    
        }      
            
        if (goodInput && sum >= N) {    
            heapSort(spaces);  
  
            int result = (spaces[M - 1][1] - spaces[0][0]) / N;  
  
            bool hasFinished = false;    
    
            while(!hasFinished) {    
                int shopsPlaced = placeShopsFaster(result, spaces);    
  
                if (shopsPlaced >= N) {  
                    hasFinished = true;  
                } else {  
                    result--;  
                    //WRITELN(result + 1, shopsPlaced);  
                }  
            }    
    
            WRITELN(result);    
        }    
    }    
}  
