#pragma once
double GaussCumFirstDeriv(double x);
double GaussCum(double x);
void BlackScholes(double s0, double x0, double vol, double q,
	double r, double t, int optionType,
	double* value, double* delta, double* gamma, double* vega,
	double* theta, double* rho);
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
	double* bankruptcyValue);


