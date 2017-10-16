#ifndef BOUNDARYWALL_H_
#define BOUNDARYWALL_H_

#include <vector>

#include "Boundary.h"

#define Wall BoundaryWall 

class BoundaryWall :
	public Boundary
{
protected:

public:
	BoundaryWall(const BaseParams& prm, const Problem& prb);
	~BoundaryWall();

	//���������� ����������� ������� 
	//����������, ���������� ������������ �� ����� �������� ������� � ��������� ������
	//���������� �������� ����� ������� U � �������� V
	//�� ����� (nx) � ������ (nx+1) ��������� �������
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	void FillVirtualCells(const vector<vector<vector<double>>>& SOL) const;
};

#endif