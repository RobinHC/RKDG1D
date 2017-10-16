#ifndef LIMITERHWENO_H_
#define LIMITERHWENO_H_

#include <vector>

#include "Indicator.h"
#include "Limiter.h"

#define HWENO LimiterHWENO

using namespace std;

class LimiterHWENO :
    public Limiter
{
private:
    double wg; //�������, � ������� ���������� ��������� ��� ������� �������������� ��������
    
	const double weps = 1e-6; //����� ������������� �����

	//���������� ����������� ������� 
	//����������, ������ �������� ����� �������� ���� ��������� �������
	//���������� �������� ����� �������� (Vcorr[cell]) �� ���������� (cell) ������ �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
    void CalculateBound(const vector<vector<double>>& UU, const vector<vector<double>>& VV, const int cell);

	double centrdiff(double yL, double yR, double h)
	{
		return 0.5 * (yR - yL) / h;
	}

	double diff2(double yL, double y, double yR, double h)
	{
		return (yR - 2.0*y + yL) / (h*h);
	}

	double backbackdiff(double yLL, double yL, double y, double h)
	{
		return 0.5 * (3.0*y - 4.0*yL + yLL) / h;
	}

	double forwforwdiff(double y, double yR, double yRR, double h)
	{
		return 0.5 * (-3.0*y + 4.0*yR - yRR) / h;
	}


public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//dimension - ����� �������������� ����������,
	//ind - ������, �������� ������������ �������,
	//degree - �������� ��������, ���������� ���������� wg)
    //prb - ��������� �� ������,
    //LimiterHWENO(const BaseParams& prm, const int dimension, const Indicator& ind, double degree);
    LimiterHWENO(const BaseParams& prm, const Problem& prb, \
                 const Indicator& ind, double degree);

	//����������
    ~LimiterHWENO();
};

#endif

