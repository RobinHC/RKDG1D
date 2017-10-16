#ifndef BOUNDARYSOFT_H_
#define BOUNDARYSOFT_H_

#include <vector>

#include "Boundary.h"

#define Soft BoundarySoft 

class BoundarySoft :
	public Boundary
{
protected:

public:
	BoundarySoft(const BaseParams& prm, const Problem& prb);
	~BoundarySoft();

	//���������� ����������� ������� 
	//����������, ���������� ������������ �� ����� �������� ������� � ��������� ������
	//���������� �������� ����� ������� U � �������� V
	//�� ����� (nx) � ������ (nx+1) ��������� �������
	//�������������� �� ������� (UU) � �������� (VV) �� ���� ������� �����
	void FillVirtualCells(const vector<vector<vector<double>>>& SOL) const;
};

#endif