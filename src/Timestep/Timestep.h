#ifndef TIMESTEP_H_
#define TIMESTEP_H_

#include <vector>

#include "Flux.h"
#include "Limiter.h"
#include "Boundary.h"

class Timestep
{
protected:
	//��������� �� ������ � ����������� ������
	const BaseParams* ptrprm;
	
	//���������� �������������� ����������
	int dim;

	//��������� �� ��
	const Boundary* ptrbnd;

	//������� ���������� ������� ������� � ��������:
	vector<vector<vector<double>>> DSOL;
	
	//���� ������� U, V �� ��������� ������	
	void ApplyBoundary(const vector<vector<vector<double>>>& SOL);

public:
	//�����������
	Timestep(const BaseParams& prm, int dimension, int nshape, const Boundary& bnd);
	
	//����������
	virtual ~Timestep();

	//����������� ������� 
	//����������, ��� ������� ��������������� ��������� �������
	//���������� ������ ������� (Unew) � �������� (Vnew) �� ���� ������� �����
	//�������������� �� ������� (U) � �������� (V) �� ���� ������� �����.
	//��� �� ������� tau
	//��� ������� ������� ������������ ��������� ����� method, ������� lim.
	//(� ���������� ��� ������� ���������� ������� ������������ method.step(...)
	virtual void runstep(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& SOLnew, \
		const double tau, Flux& method, Limiter& lim) = 0;	
};

#endif