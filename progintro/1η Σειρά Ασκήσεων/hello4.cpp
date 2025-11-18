#include "pzhelp"  
  
const int n = 20;  
int i;  
  
void num_hello () {  
  WRITELN(i, "hello world");  
}  
  
PROGRAM {  
  for (i = 1; i <= n; i++) num_hello();  
}  
