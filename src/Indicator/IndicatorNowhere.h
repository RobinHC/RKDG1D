#ifndef INDICATORNOWHERE_H_
#define INDICATORNOWHERE_H_

#include "Indicator.h"
#include "defs.h"

#define Nowhere IndicatorNowhere 

class IndicatorNowhere :
	public Indicator
{
public:
	IndicatorNowhere(const BaseParams& prm, const Problem& prb);
	~IndicatorNowhere();

	//���������� ������������ �������
	void calc_indicator(const vector<vector<vector<double>>>& SOL, \
		vector<double>& Ind) const;
};

#endif