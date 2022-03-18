#include <exception>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <GetPot>

#include "gnuplot-iostream.hpp"
#include "function.hpp"

// Right hand side of the ODE 

double fun(const double &t, const double &y)
{
	return -t * std::exp(-y);
};

double u_ex(const double &t, const double &t0, const double &u0)
{
	return std::log(1 - t*t/2.);
}

int main(int argc, char **argv) {
	std::cout << "======== ODE solver	========\n" << std::endl;
	
	// Get the parameters using GetPot	
	GetPot command_line(argc, argv);

	const double t0 = command_line("t0", 0.);	// Initial time
	const double u0 = command_line("u0", 0.);	// Initial value
	const double T = command_line("T", 1.);	// Upper bound time
	const unsigned int N = command_line("N", 100);	// Number of sub-intervals
	const double theta = command_line("theta", 1.);	// parameter for theta method

	// Creation of two vectors to stores the results in
	std::vector<double> t_n{};	// time points
	std::vector<double> u_n{};	// numeric solution
	// Reserve to avoid reallocations, sinze size is known 
	t_n.reserve(N);
	u_n.reserve(N);

	// Call to the solver to compute the solution
	bool res = solver(t_n, u_n, fun, t0, u0, T, N, theta);	
		
	// Compute the exact solution
	std::vector<double> u{};	// exact solution
	u.reserve(N);
	for (int i = 0; i < u_n.size(); i++)
	{
		u.push_back(u_ex(t_n.at(i), t0, u0));
	}

	// Create and save the results in a file called "result.dat"
	std::cout << "Result file: result.dat" << std::endl;
	std::ofstream f("result.dat");
	f << "node coordinate\tcomputed solution\texact solution" << std::endl;
	for (int i = 0; i < u_n.size(); i++)
	{
		f.setf(std::ios::left, std::ios::adjustfield);
		f.width(16);
		f << t_n[i] << "\t\t" << u_n[i] << "\t\t" << u[i] << "\n";
	}

	// Plot the computed solution and the exact solution using GnuPlot
	Gnuplot gp;
	gp << "plot" << gp.file1d(std::tie(t_n, u_n)) << "w lp lw 2 title 'un'," << gp.file1d(std::tie(t_n, u)) << "w l lw 2 title 'uex'" << std::endl;
	
	f.close();
	return 0;
}
