#include "function.hpp"
#include <cmath>
#include <functional>
#include <iostream>


std::tuple<double, bool>
Newton(const std::function<double(const double &)> &f, const std::function<double(const double &)> &df, double a , const double &tol, const double &tola, const unsigned int &maxIt)
{
	double ya = f(a);
	double resid = std::abs(ya);
	unsigned int iter{0u};
	double check = tol * resid + tola;
	bool goOn = resid > check;
 	while (goOn && iter < maxIt) 
	{
 		++iter;
		a += -ya/df(a);
		ya = f(a); 
		resid = std::abs(ya);
		goOn = resid > check;
 	}	

	return std::make_tuple(a, (iter < maxIt));
};

bool
solver(std::vector<double> &t, std::vector<double> &u, const std::function<double (const double &, const double &)> &f, const double &t0, const double &u0, const double &T, const unsigned int &N, const double &theta)
{
	const double h = (T - t0)/static_cast<double>(N);	// time step
	t.push_back(t0);	// initial time
	u.push_back(u0);	// initial solution

	for (unsigned int n = 0; n < N - 1; n++)
	{
		t.push_back(t.at(n)+h);	// new time instant
		
		auto F = [h, f, n, &t, &u, theta](const double &x) {return x-h*theta*f(t.at(n+1), x)-h*(1-theta)*f(t.at(n), u.at(n))-u.at(n);}; // function to pass in the Newton method

		auto dF = [F, h](const double &x) {return (F(x+h)-F(x-h))/(2.*h);};	// derivative F, to pass to the Newton method	
		
		auto res = Newton(F, dF, u.at(n)); // solution in the new time node

		if (!std::get<1>(res))
		{
			std::cout << "Did not converge at time " << t.at(n+1) << std::endl;
			return 0;	 		
		}
		else {
			u.push_back(std::get<0>(res));	
		}	
	}
	return 1;
}
