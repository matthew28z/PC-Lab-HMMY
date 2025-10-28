#include "pzhelp"

PROGRAM {
    const int entries = READ_INT();
    SKIP_LINE();
    
    int palins = 0;
    
    for (int i = 0; i < entries; i++) {
        char letter = getchar();
        //21 giati krataw kai to \n
        char* word = NEW(char, 21);
        
        int length = 0;
        while(letter != '\n' && length <= 20) {
            word[length] = letter;
            letter = getchar();
            length++;
        }
        
        word[length] = '\n';
        
        if (length == 0) {
            //Synexizei sthn idia grammh
            WRITELN("empty");
        } else if (length > 20) {
            WRITELN("error");
            SKIP_LINE();
        } else {
            bool isPalin = true;
            
            for (int x = 0; x < length / 2; x++) {
                if (word[x] != word[length - 1 - x]) {
                    isPalin = false;
                    break;
                }
            }
            
            if (isPalin) {
                WRITELN("yes");
                palins++;
            } else {
                WRITELN("no");
            }
        }
        
        DELETE(word);
    }
    
    WRITELN(FORM(palins * 100.0 / entries, 0, 3));
}
