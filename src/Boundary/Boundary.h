#ifndef BOUNDARY_H_
#define BOUNDARY_H_

#include <vector>

#include "defs.h"
#include "Problem.h"
#include "ProblemGas1D.h"
#include "ProblemMHD1D.h"
#include "ProblemTransfer1D.h"

using namespace std;

#define SET_NO_CONST_REF(u, constu) vector<vector<double>>& u = const_cast<vector<vector<double>>&>(constu);

class Boundary
{
protected:
	//��������� �� ������, ���������� ��������� ������
	const BaseParams* ptrprm;

	//��������� �� ������, ���������� �������� ������
	const Problem* ptrprb;

	//����������� ������� (U, V, W) -> (copyU, copyV, copyW)
	void CopySol(const vector<vector<double>>& SOL, vector<vector<double>>& copySOL) const;

public:
	//����������� ������� 
	//����������, ���������� ������������ �� ����� �������� ������� � ��������� ������
	//���������� �������� ����� ������� U � �������� V
	//�� ����� (nx) � ������ (nx+1) ��������� �������
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	virtual void FillVirtualCells(const vector<vector<vector<double>>>& SOL) const = 0;

	//����������� (prm - ������, ���������� ��������� ������
	//prb - �������� ������
	Boundary(const BaseParams& prm, const Problem& prb);

	//����������
	~Boundary();
};

#endif
