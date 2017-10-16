#ifndef FLUXHLL_H_
#define FLUXHLL_H_

#include <vector>
#include <cmath>
#include <algorithm>

#include "Flux.h"
#include "ProblemGas1D.h"

using namespace std;

#define HLL FluxHLL

class FluxHLL :
    public Flux
{
private:

    //����������� ����� �� ���� ����� (����� i-� � (i-1)-� ��������) 
    vector<vector<double>> L;

    //������ HLL �� ����� � ������ ����� ������
    vector<double> hllL, hllR;

    //��������� ����������: ������� - ������ ������� �� �������� i-� ������
    vector<double> LdU, RdU;

	//������ ���������� �������� �� ������� �����
	SoundVelType SoundVel;

public:

    //����������� (prm - ������, ���������� ��������� ������)
	FluxHLL(const BaseParams& prm, Problem& prb, SoundVelType soundvel);

    //����������
    ~FluxHLL();

	void step(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& DSOL, \
		const double cft);

};


#endif