#ifndef LIMITER_H_
#define LIMITER_H_

#include <vector>

#include "Indicator.h"
#include "Problem.h"

using namespace std;

class Limiter
{   
    private:
    protected:

		//������ �������� ������������ ������� �� ���� ������� �����
        vector<double> Ind;

		//����������������� ������� ���� ��������� ������� �� ���� �������
		vector<vector<vector<double>>> SOLcorr;

		//����������� ������� 
		//����������, ������ �������� ����� �������� ���� ��������� �������
		//���������� �������� ����� �������� (Vcorr[cell]) �� ���������� (cell) ������ �����
		//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
        virtual void CalculateBound(const vector<vector<vector<double>>>& SOL, \
            const int cell) = 0;
    
		//��������� �� ������, ���������� ��������� ������
		const BaseParams* ptrprm;

		//��������� �� ������, ���������� ��������� ������
		const Problem* ptrprb;

		//��������� �� ��������� (���������� ��� ������� �������� ������������ �������)
		const Indicator* ptrInd;

    public:

		//����������� (prm - ������, ���������� ��������� ������, 
		//dimension - ����� �������������� ����������,
		//ind - ������, �������� ������������ �������)
        Limiter(const BaseParams& prm, const Problem& prb, const Indicator& ind);
        
		//����������
		~Limiter();

		//�������, ���������� (��� �������������) ������ �������������� ��������
		//(���������� ������� VV)
		//�������������� �� ������� (UU) � �������� (VV) �� ���� �����
		void Bound(vector<vector<vector<double>>>& SOL);
};

#endif
