#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "defs.h"

class Problem
{
protected:
	//��������� �� ������ � ����������� ������
	const BaseParams* ptrprm;

public:
	//����������� ������ (���������� �������������� ����������)
	int dim;

	//���������� �������� �������
	int nshape;

	function<double(double)> shapefunc[3];
	double shapefuncnorm2[3];

	//��������� �� �������, ���������� ��������� ������� (U) ���� (\rho, Ux, Uy, Uz, p)
	vector<std::function<double(const double)>> init; 

	//����������� �������
	//���������� �������� (sd = left/right) q-� ���������� �������,
	//�������������� �� ������� (U) � ������� (V)
	virtual inline double side_val(const vector<vector<double>>& sol, var q, side sd) const = 0;
	virtual inline vector<double> gauss_val(const vector<vector<double>>& sol, double Lcoord) const = 0;


	//����������� �������
	//���������� �������������� ������ Flux �� ��������� ������� U
	virtual void getFlux(const vector<double>& U, vector<double>& Flux) const = 0;
	virtual vector<double> getFlux(const vector<double>& U) const = 0;

	//������������� ������, ����������� �� �������:
	//  - � ������ ������ (FLUX), 
	//  - �� ����� ����� (LFLUX), 
	//  - �� ������ ����� (RFLUX)
	// � �������� n � (n+1) - ��������� ������
	vector<vector<double>> FLUX, LFLUX, RFLUX;

	//���������� ������� ������� ��� ���� �����:
	//  - �� ������� � ������ �����: conv_flux(UU)
	//  - �� ������� � ������ �����, �� ����� � ������ �����: conv_flux(UU, VV) � ������ ��������� �����
//	void convFlux(const vector<vector<double>>& UU);
	void convFlux(const vector<vector<vector<double>>>& SOL);
		

	//����������� �������
	//���������� ������ ����. ���������� � ����� x, ����������� �� �������� � ������� Param ��������� ��������
	virtual vector<double> initial_var(const double x) const = 0;


	virtual void EigenMatricies(const vector<vector<double>>& sol, \
		vector<vector<double>>& LL, \
		vector<vector<double>>& RR) const = 0;

	//����������� ������� � ������ ����������� �� ���������
	//������ � ��������
	virtual void more_to_file(ostream& str, \
		const vector<vector<vector<double>>>& SOL, int cell) const {	};


	Problem(const BaseParams& prm, int dimension, int nshapefunctions, vector<std::function<double(const double)>> initv);
	~Problem();
};

#endif