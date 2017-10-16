#include "Boundary.h"

//����������� ��
Boundary::Boundary(const BaseParams& prm, const Problem& prb)
{
	ptrprm = &prm;
	ptrprb = &prb;
}

//���������� ��
Boundary::~Boundary()
{
}

//����������� ������� (U, V, W) -> (copyU, copyV, copyW)
void Boundary::CopySol(const vector<vector<double>>& SOL, vector<vector<double>>& copySOL) const
{
	copySOL = SOL;	
};

