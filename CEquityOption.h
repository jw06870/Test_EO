#include <math.h>
#include "EOHelper.h"


	/******************************** class CStock **********************/
	class CStock
	{
	public:
		long	settleDate;
		double	vol260Day;
		double	yield;
		double	mktPrice;
		double	borrowCost;
		long	dvdDate;
		long	dvdFreq;
		double	dvdAmount;
		double	dvdGrowthRate;
		double	fxRate; //(base=USD)

		double	jpmCEVSigma;
		double	jpmCEVAlpha;
		double	JDCEVConstb;
		double	JDCEVConstc;

	};

	/******************************** class CEquityOption **********************/

	class CEquityOption
	{
	public:
		//regular


		double	strike;
		double  matureYears;

		long	callPut; // call=1, put=2
		double	targetVol;
		double	mktPrice;
		double	currConvRatio;
		double	singleRate;

		CStock	aStock;

		//non-db inputs
		long	isToCalcVega;
		long	isToCalcRho;
		long	isToCalcGamma;
		long	isToCalcSigma;

		//output:calc results

		// model calc: defaults
		double	value = 0;
		double	delta = 0;
		double	gamma = 0;
		double	theta = 0;
		double	vega = 0;
		double	aleph = 0; //price vs vol skew (alpha)
		double	rho = 0;
		double	bankruptcyValue = 0;
		double	expLife = 0;
		double	defaultProb = 0;

		// model calc: implied
		double	impliedVol = 0;

	public:
		void CalculateDefault();

		void CalculateValue(double* rtnValue,
			double* rtnDelta,
			double* rtnGamma,
			double* rtnVega,
			double* rtnTheta,
			double* rtnRho,
			double* rtnExpLife,
			double* rtnDefaultProb);

		void CalculateImpliedVol();
	};



