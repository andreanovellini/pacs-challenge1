#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include <tuple>
#include <vector>
#include <functional>

/*!
 * Computes the zero of a scalar function with the Newton (the derivative is computed with the symmetric difference quotient formula
 * @param f the function
 * @param h the step
 * @param a the initial point
 * @param tol relative tolerance
 * @param tola absolute tolerance
 * @param maxIt maximum number of iterations
 * @return The approximation of the zero of f and a status (false if not converging)
 *
 */
template<class Function, class Dfunction>
std::tuple<double, bool>
Newton(Function const &f, double h, double a, double tol, double tola, unsigned int maxIt);

/*!
 * Solves the initial value problem using backward Euler scheme
 *
 * @param t vector of time nodes
 * @param u vector of the numeric solution computed in the nodes' vector
 * #param f the right hand side of the ODE
 * @param T the final time
 * @param N the number of steps
 * @return the vector containing t_n and u_n for all n
 *
 */
bool
solver(std::vector<double> &t, std::vector<double> &u, const std::function<double(const double &, const double &)> &f, const double &t0, const double &y0, const double &T, const unsigned int &N); 


#endif
