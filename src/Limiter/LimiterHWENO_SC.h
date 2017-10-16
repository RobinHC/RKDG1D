#ifndef LIMITERHWENO_SC_H_
#define LIMITERHWENO_SC_H_

#include <vector>

#include "Indicator.h"
#include "Limiter.h"

#define HWENO_SC LimiterHWENO_SC

using namespace std;

class LimiterHWENO_SC :
	public Limiter
{
private:
	double wg; //�������, � ������� ���������� ��������� ��� ������� �������������� ��������

	const double weps = 1e-6; //����� ������������� �����

	//���������� ����������� ������� 
	//����������, ������ �������� ����� �������� ���� ��������� �������
	void CalculateBound(const vector<vector<vector<double>>>& SOL, const int cell);

public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//dimension - ����� �������������� ����������,
	//ind - ������, �������� ������������ �������,
	//degree - �������� ��������, ���������� ���������� wg)
    LimiterHWENO_SC(const BaseParams& prm, const Problem& prb, const Indicator& ind, double degree);

	//����������
	~LimiterHWENO_SC();
};

#endif
