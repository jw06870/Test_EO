#include <math.h>
#include "EOHelper.h"



	double GaussCumFirstDeriv(double x)
	{
		double pi = 3.14159265;

		return 1.0 / sqrt(2 * pi) * exp(-x * x / 2.0);
	}

	double GaussCum(double x)
	{
		if (x >= 0)
		{
			double y;
			double a1, a2, a3, a4, a5, g, k;

			g = 0.2316419;
			k = 1.0 / (1 + g * x);
			a1 = 0.319381530;
			a2 = -0.356563782;
			a3 = 1.781477937;
			a4 = -1.821255978;
			a5 = 1.330274429;

			y = a1 * k + a2 * pow(k, 2) + a3 * pow(k, 3) + a4 * pow(k, 4) + a5 * pow(k, 5);
			return 1.0 - GaussCumFirstDeriv(x) * y;
		}
		else
		{
			return 1.0 - GaussCum(-x);
		}
	}
	
	void BlackScholes(double s0, double x0, double vol, double q,
		double r, double t, int optionType,
		double* value, double* delta, double* gamma, double* vega,
		double* theta, double* rho)
	{

		/*
		function:	black-scholes standard formula to calculate a call/put option's0
					value, delta, gamma

					the underlying follows GBM.

		reference:	john hull , 3rd ed, p241-244 , greeks p312-329

		need to work on:

		problems:

		inputs:
			s0: stock price;
			x0:	strike;
			vol:	volatility2
			q:	continuous dvd yield, in cc form
			r:	interest rate, in cc form
			t:	time to maturity, in years
			optionType: 1=call; 2=put; default is call

		outputs:
			value:	option price
			stdError:	std error
			gamma:	gamma
			theta:	theta


		*/

		double d1, d2;

		d1 = (log(s0 / x0) + (r - q + vol * vol / 2) * t) / (vol * sqrt(t));
		d2 = d1 - (vol * sqrt(t));

		if (optionType == 1)
		{

			*delta = GaussCum(d1) * exp(-q * t);
			*value = s0 * exp(-q * t) * GaussCum(d1) - x0 * exp(-r * t) * GaussCum(d2);
			*theta = -s0 * GaussCumFirstDeriv(d1) * vol * exp(-q * t) / (2 * sqrt(t))
				+ q * s0 * GaussCum(d1) * exp(-q * t)
				- r * x0 * exp(-r * t) * GaussCum(d2);
			*rho = x0 * t * exp(-r * t) * GaussCum(d2) / 100.0;

		}
		else
		{
			*delta = -GaussCum(-d1) * exp(-q * t);
			*value = -s0 * exp(-q * t) * GaussCum(-d1) + x0 * exp(-r * t) * GaussCum(-d2);
			*theta = -s0 * GaussCumFirstDeriv(d1) * vol * exp(-q * t) / (2 * sqrt(t))
				- q * s0 * GaussCum(-d1) * exp(-q * t)
				+ r * x0 * exp(-r * t) * GaussCum(-d2);
			*rho = -x0 * t * exp(-r * t) * GaussCum(-d2) / 100.0;
		}

		*gamma = GaussCumFirstDeriv(d1) * exp(-q * t) / (s0 * vol * sqrt(t));
		*vega = s0 * sqrt(t) * GaussCumFirstDeriv(d1) * exp(-q * t) / 100.0;
	}

	  
	void Value_BlackScholes(
		double	undPrice,
		double	undBorrowCost,
		double  dvdYield,
		double  rate,
		double	targetVol,
		double	strike,
		double	matureYears,
		long	callPut,
		double* value,
		double* delta,
		double* gamma,
		double* vega,
		double* theta,
		double* rho,
		double* expLife,
		double* bankruptcyValue)
	{
		// exercise type = European;

		double adjustedVol = targetVol / 100.0;
		double r = rate / 100.0;

		double t = matureYears;
		double q = (dvdYield + undBorrowCost) / 100.0;

		BlackScholes(undPrice, strike, adjustedVol, q, r, t, (int)callPut,
			value, delta, gamma, vega, theta, rho);

		if (callPut == 1)
		{
			*bankruptcyValue = 0;
		}
		else
		{
			*bankruptcyValue = strike;
		}

		*expLife = t;

	}





