#include "pzhelp"  
  
void hello () {  
 WRITELN("hello world");  
}  
  
PROGRAM {  
  int n = READ_INT();  
  
  if ( n <= 0 ) WRITELN("nothing today");  
  else         for (int i = 0; i < n; i++) hello();  
}   
