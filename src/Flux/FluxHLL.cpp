#include "FluxHLL.h"
#include "Integrator.h"

//����������� HLL
FluxHLL::FluxHLL(const BaseParams& prm, Problem& prb, SoundVelType soundvel) : Flux(prm, prb), SoundVel(soundvel)
{
    int nx = ptrprm->nx;

    //��������� ��� L
    L.resize(nx + 1);
    for (int row = 0; row < nx + 1; ++row)
    {
        L[row].resize(2);
    }

    //��������� ��� ����������� (���������) �������
    LdU.resize(5), RdU.resize(5), hllL.resize(5), hllR.resize(5);
}

//���������� HLL
FluxHLL::~FluxHLL()
{};

void FluxHLL::step(const vector<vector<vector<double>>>& SOL, \
	vector<vector<vector<double>>>& DSOL, \
	const double cft)
{
    int nx = ptrprm->nx;
    double h = ptrprm->h;
	int dim = ptrprb->dim;

	//������� ������������ ������
	ptrprb->convFlux(SOL);

    //������� ����������� �����
	ptrprb_toGas->lambda(SOL, SoundVel, L, { 0, dim - 1 });

    //�������� ���� �� �������
    for (int cell = 0; cell < nx; ++cell)
    {
		//��������� ������ �� ������� �� ���� �������	:
		//  myu(), myv() - �� ����� ������
		//  leftu(), leftv() - �� �������� ����� ������
		//  rightu(), rightv() - �� �������� ������ ������ 
		//� �� ����.������ �� ���� �������:
		//  myflux(), myfluxL(), myfluxR() - ����.������ �� ����� ������ (�� ������, �����, ������)
		//  rightfluxL(), leftfluxR() - ����.������ �� ������ � ����� �������� ������� (�����, ������)
		setlocsolflux(SOL, cell);

        //������ �������� ������� �� �������
        for (size_t val = 0; val < 5; ++val)
        {
			LdU[val] = side_val(mysol(), (var)val, side::left)       - side_val(leftsol(), (var)val, side::right);
			RdU[val] = side_val(rightsol(), (var)val, side::left) - side_val(mysol(), (var)val, side::right);
        }
		
		//�������� ����������� ��������
		if (L[cell][0] > 0)
			for (size_t val = 0; val < 5; ++val)
				hllL[val] = leftfluxR()[val];
		else
		if (L[cell][1] < 0)
			for (size_t val = 0; val < 5; ++val)
				hllL[val] = myfluxL()[val];
		else
			for (size_t val = 0; val < 5; ++val)
				hllL[val] = (L[cell][1] * leftfluxR()[val] - L[cell][0] * myfluxL()[val] + L[cell][1] * L[cell][0] * LdU[val]) / (L[cell][1] - L[cell][0]);

		//�������� ����������� ��������
		if (L[cell+1][0] > 0)
			for (size_t val = 0; val < 5; ++val)
				hllR[val] = myfluxR()[val];
		else
		if (L[cell+1][1] < 0)
			for (size_t val = 0; val < 5; ++val)
				hllR[val] = rightfluxL()[val];
		else
			for (size_t val = 0; val < 5; ++val)
				hllR[val] = (L[cell+1][1] * myfluxR()[val] - L[cell+1][0] * rightfluxL()[val] + L[cell+1][1] * L[cell+1][0] * RdU[val]) / (L[cell+1][1] - L[cell+1][0]);            
        

			int ngp = 3;
			Integrator GP(IntegrPoints::Gauss, ngp);

			function<vector<double>(double)> flx = [&](double x) {return ptrprb->getFlux(ptrprb->gauss_val(mysol(), x)); };

			vector<double> intFL1 = GP.integrate([&](double pts) {return flx(pts)*2.0; }, dim);
			vector<double> intFL2 = GP.integrate([&](double pts) {return flx(pts)*6.0*pts; }, dim);

			//������������� ������� �������� � ������
			for (size_t val = 0; val < 5; ++val)
			{
				DSOL[cell][0][val] = -(cft / h) * (hllR[val] - hllL[val]);
				DSOL[cell][1][val] = -3.0*(cft / h) * (-intFL1[val] + hllR[val] + hllL[val]);

				if (ptrprb->nshape > 2)
					DSOL[cell][2][val] = -5.0*(cft / h) * (-intFL2[val] + hllR[val] - hllL[val]);
			}
    }
}

