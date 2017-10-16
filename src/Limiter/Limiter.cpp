#include "Limiter.h"

//����������� ��������
Limiter::Limiter(const BaseParams& prm, const Problem& prb, const Indicator& ind)
{
	ptrprm = &prm;
	ptrprb = &prb;	
	ptrInd = &ind;
	
	int dim = ptrprb->dim;
	int nx = ptrprm->nx;
	
	
	//�������� ������ ��� ��� ����������� ����������
    Ind.resize(nx);
	
    //��������� ��� ������ ��������	
	int nshape = ptrprb->nshape;

	SOLcorr.resize(nx);
	
	for (int cell = 0; cell < nx; ++cell)
	{
		SOLcorr[cell].resize(nshape);		

		for (int shape = 0; shape < nshape; ++shape)
		{
			SOLcorr[cell][shape].resize(dim);
		}
	}	
}

Limiter::~Limiter()
{
}


void Limiter::Bound(vector<vector<vector<double>>>& SOL)
{
	int nshape = SOL[0].size();
	//��������� ��������
	ptrInd->calc_indicator(SOL, Ind);
        
	for (int cell = 0; cell < ptrprm->nx; ++cell)
	{
		//������� ��������� ��������
		if (Ind[cell] > 1.0)
		{
			CalculateBound(SOL, cell);
			//cout << cell << " ";
		}
	}
	//cout << endl;

    for (int cell = 0; cell < ptrprm->nx; ++cell)
    {
		//������� ��������� ��������
		if (Ind[cell] > 1.0)
			for (int i = 1; i < nshape; ++i)
				SOL[cell][i] = SOLcorr[cell][i];				     
    }
}
