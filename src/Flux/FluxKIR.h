#ifndef FLUXKIR_H_
#define FLUXKIR_H_

#include <vector>
#include <cmath>
#include <algorithm>

#include "Flux.h"
#include "ProblemGas1D.h"

#define KIR FluxKIR

using namespace std;


class FluxKIR : 
	public Flux
{
private:
	//����� � ������ ����������� ������� �� ���� ����� (����� i-� � (i-1)-� ��������)
    vector<vector<vector<double>>> LW, RW; 

	//����������� ����� �� ���� ����� (����� i-� � (i-1)-� ��������) 
    vector<vector<double>> L;    

	//��������� ����������: ������� - ��������� ������������ RW * L * LW
    vector<vector<double>> LMatr, RMatr;

	//��������� ����������: ������� - ������ ������� �� �������� i-� ������
	vector<double> LdU, RdU;

	//��������� ����������: ������� - ��������� ������������ Matr * dU
    vector<double> ProdL, ProdR;	

public:
	//�����������  (prm - ������, ���������� ��������� ������)
	FluxKIR(const BaseParams& prm, Problem& prb);

	//����������
    ~FluxKIR();

	//���������� ����������� ������� 
	//����������, ��� �������
	//���������� ���������� ������� (DU) � �������� (DV) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	//��������� �������� ��������� ������� � �������� ���������� �� cft
	//(��� ���������� ������ ������ ������ ������� �������� cft = ptrprm->tau)
    void step(const vector<vector<double>>& UU, const vector<vector<double>>& VV, \
		vector<vector<double>>& DU, vector<vector<double>>& DV, \
        const double cft);
};

#endif
