// RKDG-1D.cpp: ���������� ����� ����� ��� ����������� ����������.
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "defs.h"
#include "Params.h"
#include "Mesh1D.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	//�������������� ��������� ������
	//Params prm(LeftTriangle);
	Params prm(Sod);
	//Params prm(BrioWu);
	//Params prm(Lax);
	//Params prm(Rarefaction);
	//Params prm(leftWoodward);
	//Params prm(rightWoodward);
    //Params prm(Shock);
	//Params prm(TestSmallTravelingWave);
	
	//�������������� ����� � ��������� ������� � ��������� ������ �������
	Mesh1D mesh(prm);

	//���������� ���� �� �������
	do
	{
		mesh.TimeStepping();
	}
	while (!mesh.finished());
	
    return 0;
}
