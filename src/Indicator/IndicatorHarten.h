#ifndef INDICATORHARTEN_H_
#define INDICATORHARTEN_H_

#include "Indicator.h"
#include "defs.h"

#define Harten IndicatorHarten

class IndicatorHarten :
	public Indicator
{

private:
	double mult; //��������� ��� ��������� �������� � �������� �������

	//"��������������" ����������, �� ������� �������������� �������� ������������ �������
	var sens;

public:
	//����������� 
	//  prm - ������, ���������� ��������� ������, 
	//  val - "��������������" ����������
	//  alpha - ����������� � ���������� �������
	IndicatorHarten(const BaseParams& prm, const Problem& prb, const var val, const double alpha);

	//����������
	~IndicatorHarten();

	//���������� ����������� ������� 
	//����������, ������ �������� ������������ �������
	//���������� �������� ������������ ������� (Ind) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	void calc_indicator(const vector<vector<double>>& UU, \
		const vector<vector<double>>& VV, \
		vector<double>& Ind) const;
};

#endif

