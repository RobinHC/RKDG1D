#ifndef MESH1D_H_
#define MESH1D_H_

#include <vector>
#include <sstream>
#include <fstream>

#include "defs.h"
#include "Params.h"

#include "Flux.h"
#include "Limiter.h"
#include "Timestep.h"



using namespace std;

class Mesh1D
{
private:
    const Params* ptrprm;

	//����� �������� ���� �� �������
	int step_num;

	//U1, V1 --- ������� � ������ �� �������/���������� ����
	//U2, V2 --- ������� � ������ �� �������/���������� ����
	//� �������� (n) � (n+1) - ����� � ������ ��������� ������ ��������������
	vector<vector<vector<double>>> SOL1;
	vector<vector<vector<double>>> SOL2;
	  
    //ptrU,    ptrV     ---  ��������� �� ������� � ������� �� ���������� ����
	//ptrUnew, ptrVnew  ---  ��������� �� ������� � ������� �� ������� ����
	vector<vector<vector<double>>> *ptrSOL;
	vector<vector<vector<double>>> *ptrSOLnew;
	
	//����� ������, ��������� � ��������� ������ (����������)
	ofstream telefile;
    
	//������������� ���������
    void init_telefile();


	//���������� ������� ������� �� 0-� ���� ���������� ���������
	void set_initial();

public:
	//���������� ������� ����� ���� �� �������
	int step() const { return step_num; }
	
	//���������� ��������� �� ������� �� ���������� ����
    const vector<vector<vector<double>>>& SOL() const { return *ptrSOL; };

	//���������� ��������� �� ������� �� ������� ����
    vector<vector<vector<double>>>& SOLnew() const { return *ptrSOLnew; };

	//���������� ������ ���� �� �������
	void TimeStepping();

	//������� ����, ��� ���� ��������
	bool finished() const { return !(step_num * ptrprm->basic.tau < ptrprm->basic.T); }
	    
	//����������� (prm - ������, ���������� ��������� ������)
    Mesh1D(const Params& prm_);

	//����������
    ~Mesh1D();

	//���������� ��������� ������ i-� ������ �����
    double cnt(const int i){ return (ptrprm->basic.h) * (i + 0.5); };

	//���������� ���������� � ������� �� ������� ���� � ��������
    void add_to_telefile();      
};


#endif

