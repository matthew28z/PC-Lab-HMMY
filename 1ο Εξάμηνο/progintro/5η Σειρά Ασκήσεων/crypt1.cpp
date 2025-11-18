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
    
    for (int i = 0; i < 26; i++) {
        after[i] = getchar();
    }
    
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
}
