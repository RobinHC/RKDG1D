#ifndef BOUNDARYPERIODIC_H_
#define BOUNDARYPERIODIC_H_

#include <vector>

#include "Boundary.h"

#define Periodic BoundaryPeriodic 

class BoundaryPeriodic :
	public Boundary
{
protected:

public:
	BoundaryPeriodic(const BaseParams& prm, const Problem& prb);
	~BoundaryPeriodic();

	//���������� ����������� ������� 
	//����������, ���������� ������������ �� ����� �������� ������� � ��������� ������
	//���������� �������� ����� ������� U � �������� V
	//�� ����� (nx) � ������ (nx+1) ��������� �������
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	void FillVirtualCells(const vector<vector<vector<double>>>& SOL) const;
};

#endif