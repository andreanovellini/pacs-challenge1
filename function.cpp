#include "function.hpp"
#include <cmath>
#include <functional>
#include <tuple>
#include <vector>
#include <iostream>

template <class Function>
std::tuple<double, bool>
Newton(const Function &f, double h, double a , double tol = 1e-4, double tola = 1e-10, unsigned int maxIt = 150)
{
	double ya = f(a);
	double resid = std::abs(ya);
	unsigned int iter{0u};
	double check = tol * resid + tola;
	bool goOn = resid > check;
 	while (goOn && iter < maxIt) {
 		++iter;
		const double df = (f(a+h)-f(a-h))/(2*h);
		a += -ya/df;
		ya = f(a); 
		resid = std::abs(ya);
		goOn = resid > check;
 	}	

	return std::make_tuple(a, (iter < maxIt));
};

bool
solver(std::vector<double> &t, std::vector<double> &u, const std::function<double (const double &, const double &)> &f, const double &t0, const double &y0, const double &T, const unsigned int &N)
{
	const double h = T/static_cast<double>(N);
	t.push_back(t0);
	u.push_back(y0);

	for(unsigned int n = 0; n < N - 1; n++){
		double t_n_plus_1 = t[n] + h;
		t.push_back(t_n_plus_1);
		double u_n = u[n];
		auto F = [h, f, t_n_plus_1, u_n](const double &x) {return x-h*f(t_n_plus_1, x) - u_n;};
		auto res = Newton(F, h, u_n);
		if(std::get<1>(res)==0){
			std::cout << "Did not converge at time " << t.at(n+1) << std::endl;
			return 0;	 		
		}
		else {
			u.push_back(std::get<0>(res));	
		}	
	}
	return 1;
}
