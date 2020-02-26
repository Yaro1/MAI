#include "mlisp.h"

double a = 0; double b = 2;

double fun(double x);

double eps = 1e-5;
double golden__section__search(double a, double b);
double golden__start(double a, double b);

double mphi = 0;

double __pys__try(double a, double b, double xa, double ya, double xb, double yb);

double xmin = 0;

double fun(double x){
	x = x - (double)19/20/e;
		return ((expt(log(expt(atan(x - 2),2)),4))*5 - x - 7);
}

double golden__section__search(double a, double b){
	{ double xmin;
		(a<b? xmin = golden__start(a, b)
				:xmin = golden__start(b,a));
		newline();
		return(xmin);
	}
}

double golden__start(double a, double b){
	mphi = 0.5 * (3 - sqrt(5));
	{ 
		double xa = a + mphi * (b - a);
		double xb = b - mphi * (b - a);
		return (__pys__try(a, b, xa, fun(xa), xb, fun(xb)));
	}
}

double __pys__try(double a, double b, double xa, double ya, double xb, double yb) {
	return(abs(a - b) < eps ? ((a+b)*0.5)
					: (true)? (display("+")),
							(ya < yb) ? (
									b = xb,
									xb = xa,
									yb = ya,
									xa = a + mphi*(b-a),
									__pys__try(a, b ,xa, fun(xa), xb, yb)
									)
							: (
								a = xa,
								xa = xb,
								ya = yb,
								xb = b - mphi*(b-a),
								__pys__try(a, b, xa, ya, xb, fun(xb))
								)
					:_infinity
			);
	}


int main(){
	xmin = golden__section__search(a,b);
	display("interval=\t[");
	display (a);
	display(",");
	display(b);
	display("]\n");
	display("xmin=\t\t");
	display(xmin);
	newline();
	display("f(xmin)=\t");
	display(fun(xmin));

	std::cin.get();
	return 0;
}




