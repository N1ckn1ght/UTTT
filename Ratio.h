#pragma once
#include "Result.h"

class Ratio {
private:
	float sum;
	size_t amount;
public:
	Ratio();

	void addResult(const Result& result);
	void addRatio(Ratio& ratio);
	void addRatio(const float sum_, const size_t amount_);
	float getChance();
	size_t getAmount();
};