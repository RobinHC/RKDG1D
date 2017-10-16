#ifndef FLUXGODUNOVTYPE_H_
#define FLUXGODUNOVTYPE_H_

#include <vector>
#include <cmath>
#include <algorithm>

#include "defs.h"
#include "Flux.h"
#include "Problem.h"
#include "ProblemTransfer1D.h"


using namespace std;

#define GodunovType FluxGodunovType


//���������� �������-������������ ��� ������� ���������� ������:
//  - ����� �.�. �������� (������ ������, ���������, 1-� �������)
//  - �����, ������������ �� ��������� ������� � ����� � ������ ������� (�����������, 2-� �������)
//  - ����� ���-���� (���������, 2-� �������)

#define Godunov phiGodunov
double phiGodunov(const double r);

#define CentralDiff phiCentralDiff
double phiCentralDiff(const double r);

#define vanLeer phivanLeer
double phivanLeer(const double r);


class FluxGodunovType :
	public Flux
{
private:

	//����� ����� - ������� ��� ��������:
	double thres;

	//������ �� �������-������������ (phiGodunov, phivanLeer...)
	double(*const phi)(const double);

	//������� ���������� ������, 
	//������������ �� ������� ����� (UL) � ������ (UR) �� �������,
	//�������� r ��� ���������� val
	double FluxNum(const vector<double>& fluxL, const vector<double>& fluxR, const double r, const var val);

	//��������� �� ������� ������� � ������ ����� ���� �����
	const vector<vector<double>> *ptr_leftleftsol;

protected:
	const vector<vector<double>>& leftleftsol()  { return *ptr_leftleftsol; };

	//����������� �������
	//��������� ��������� ���������� (����� �������� ����������������� ������): 
	// - �� ����. ������ � ����� ������
	// - �� ���������� (����� � ������) ������ � ��������� �������
	// - �� ������� � ����� ������ � � �������� �������
	virtual void setlocsolflux(const vector<vector<vector<double>>>& SOL, const int cell);


public:
	//����������� (prm - ������, ���������� ��������� ������, 
	//            phi - �������-������������)
	FluxGodunovType(const BaseParams& prm, Problem& prb,\
		double(*const phi_)(const double), double thres);

	//����������
	~FluxGodunovType();

	//���������� ����������� ������� 
	//����������, ��� �������
	//���������� ���������� ������� (DU) � �������� (DV) �� ���� ������� �����
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	//��������� �������� ��������� ������� � �������� ���������� �� cft
	//(��� ���������� ������ ������ ������ ������� �������� cft = ptrprm->tau)
	void step(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& DSOL, \
		const double cft);
};



#endif
