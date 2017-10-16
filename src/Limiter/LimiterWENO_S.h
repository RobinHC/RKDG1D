#ifndef LIMITERWENO_S_H_
#define LIMITERWENO_S_H_

#include <vector>

#include "Indicator.h"
#include "Limiter.h"

#define WENO_S LimiterWENO_S

using namespace std;

class LimiterWENO_S :
	public Limiter
{
private:
	double wg; //�������, � ������� ���������� ��������� ��� ������� �������������� ��������

	const double weps = 1e-7; //����� ������������� �����

	//���������� ����������� ������� 
	//����������, ������ �������� ����� �������� ���� ��������� �������
	void CalculateBound(const vector<vector<vector<double>>>& SOL, const int cell);

public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//dimension - ����� �������������� ����������,
	//ind - ������, �������� ������������ �������,
	//degree - �������� ��������, ���������� ���������� wg)
    LimiterWENO_S(const BaseParams& prm, const Problem& prb, const Indicator& ind, double degree);

	//����������
	~LimiterWENO_S();
};

#endif
