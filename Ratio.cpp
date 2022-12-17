#include "Ratio.h"

Ratio::Ratio()
{
	sum = 0;
	amount = 0;
}

void Ratio::addResult(const Result& result)
{
	switch (result) {
		case Result::Win:
			sum += 1;
			break;
		case Result::Draw:
			sum += 0.5;
			break;
		default:
			break;
	}
	amount++;
}

void Ratio::addRatio(Ratio& ratio)
{
	sum += ratio.getChance() * float(ratio.getAmount());
	amount += ratio.getAmount();
}

void Ratio::addRatio(const float sum_, const float amount_)
{
	sum += sum_;
	amount += amount_;
}

float Ratio::getChance()
{
	if (amount) {
		return sum / float(amount);
	}
	return 0.5;
}

float Ratio::getAmount()
{
	return amount;
}
