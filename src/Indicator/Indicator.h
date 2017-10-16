#ifndef INDICATOR_H_
#define INDICATOR_H_

#include <vector>

#include "defs.h"
#include "Problem.h"

using namespace std;

class Indicator
{
private:

protected:
	//��������� �� ������ � ����������� ������
    const BaseParams* ptrprm;
	const Problem* ptrprb;
public:
	//����������� (prm - ������, ���������� ��������� ������, prb - ������ �� �������� ������)
	Indicator(const BaseParams& prm, const Problem& prb);
    
	//����������
	~Indicator();
    	
	//����������� ������� 
	//����������, ������ �������� ������������ �������
	//���������� �������� ������������ ������� (Ind) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
    virtual void calc_indicator(const vector<vector<vector<double>>>& SOL, \
        vector<double>& Ind) const = 0;
};

#endif
