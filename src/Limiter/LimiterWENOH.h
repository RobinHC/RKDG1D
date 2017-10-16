#ifndef LIMITERWENOH_H_
#define LIMITERWENOH_H_

#include <vector>

#include "Indicator.h"
#include "Limiter.h"

#define WENOH LimiterWENOH

using namespace std;

class LimiterWENOH :
    public Limiter
{
private:
    double wg; //�������, � ������� ���������� ��������� ��� ������� �������������� ��������
    
	const double weps = 1e-8; //����� ������������� �����

	//���������� ����������� ������� 
	//����������, ������ �������� ����� �������� ���� ��������� �������
	//���������� �������� ����� �������� (Vcorr[cell]) �� ���������� (cell) ������ �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
    void CalculateBound(const vector<vector<double>>& UU, const vector<vector<double>>& VV, const int cell);
public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//dimension - ����� �������������� ����������,
	//ind - ������, �������� ������������ �������,
	//degree - �������� ��������, ���������� ���������� wg)
    //LimiterWENOH(const BaseParams& prm, const int dimension, const Indicator& ind, double degree);
    LimiterWENOH(const BaseParams& prm, const Problem& prb, \
                 const Indicator& ind, double degree);
	//����������
    ~LimiterWENOH();
};

#endif

