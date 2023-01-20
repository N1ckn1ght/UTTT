#pragma once
#include <cstdlib>
#include "MinMaxEngine.h"

class Heurist_v2_0 : public MinMaxEngine
{
private:
	// Amount of random branches searched per move at the static evaluation
	size_t branches;

	void modEvals(std::vector <EvalMove>& evals) override;
	double staticEval(Field& field) override;

	double k(const Cell& cell) const;
public:
	Heurist_v2_0(size_t branches_);
};