#ifndef FLUXLAXFRIEDRICHS_H_
#define FLUXLAXFRIEDRICHS_H_

#include <vector>
#include <cmath>
#include <algorithm>

#include "Flux.h"
#include "ProblemGas1D.h"
#include "ProblemMHD1D.h"

#define LaxFriedrichs FluxLaxFriedrichs

using namespace std;

class FluxLaxFriedrichs :
    public Flux
{
private:

    //����������� ����� �� ���� ����� (����� i-� � (i-1)-� ��������) 
    vector<vector<double>> L;

    //������ �����-��������� �� ����� � ������ ����� ������
    vector<double> lfL, lfR;

    //��������� ����������: ������� - ������ ������� �� �������� i-� ������
    vector<double> LdU, RdU;

	//������ ���������� �������� �� ������� �����
	SoundVelType SoundVel;

public:

    //�����������  (prm - ������, ���������� ��������� ������)
	FluxLaxFriedrichs(const BaseParams& prm, Problem& prb, SoundVelType soundvel);

    //����������
    ~FluxLaxFriedrichs();

	void step(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& DSOL, \
		const double cft);
};

#endif