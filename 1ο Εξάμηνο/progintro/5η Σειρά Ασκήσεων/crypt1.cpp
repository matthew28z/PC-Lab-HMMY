#include "pzhelp"  
  
char before[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',  
                   'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',  
                   'q', 'r', 's', 't', 'u', 'v', 'w', 'x',  
                   'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',  
                   'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',  
                   'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',  
                   'W', 'X', 'Y', 'Z'  
                  };  
  
char upperCase(char c) {  
    for (int i = 0; i < 26; i++) {  
        if (c == before[i]) {  
            return before[26 + i];  
        }  
    }  
  
    return '\0';  
}  
  
PROGRAM {  
    char after[52];  
  
    int counter = 0;  
  
    bool goodInput = true;  
  
    for (int i = 0; i < 26; i++) {  
        after[i] = getchar();  
        for (int j = counter; j < i; j++) {  
            if (after[j] == after[i]) {  
                goodInput = false;  
                break;  
            }  
        }  
          
        int track = 0;  
          
        if (goodInput) {  
            for (int j = 0; j < 26; j++) {  
                if (after[i] != before[j]) {  
                    track++;  
                }  
            }  
              
            if (track == 26) {  
                goodInput = false;  
            }  
        }  
    }  
  
    if (goodInput) {  
        for (int i = 26; i < 52; i++) {  
            after[i] = upperCase(after[i - 26]);  
        }  
  
  
  
        SKIP_LINE();  
  
        char letter = getchar();  
  
        while (letter != EOF) {  
            for (int i = 0; i < 52; i++) {  
                if (letter == before[i]) {  
                    letter = after[i];  
                    break;  
                }  
            }  
  
            WRITE(letter);  
  
            letter = getchar();  
        }  
    } else {  
        WRITELN("error");  
    }  
}
