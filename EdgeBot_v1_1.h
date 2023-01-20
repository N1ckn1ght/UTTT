#pragma once
#include "MinMaxEngine.h"

class EdgeBot_v1_1 : public MinMaxEngine
{
private:
	double EVAL_MAX;

	// pure static evaluation variables go here:
	std::vector <std::vector <double>> localPts;
	std::vector <std::vector <double>> globalPts;
	std::vector <std::vector <double>> localWinPts;
	double globalWinPts;
	double localAtkPts;
	double globalAtkPts;
	double wastedAtkPts;
	double selfRefPts;
	
	void modEvals(std::vector <EvalMove>& evals) override;
	double staticEval(Field& field) override;

	int k(const Cell& cell) const;
	int atk(const Cell& a, const Cell& b, const Cell& c) const;
public:
	EdgeBot_v1_1();
};