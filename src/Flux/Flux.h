#ifndef FLUX_H_
#define FLUX_H_

#include <vector>

#include "defs.h"
#include "Problem.h"
#include "ProblemGas1D.h"
#include "ProblemMHD1D.h"

using namespace std;

class Flux
{
private:
	//��������� �� ������� ����. ������� �� ���� �������
	vector<double> *ptr_leftfluxR, *ptr_myflux, *ptr_myfluxL, *ptr_myfluxR, *ptr_rightfluxL;

	//��������� �� ������� ������� � ���� �������
	const vector<vector<double>> *ptr_mysol, *ptr_leftsol, *ptr_rightsol;


protected:
	//��������� �� ������ � ������ �����������
	const BaseParams* ptrprm;
			
	//��������� �� ������ ������
	Problem* ptrprb;
	ProblemGas1D* ptrprb_toGas;
	ProblemMHD1D* ptrprb_toMHD;

	//������� ��� ������ ����������� ������� �� ������ Problem
    double side_val(const vector<vector<double>>& sol, var q, side sd) const
	{
		return ptrprb->side_val(sol, q, sd);
	}

    vector<double> gauss_val(const vector<vector<double>>& sol, double Lcoord) const
	{
		return ptrprb->gauss_val(sol, Lcoord);
	}

	//������ �� ������� ����. ������� �� ���� �������
	vector<double>& myfluxL() { return *ptr_myfluxL; };
	vector<double>& myfluxR() { return *ptr_myfluxR; };
	vector<double>& myflux()  { return *ptr_myflux; };
	vector<double>& leftfluxR()  { return *ptr_leftfluxR; };
	vector<double>& rightfluxL() { return *ptr_rightfluxL; };

	//������ �� ������� ������� �� ���� �������
	const vector<vector<double>>& mysol() { return *ptr_mysol; };
	const vector<vector<double>>& leftsol()  { return *ptr_leftsol; };
	const vector<vector<double>>& rightsol() { return *ptr_rightsol; };
	

	//����������� ������� � �����������
	//��������� ��������� ���������� (����� �������� ����������������� ������): 
	// - �� ����. ������ � ����� ������
	// - �� ���������� (����� � ������) ������ � ��������� �������
	// - �� ������� � ����� ������ � � �������� �������
	virtual void setlocsolflux(const vector<vector<vector<double>>>& SOL, const int cell);




public: 

	//����������� (prm - ������, ���������� ��������� ������)
	Flux(const BaseParams& prm, Problem& prb);
	
	//����������
	~Flux();

	//����������� ������� 
	//���������� ���������� ������� (DU) � �������� (DV) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	//��������� �������� ��������� ������� � �������� ���������� �� cft
	//(��� ���������� ������ ������ ������ ������� �������� cft = ptrprm->tau)
	virtual void step(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& DSOL, \
		const double cft) = 0;
};

#endif

