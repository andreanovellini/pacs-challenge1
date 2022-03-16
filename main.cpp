#include <exception>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#include "gnuplot-iostream.hpp"

#include "function.hpp"
double fun(const double &t, const double &y)
{
	return -t * std::exp(-y);
};

double u_ex(const double &t)
{
	return std::log(1 - t*t/2.);
}

int main() {
	std::cout << "======== ODE solver	========\n" << std::endl;

	// Readiing the parameters
	// Initial condition on time
	std::cout << "Insert t0: " << std::endl;
	double t0;
	std::cin >> t0;
	// Initial condition of the solution
	std::cout << "Insert y0: " << std::endl;
	double y0; 
	std::cin >> y0;
	// Upper bound of the time interval
	std::cout << "Insert T: " << std::endl;
	double T; 
	std::cin >> T;
	// Number of points for the partitioning of the interval
	std::cout << "Insert N; " << std::endl;
	double N;
	std::cin >> N;
		
	// Creation of two vectors to stores the results in
	// vector t_n stores the time points
	// vector u_n stores the values of the computed at the respective time instant
	std::vector<double> t_n{};
	std::vector<double> u_n{};
	// Since the size is known we reserve it to avoid reallocations 
	t_n.reserve(N);
	u_n.reserve(N);

	// Call to the solver to compute the solution
	bool res = solver(t_n, u_n, fun, y0, t0, T, N);	
		
	// Compute the exact solution
	std::vector<double> u{};
	u.reserve(N);
	for (int i = 0; i < u_n.size(); i++)
	{
		u.push_back(u_ex(t_n[i]));
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

	std::cout << t_n.size() << " " << u_n.size() << " " << u.size();
	Gnuplot gp;
	gp << "plot" << gp.file1d(std::tie(t_n, u_n)) << "w lp lw 2 title 'un'," << gp.file1d(std::tie(t_n, u)) << "w l lw 2 title 'uex'" << std::endl;
	
	f.close();
	return 0;
}
