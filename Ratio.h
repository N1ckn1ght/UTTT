#pragma once
#include "Result.h"

class Ratio {
private:
	float sum;
	float amount;
public:
	Ratio();

	void addResult(const Result& result);
	void addRatio(Ratio& ratio);
	void addRatio(const float sum_, const float amount_);
	float getChance();
	float getAmount();
};