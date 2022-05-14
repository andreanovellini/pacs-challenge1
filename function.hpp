#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include <tuple>
#include <vector>
#include <functional>

/*!
 * Computes the zero of a scalar function with the Newton (the derivative is computed with the symmetric difference quotient formula
 * @param f the function
 * @param df the derivative of f
 * @param a the initial point
 * @param tol relative tolerance
 * @param tola absolute tolerance
 * @param maxIt maximum number of iterations
 * @return The approximation of the zero of f and a status (false if not converging)
 *
 */
std::tuple<double, bool>
Newton(const std::function<double(const double &)> &f, const std::function<double(const double &)> &df, double a, const double &tol = 1e-4, const double &tola = 1e-10, const unsigned int &maxIt = 150);

/*!
 * Solves the initial value problem using backward Euler scheme
 *
 * @param t vector of time nodes
 * @param u vector of the numeric solution computed in each time node
 * @param f the right hand side of the ODE
 * @oaram t0 initial time
 * @param u0 intiial solution
 * @param T the final time
 * @param N the number of steps
 * @param theta is the parameter for the choice of the method
 * @return the status (1 if converged, 0 if not)
 *
 */
bool
solver(std::vector<double> &t, std::vector<double> &u, const std::function<double(const double &, const double &)> &f, const double &t0, const double &u0, const double &T, const unsigned int &N, const double &theta = 1.0); 


#endif
