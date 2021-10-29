#include <math.h>
#include "CEquityOption.h"

	
void CEquityOption::CalculateDefault()
{
	int dataIsValid;

	value = 0;
	delta = 0;
	gamma = 0;
	vega = 0;
	theta = 0;
	rho = 0;
	expLife = 0;

	dataIsValid = 1;
	// regular
	if (matureYears < 0
		|| aStock.mktPrice < 0
		|| targetVol < 0)
	{
		dataIsValid = 0;
	}
	else if (matureYears == 0)
	{
		dataIsValid = 0;
		gamma = 0;
		theta = 0;
		vega = 0;
		rho = 0;
		expLife = 0;

		if (callPut == 1)
		{
			if (aStock.mktPrice < strike)
			{
				value = 0;
				delta = 0;
			}
			else
			{
				value = aStock.mktPrice - strike;
				delta = 1;
			}
		}
		else
		{
			//put
			if (aStock.mktPrice < strike)
			{
				value = strike - aStock.mktPrice;
				delta = -1;
			}
			else
			{
				value = 0;
				delta = 0;
			}
		}
	}

	if (dataIsValid)
	{
		vega = 0;
		rho = 0;

		CalculateValue(&value,
			&delta,
			&gamma,
			&vega,
			&theta,
			&rho,
			&expLife,
			&defaultProb);

	}
};

void CEquityOption::CalculateValue(double* rtnValue,
	double* rtnDelta,
	double* rtnGamma,
	double* rtnVega,
	double* rtnTheta,
	double* rtnRho,
	double* rtnExpLife,
	double* rtnDefaultProb)
{

	*rtnDefaultProb = 0;

	Value_BlackScholes(
		aStock.mktPrice,
		aStock.borrowCost,
		aStock.dvdFreq * aStock.dvdAmount / aStock.mktPrice,
		singleRate,
		targetVol,
		strike,
		matureYears,
		callPut,
		rtnValue, rtnDelta, rtnGamma, rtnVega, rtnTheta, rtnRho, rtnExpLife,
		&bankruptcyValue);

	if (currConvRatio != 1)
	{
		*rtnValue = (*rtnValue) * currConvRatio;
		*rtnVega = (*rtnVega) * currConvRatio;
		*rtnTheta = (*rtnTheta) * currConvRatio;
		*rtnRho = (*rtnRho) * currConvRatio;
	}


};

void CEquityOption::CalculateImpliedVol()
{
	double	tol = 0.01; // 0.0005 for 0.05% of mkt price, or 5 cents on par
	long	nIter = 20;
	long	n = 0;
	double	impliedVega, impliedValue, crap1, crap2, crap3, crap4, crap5, crap6, crap7;

	double copyUndVol = targetVol;

	CalculateDefault();
	impliedVega = vega;
	impliedValue = value;

	impliedVol = targetVol;

	if ( fabs(mktPrice - impliedValue) / mktPrice > tol)
	{

		if (impliedValue < -100)
		{
			impliedVol = impliedValue;
			return;
		}

		n = 0;

		if (impliedVega != 0)
		{
			targetVol += (mktPrice - impliedValue) / impliedVega;
		}
		else
		{
			n = nIter;
		}

		if (targetVol > 0 && targetVol < 300)
		{
			CalculateValue(&impliedValue,
				&crap1,
				&crap2,
				&crap3,
				&crap4,
				&crap5,
				&crap6, &crap7);
		}


		while (fabs(mktPrice - impliedValue) / mktPrice > tol && n < nIter &&
			targetVol > 0
			&& targetVol < 200)
		{
			n++;

			targetVol += (mktPrice - impliedValue) / impliedVega;

			if (targetVol > 0)
			{
				CalculateValue(&impliedValue,
					&crap1,
					&crap2,
					&crap3,
					&crap4,
					&crap5,
					&crap6, &crap7);

				//CalculateVega(&impliedVega);
			}

			//	printf("fabs(mktPrice - impliedValue)/mktPrice", fabs(mktPrice - 
	//impliedValue)/mktPrice);

		}
	}

	if (fabs(mktPrice - impliedValue) / mktPrice <= tol && targetVol > 0 &&
		targetVol < 200)
	{
		impliedVol = targetVol;
	}
	else if (n >= nIter)
	{
		impliedVol = -999;
	}
	else
	{
		impliedVol = -999;
	}

	targetVol = copyUndVol;
}

