#ifndef INDIKATORKRIVODONOVA_H_
#define INDICATORKRIVODONOVA_H_

#include "Indicator.h"
#include "defs.h"


#define Krivodonova IndicatorKrivodonova

class IndicatorKrivodonova :
    public Indicator
{
private:
	//"��������������" ����������, �� ������� �������������� �������� ������������ �������
	var sens;

public:
	//����������� (prm - ������, ���������� ��������� ������, val - "��������������" ����������
	//             prb - �������� ������ (�.�. ����� ����������� ��������!)
	IndicatorKrivodonova(const BaseParams& prm, const Problem& prb, const var val);

	//����������
    ~IndicatorKrivodonova();
    
	//���������� ����������� ������� 
	//����������, ������ �������� ������������ �������
	//���������� �������� ������������ ������� (Ind) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	void calc_indicator(const vector<vector<vector<double>>>& SOL, \
		vector<double>& Ind) const;
};

#endif