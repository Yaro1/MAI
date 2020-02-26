#include "mlisp.h"

double odd__bits(double n);
double even__bits(double n);
double display__bin(double n);
double report__results(double n);

double odd__bits(double n)
{
return (n == 0 ? 0
: remainder(n,2) == 0 ?
odd__bits (quotient(n,2))
: true ? even__bits(quotient(n,2))
: _infinity);
}

double even__bits(double n)
{
return (n == 0 ? 1
: remainder(n,2) == 0 ?
even__bits (quotient(n,2))
: odd__bits(quotient(n,2)));
}

double display__bin(double n){
(display(remainder(n,2))),
(n==0 ? 0 : display__bin(quotient(n,2)));
return 0;
}

double report__results(double n){
(display("Happy birthday to you!\n\t")),
(display(n)),(display(" (decimal)\n\t")),
(display__bin(n)),(display("(reversed binary)\n")),
(display("\teven?\t")),(display(even__bits(n)==1 ? "yes" : "no")),
(newline()),
(display("\todd?\t")),(display(odd__bits(n)==1 ? "yes" : "no")),
(newline());
return 0;

}
//***** Date of YOUR birthday *******
int dd=02;
int mm=04;
int yyyy=2000;
//***********************************

int main(){
display(report__results (dd*1000000+
mm*10000+
yyyy));
newline();
std::cin.get();
return 0;
}