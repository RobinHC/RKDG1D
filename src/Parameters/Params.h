#ifndef PARAMS_H_
#define PARAMS_H_

#include "defs.h"

//��� ������ "��� ������"
enum CaseName { Sod,  BrioWu, Lax, Rarefaction, leftWoodward, rightWoodward, Shock, TestSmallTravelingWave, TestSmooth, \
	LeftTriangle};

#include "Boundary.h"
#include "BoundaryWall.h"
#include "BoundaryPeriodic.h"
#include "BoundarySoft.h"

#include "Indicator.h"
#include "IndicatorKrivodonova.h"  //��������� ������������
//#include "IndicatorHarten.h"       //��������� �������
#include "IndicatorEverywhere.h"   //���������, ������� ����������� ������ (������������� ���������� � ���)
#include "IndicatorNowhere.h"      //���������, ������� �� ����������� �������

#include "Limiter.h"
#include "LimiterFinDiff.h"      //����� �������� ���������
#include "LimiterWENO.h"         //������� WENO
#include "LimiterWENO_S.h"         //������� WENO_S
#include "LimiterHWENO_SC.h"         //������� HWENO_SC
#include "LimiterHWENO_SC_Char.h"         //������� HWENO_SC_Char
#include "LimiterHWENO.h"         //������� WENO
//#include "LimiterWENOH.h"        //������� WENOH

#include "Timestep.h"       
#include "TimestepEuler.h"   //����� ����� ������
#include "TimestepRK2.h"     //����� �����-����� 2-�� �������
#include "TimestepRK2TVD.h"  //����� �����-����� 2-�� ������� (����� TVD)
#include "TimestepRK3TVD.h"  //����� �����-����� 3-�� ������� (����� TVD)

#include "Flux.h"            
//#include "FluxKIR.h"          //����� ���
#include "FluxHLL.h"          //����� HLL   
#include "FluxHLLC.h"         //����� HLLC
//#include "FluxHLLE.h"
#include "FluxLaxFriedrichs.h"//����� �����-���������
#include "FluxGodunovType.h"  //����� ���� �������� (phiGodunov, phiCentralDiff, phivanLeer)

#include "Problem.h"           //���������� ���������� ������
#include "ProblemGas1D.h"      //���������� ������� ��������, ��-� ������
#include "ProblemMHD1D.h"      //���������� M��
#include "ProblemTransfer1D.h" //���������� ��������� ��������

#include <vector>
#include <functional>
#include <memory>

using namespace std;

//������ ��� ������������� ��������� �������
//(������������� ����� �������� ������)
#define InitF(name, expr) function<double(const double)> name = [=](const double x) -> double { return (expr); }

//������ ��� ������������ ������� ��������� �������
#define InitVector(name, ...) vector<std::function<double(const double)>> name = __VA_ARGS__


class Params
{
private:
	//�������, ������������ ������������� ����
	std::function<double(const double)> zero;

public:
	//������� ���������
	BaseParams basic;

	//��������� �� ���������� ������, ��, ���������, �������, ���������� �� �������, �����
	Problem   *ptrprb;
	Boundary  *ptrbnd;
	Indicator *ptrind;
	Limiter   *ptrlim;
	Timestep  *ptrtst;
	Flux      *ptrflx;

	//��������� ������� ���������� (�������� ��������� �������)
	void SetBasicParams(double L, double T, int nx, double Co, int deltacnt)
	{
		basic.L = L;
		basic.T = T;
		basic.nx = nx;
		basic.Co = Co;
		basic.deltacnt = deltacnt;
		basic.h = L / nx;
		basic.tau = Co * L / nx;
	}


	//��� ������� ��� ��������� ���� ������ - ��� ���������� � � �����������
	//template <typename T>
	//void SetProblem() { ptrprb = new T(basic); }

	template <typename T, typename... Arg>
	void SetProblem(Arg... arg) { ptrprb = new T(basic, arg...); }

	//��� ������� ��� ��������� ���� �� - ��� ���������� � � �����������
	template <typename T>
	void SetBoundaryCondition() { ptrbnd = new T(basic, *ptrprb); }

	template <typename T, typename... Arg>
	void SetBoundaryCondition(Arg... arg) { ptrbnd = new T(basic, *ptrprb, arg...); }

	//��� ������� ��� ��������� ���� ���������� - ��� ���������� � � �����������
	template <typename T>
	void SetIndicator()	{ ptrind = new T(basic, *ptrprb); }

	template <typename T, typename... Arg>
	void SetIndicator(Arg... arg)
	{
		ptrind = new T(basic, *ptrprb, arg...);
	}

	//��� ������� ��� ��������� ���� �������� - ��� ���������� � � �����������
	template <typename T>
	void SetLimiter() { ptrlim = new T(basic, *ptrprb, *ptrind); }

	template <typename T, typename... Arg> 
	void SetLimiter(Arg... arg) { ptrlim = new T(basic, *ptrprb, *ptrind, arg...); }

	//��� ������� ��� ��������� ���� ����������� �� ������� - ��� ���������� � � �����������
	template <typename T>
	void SetTimestep() { ptrtst = new T(basic, ptrprb->dim, ptrprb->nshape, *ptrbnd); }

	template <typename T, typename... Arg>
	void SetTimestep(Arg... arg) { ptrtst = new T(basic, ptrprb->dim, ptrprb->nshape, *ptrbnd, arg...); }

	//��� ������� ��� ��������� ���� ���������� ������ - ��� ���������� � � �����������
	template <typename T>
	void SetFlux() { ptrflx = new T(basic, *ptrprb); }		

	template <typename T, typename... Arg>
	void SetFlux(Arg... arg) { ptrflx = new T(basic, *ptrprb, arg...); }


	//�����������:
	//problem - ������������� �������� ������
	Params(const CaseName SovingCase);

	//����������
	~Params()
	{
		delete ptrind;
		delete ptrlim;
		delete ptrbnd;
		delete ptrflx;
		delete ptrtst;
	};

};

#endif
