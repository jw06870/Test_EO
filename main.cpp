// EquityOption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CEquityOption.h"
using namespace std;


int main()
{
	CEquityOption anOption;	

	anOption.matureYears = 1;
	anOption.aStock.borrowCost = 0;
	anOption.aStock.mktPrice = 10.45;
	anOption.aStock.dvdAmount = 0.025;
	anOption.aStock.dvdFreq = 4;
	anOption.singleRate = 2.5;

	anOption.strike = anOption.aStock.mktPrice * 0.8;
	anOption.currConvRatio = 1;
	anOption.targetVol = 15.15;
	//printf("anOption.targetVol =%lf %lf\n", anOption.targetVol);

	anOption.isToCalcVega = 1;
	anOption.isToCalcRho = 0;


	//anOption.CheckInputs();
	anOption.CalculateDefault();
	cout << anOption.aStock.mktPrice << " "
		<< anOption.value << " "
		<< anOption.delta << " "
		<< anOption.gamma << " "
		<< anOption.vega << " "
		<< anOption.aleph << endl;
	
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
