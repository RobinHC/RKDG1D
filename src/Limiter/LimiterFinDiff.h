#ifndef LIMITERFINDIFF_H_
#define LIMITERFINDIFF_H_


#include "Limiter.h"

#define FinDiff LimiterFinDiff

class LimiterFinDiff :
    public Limiter
{
private:
	//���������� ����������� ������� 
	//����������, ������ �������� ����� �������� ���� ��������� �������
	//���������� �������� ����� �������� (Vcorr[cell]) �� ���������� (cell) ������ �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	//����� ��������������� ������� �������
	void CalculateBound(const vector<vector<vector<double>>>& SOL, \
		const int cell);
public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//dimension - ����� �������������� ����������,
	//ind - ������, �������� ������������ �������)
	//������ �������� ��������� IndEverywhere, ������������� �����!
    LimiterFinDiff(const BaseParams& prm, const Problem& prb, const Indicator& ind);

	//����������
    ~LimiterFinDiff();
};

#endif
