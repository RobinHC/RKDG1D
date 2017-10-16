#include "IndicatorEverywhere.h"

//����������� ���������� "����� � �����"
IndicatorEverywhere::IndicatorEverywhere(const BaseParams& prm, const Problem& prb) : Indicator(prm, prb)
{
}//IndicatorEverywhere::IndicatorEverywhere

//���������� ���������� "����� � �����"
IndicatorEverywhere::~IndicatorEverywhere()
{};

//���������� ������������ �������
void IndicatorEverywhere::calc_indicator(const vector<vector<vector<double>>>& SOL, \
	vector<double>& Ind) const
{
	int nx = ptrprm->nx;
	double h = ptrprm->h;

	for (int cell = 0; cell < nx; ++cell)
		Ind[cell] = 2.0;
}
