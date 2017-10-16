#include "FluxKIR.h"

//����������� ���
FluxKIR::FluxKIR(const BaseParams& prm, Problem& prb) : Flux(prm, prb)
{
    int nx = ptrprm->nx;

    //��������� ��� RW, LW
    LW.resize(nx + 1); 	RW.resize(nx + 1);
    for (int row = 0; row < nx + 1; ++row)
    {
        LW[row].resize(5);
        RW[row].resize(5);
        for (int col = 0; col < 5; ++col)
        {
            LW[row][col].resize(5);
            RW[row][col].resize(5);
        }
    }

    //��������� ��� L
    L.resize(nx + 1);
    for (int row = 0; row < nx + 1; ++row)
    {
        L[row].resize(5);
    }

    //��������� ��� ����������� RW |L| LW
    LMatr.resize(5), RMatr.resize(5);
    for (int row = 0; row < 5; ++row)
    {
        LMatr[row].resize(5);
        RMatr[row].resize(5);
    }

    //��������� ��� ����������� (���������) �������
    LdU.resize(5), RdU.resize(5), ProdL.resize(5), ProdR.resize(5);
}//KIR::KIR

//���������� ���
FluxKIR::~FluxKIR()
{};


void FluxKIR::step(const vector<vector<double>>& UU, const vector<vector<double>>& VV, \
	vector<vector<double>>& DU, vector<vector<double>>& DV, \
    const double cft)
{
    int nx = ptrprm->nx;
	double h = ptrprm->h;
	int dim = ptrprb->dim;

	//������� ������������ ������
	ptrprb->convFlux(UU, VV);

    //������� ����������� ������� � ����������� �����
	ptrprb_toGas->omega(UU, VV, LW, RW, { 0, (dim - 1) / 2 - 1, (dim - 1) / 2, (dim - 1) / 2 + 1, dim - 1 });
	ptrprb_toGas->lambda(UU, VV, RoeSoundVel, L, { 0, (dim - 1) / 2 - 1, (dim - 1) / 2, (dim - 1) / 2 + 1, dim - 1 });

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
		setlocsolflux(UU, VV, cell);

        //������ �������� ������� �� �������
        for (size_t val = 0; val < 5; ++val)
        {
            LdU[val] = side_val(myu(), myv(), (var)val, side::left) - side_val(leftu(), leftv(), (var)val, side::right);
            RdU[val] = side_val(rightu(), rightv(), (var)val, side::left) - side_val(myu(), myv(), (var)val, side::right);
        }

        //����������� ��, ��������� - � �������� LMatr, RMatr
        prodWrAbsLWl(RW[cell], LW[cell], L[cell], LMatr);
        prodWrAbsLWl(RW[cell + 1], LW[cell + 1], L[cell + 1], RMatr);

        //����������� �� ������ �������
        prodMatrVec(LMatr, LdU, ProdL);
        prodMatrVec(RMatr, RdU, ProdR);

        //������������� ������� �������� � ������
        for (size_t val = 0; val < 5; ++val)
        {
            DU[cell][val] = -0.5*(cft / h)*(((rightfluxL()[val] + myfluxR()[val]) - (myfluxL()[val] + leftfluxR()[val])) \
                - (ProdR[val] - ProdL[val]));
            
			//�� ������� ����������� ���������������
			//DV[cell][val] = -1.5*(cft / h)*(-4.0*myflux[val] + ((rightfluxL[val] + myfluxR[val]) + (myfluxL[val] + leftfluxR[val])) \
            //    - (ProdR[val] + ProdL[val]));

			//�� ������� ��������
			DV[cell][val] = -1.5*(cft / h)*(-4.0*(myfluxL()[val]+4.0*myflux()[val]+myfluxR()[val])/6.0 + ((rightfluxL()[val] + myfluxR()[val]) + (myfluxL()[val] + leftfluxR()[val])) \
			                - (ProdR[val] + ProdL[val]));
        }

    }//for cell

}//KIR::step
