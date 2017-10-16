#include "LimiterHWENO_SC_Char.h"
#include "Integrator.h"


//����������� �������� HWENO_SC_Char
LimiterHWENO_SC_Char::LimiterHWENO_SC_Char(const BaseParams& prm, const Problem& prb, \
    const Indicator& ind, double degree) : Limiter(prm, prb, ind)
{
	wg = degree;
}

//���������� ��������
LimiterHWENO_SC_Char::~LimiterHWENO_SC_Char()
{}


void LimiterHWENO_SC_Char::CalculateBound(const vector<vector<vector<double>>>& SOL, const int cell)
{
	// ��������� ������� ���������.
	int nx = ptrprm->nx;
	double h = ptrprm->h;
	int dim = ptrprb->dim;
	int nshape = ptrprb->nshape;

	//���������� ������� ���������� ������. ��� �������������, ����������� ��������� �����.
	const vector<vector<double>>& leftSol = (cell > 0) ? SOL[cell - 1] : SOL[nx];
	const vector<vector<double>>& troublSol = SOL[cell];
	const vector<vector<double>>& rightSol = (cell < nx - 1) ? SOL[cell + 1] : SOL[nx + 1];

	//������� ��� ����������� ��������.
	vector<vector<double>> LL; 
	vector<vector<double>> RR;
	LL.resize(dim);
	RR.resize(dim);
	for (int j = 0; j < dim; ++j)
	{
		LL[j].resize(dim);
		RR[j].resize(dim);
	}// for j

	// ��������� ������� ����������� ��������.
	ptrprb->EigenMatricies(troublSol, LL, RR);

	// �������� ����.
	double ak = 0.001;
	double gamma0 = ak;
	double gamma1 = 1.0 - 2.0*ak;
	double gamma2 = ak;

	
	// ������ ��- � �������������� ��������� � ������������������ ������������.
	vector<vector<vector<double>>> auxSOL;
	vector<vector<double>> auxSOLcorr;
	auxSOL.resize(3);
	auxSOLcorr.resize(nshape);
	for (int j = 0; j < nshape; ++j)
	{
		auxSOLcorr[j].resize(dim);
	}// for j
	for (int i = 0; i < 3; ++i)
	{
		auxSOL[i].resize(nshape);
		for (int j = 0; j < nshape; ++j)
		{
			auxSOL[i][j].resize(dim);
		}// for j		
	}// for i

	// ���������� � ������� �� ������ HWENO_SC --- �������� ������� �� ����� ����������� ��������.
	for (int j = 0; j < nshape; ++j)
	{
		prodMatrVec(LL, leftSol[j],   auxSOL[0][j]);
		prodMatrVec(LL, troublSol[j], auxSOL[1][j]);
		prodMatrVec(LL, rightSol[j],  auxSOL[2][j]);
	}


	// ���� �� �������������� ���������� 
	for (int val = 0; val < dim; ++val)
	{
		// ��������������� �������� ������� � ����� �������.
		const double& ul = auxSOL[0][0][val];
		const double& u = auxSOL[1][0][val];
		const double& ur = auxSOL[2][0][val];
		const double& vl = auxSOL[0][1][val];
		const double& v = auxSOL[1][1][val];
		const double& vr = auxSOL[2][1][val];
		
		// ������ ����������, ���� ����� ������� �� �����������. ������ ������ ������ ����� if(nshape).
		double beta0, beta1, beta2;
		// ������ ��� ������� ���������: ������������ ��� ������ ����������������.
		vector<vector<double>> SIDE_auxSOL;
		SIDE_auxSOL.resize(nshape);
		for (int j = 0; j < nshape; ++j)
			SIDE_auxSOL[j].resize(2);

		double p;
		
		// ������ ������� �� �������� � ����������� �� nshape.
		if (nshape == 2)
		{
			// Evaluating modified with LSM polynomials. Operating with slopes seems to be enough.
			SIDE_auxSOL[1][0] = (2.0*vl / h + 12.0 * (u - ul) / h) / 13.0;
			p = 2.0 *v / h;
			SIDE_auxSOL[1][1] = (2.0*vr / h + 12.0 * (ur - u) / h) / 13.0;

			// Calculating the smothness indicators for modified polynomials at the troubled cell. 
			beta0 = SIDE_auxSOL[1][0]*SIDE_auxSOL[1][0] * h * h;
			beta1 = p*p * h * h;
			beta2 = SIDE_auxSOL[1][1]*SIDE_auxSOL[1][1] * h * h;

		}//if nshape
		
		if (nshape == 3)
		{
			const double& wl = auxSOL[0][2][val];
			const double& w = auxSOL[1][2][val];
			const double& wr = auxSOL[2][2][val];


			// ���������������� �������� �������� ����� (�� ���)
			SIDE_auxSOL[0][0] = (u + 192.0*ul - 2.0*(vl + 3.0*wl)) / 193.0;
			SIDE_auxSOL[1][0] = (6.0*u - 6.0*ul + 181.0*vl - 36.0*wl) / 193.0;
			SIDE_auxSOL[2][0] = (30.0*u - 30.0*ul - 60.0*vl + 13.0*wl) / 193.0;

			SIDE_auxSOL[0][1] = (u + 2.0 * (96.0 * ur + vr - 3.0 * wr)) / 193.0;
			SIDE_auxSOL[1][1] = (-6.0*u + 6.0*ur + 181.0*vr + 36.0*wr) / 193.0;
			SIDE_auxSOL[2][1] = (30.0*u - 30.0*ur + 60.0*vr + 13.0*wr) / 193.0;


			// ��������� ���������� ��������� ��������� ������� � ���������� ������. 
			beta0 = 4.0 * ((SIDE_auxSOL[1][0] + 6.0 * SIDE_auxSOL[2][0])*(SIDE_auxSOL[1][0] + 6.0 * SIDE_auxSOL[2][0]) + 39.0 * SIDE_auxSOL[2][0]*SIDE_auxSOL[2][0]);
			beta1 = 4.0 * (v*v + 39.0 * w*w);
			beta2 = 4.0 * ((SIDE_auxSOL[1][1] - 6.0 * SIDE_auxSOL[2][1])*(SIDE_auxSOL[1][1] - 6.0 * SIDE_auxSOL[2][1]) + 39.0 * SIDE_auxSOL[2][1]*SIDE_auxSOL[2][1]);
		}// if nshape
		// ��������� ���������� ����. ���������� ����� ������������ ����.
		double w0 = gamma0 / pow(weps + beta0, wg);
		double w1 = gamma1 / pow(weps + beta1, wg);
		double w2 = gamma2 / pow(weps + beta2, wg);
		// ���������� �����.
		double WWW = (w0 + w1 + w2);
		w0 = w0 / WWW; w1 = w1 / WWW; w2 = w2 / WWW;
		
		
		// ������ ��������� �������� �������� � ������ �������� �������� ������� � �������. 

		double t1, t2, t3,t4;
		t1 = w0*SIDE_auxSOL[nshape-1][0];
		t2 = w1*troublSol[nshape-1][val];
		t3 = w2*SIDE_auxSOL[nshape-1][1];
		t4 = t1 + t2 + t3;
		//if (fabs(t4) < weps) t4 = 0;
		auxSOLcorr[nshape-1][val] = t4;//(w0*leftSol[2][val] + w1*troublSol[2][val] + w2*rightSol[2][val]);
		
		if (nshape == 3)
		{
			t1 = w0*(SIDE_auxSOL[1][0] + 6.0 * SIDE_auxSOL[2][0]);
			t2 = w1*troublSol[1][val];
			t3 = w2*(SIDE_auxSOL[1][1] - 6.0 * SIDE_auxSOL[2][1]);
			t4 = t1 + t2 + t3;
			//if (fabs(t4) < weps) t4 = 0;
			auxSOLcorr[1][val] = t4;// (w0*(leftSol[1][val] + 6 * leftSol[2][val]) + w1*troublSol[1][val] + w2*(rightSol[1][val] - 6 * rightSol[2][val]));
		}//if nshapae

	}// for val

	// ����������� �������������� ������� ������� � ������������ �������������� ����������.
	for (int j = 1; j < nshape; ++j)
		prodMatrVec(RR, auxSOLcorr[j], SOLcorr[cell][j]);
}
