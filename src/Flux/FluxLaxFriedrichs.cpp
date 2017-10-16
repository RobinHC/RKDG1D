#include "FluxLaxFriedrichs.h"
#include "Integrator.h"

//����������� �����-���������
FluxLaxFriedrichs::FluxLaxFriedrichs(const BaseParams& prm, Problem& prb, SoundVelType soundvel) : Flux(prm, prb), SoundVel(soundvel)
{
    int nx = ptrprm->nx;
	int dim = ptrprb->dim;

    //��������� ��� L
    L.resize(nx + 1);
    for (int row = 0; row < nx + 1; ++row)
    {
        L[row].resize(2);
    }

    //��������� ��� ����������� (���������) �������
    LdU.resize(dim), RdU.resize(dim), lfL.resize(dim), lfR.resize(dim);
}

//���������� �����-���������
FluxLaxFriedrichs::~FluxLaxFriedrichs()
{};

void FluxLaxFriedrichs::step(const vector<vector<vector<double>>>& SOL, \
	vector<vector<vector<double>>>& DSOL, \
	const double cft)
{
    int nx = ptrprm->nx;
    double h = ptrprm->h;
	int dim = ptrprb->dim;

	ptrprb->convFlux(SOL);

		//������� ����������� �����
	ptrprb_toGas->lambda(SOL, SoundVel, L, { 0, dim - 1 });

    //?????????????????????????????????????????????????????????????
	//ptrprb_toMHD->lambda(SOL, L, { 0, dim - 1 });

    //// Experiment
	//double A = ptrprb_toMHD->CFLSpeedMax(SOL);

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
        for (size_t val = 0; val < dim; ++val)
        {
            LdU[val] = side_val(mysol(), (var)val, side::left) - side_val(leftsol(), (var)val, side::right);
            RdU[val] = side_val(rightsol(), (var)val, side::left) - side_val(mysol(), (var)val, side::right);
        }

		for (size_t val = 0; val < dim; ++val)
		{
			lfL[val] = 0.5*(leftfluxR()[val] + myfluxL()[val]) - 0.5*max(fabs(L[cell][0]), fabs(L[cell][1]))   *LdU[val];
			lfR[val] = 0.5*(myfluxR()[val] + rightfluxL()[val]) - 0.5*max(fabs(L[cell + 1][0]), fabs(L[cell + 1][1])) * RdU[val];
        }

		int ngp = 3;
		Integrator GP(IntegrPoints::Gauss, ngp);

		function<vector<double>(double)> flx = [&](double x) {return ptrprb->getFlux(ptrprb->gauss_val(mysol(), x)); };

        vector<double> intFL1 = GP.integrate([&](double pts) {return flx(pts)*2.0; }, dim);
        vector<double> intFL2 = GP.integrate([&](double pts) {return flx(pts)*6.0*pts; }, dim);

		//������������� ������� �������� � ������
		for (size_t val = 0; val < dim; ++val)
		{
			DSOL[cell][0][val] = -(cft / h) * (lfR[val] - lfL[val]);
			DSOL[cell][1][val] = -3.0*(cft / h) * (-intFL1[val] + lfR[val] + lfL[val]);

			if (ptrprb->nshape > 2)
				DSOL[cell][2][val] = -5.0*(cft / h) * (-intFL2[val] + lfR[val] - lfL[val]);
		}
    }
}

