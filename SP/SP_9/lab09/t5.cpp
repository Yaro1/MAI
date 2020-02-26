/*  xxx2019   */
#include "mlisp.h"
//________________ 
double __xxx2019__try(double x) {
x = x * x;
 return x;
 }
int main(){
 display("Calculation is ok!");newline();
 display(__xxx2019__try(2)); newline();

 std::cin.get();
 return 0;
}

