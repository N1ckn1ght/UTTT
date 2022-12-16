#pragma once
#include "Result.h"

class Ratio {
private:
	float sum;
	size_t amount;
public:
	Ratio();

	void addResult(const Result& result);
	float getChance();
};