#ifndef PROBLEMMHD1D_H_
#define PROBLEMMHD1D_H_

#define MHD1D ProblemMHD1D

#include "Problem.h"
class ProblemMHD1D :
	public Problem
{
private:
	double gamma;
	double Hx;

	//��������� ����� �� ������� (left)-� � (right)-� �����
	double h_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//��������� ����� �� i-� ������
	double h(const vector<vector<double>>& sol) const;
	
	//�������� ����� �� ������� (left)-� � (right)-� �����
	double c_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//�������� ����� � i-� ������
	double c(const vector<vector<double>>& sol) const;

	//�������� �� ������� �����
	vector<double> v_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//�������� �� i-� ������
	vector<double> v(const vector<vector<double>>& sol) const;

	//������� �������� �� ������� (left)-� � (right)-� �����
	double v2_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//������� �������� �� i-� ������
	double v2(const vector<vector<double>>& sol) const;

	//���������� �������� ����� �� �������
	double d_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;

	//������������ �� �� ������� (left)-� � (right)-� �����
	vector<double> H_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//������������ �� �� i-� ������
	vector<double> H(const vector<vector<double>>& sol) const;
	//������� ������������ �� �� ������� (left)-� � (right)-� �����
	double H2_av(const vector<vector<double>>& solleft, const vector<vector<double>>& solright) const;
	//������� ������������ �� �� i-� ������
	double H2(const vector<vector<double>>& sol) const;

	// ������ ��������
	double PT(const vector<vector<double>>& sol) const;
	
	// ��������� ������������ ��� ������
	double B2(const vector<vector<double>>& sol) const;
	double B3(const vector<vector<double>>& sol) const;
	double S1(const vector<vector<double>>& sol) const;
	double AlfaF(const vector<vector<double>>& sol) const;
	double AlfaS(const vector<vector<double>>& sol) const;

	//// �������� ��������������� ����������
	//// ���������� �������� ��������������� �� ��������� ������
	//double CFLSpeedMax(const vector<vector<vector<double>>>& SOL) const;
	//// ������������� ��������
	//double SpeedAlfven(const vector<vector<double>>& sol) const;
	//// ������� ��������������� ��������
	//double Af(const vector<vector<double>>& sol) const;
	//// ��������� ��������������� ��������
	//double As(const vector<vector<double>>& sol) const;
	
   
protected:

	//����������� �������
	//���������� ������������� ������ �� ��������� ������� �������
	virtual void getFlux(const vector<double>& U, vector<double>& Flux) const;
	virtual vector<double> getFlux(const vector<double>& U) const;

public:
	ProblemMHD1D(const BaseParams& prm, int order, double gam, double Hx, vector<std::function<double(const double)>> initv);
	~ProblemMHD1D();

	//����������� �������
	//���������� �������� (sd = left/right) q-� ���������� �������,
	//�������������� �� ������� (U) � ������� (V)
	virtual inline double side_val(const vector<vector<double>>& sol, var q, side sd) const;
	virtual inline double val(const vector<vector<double>>& sol, var q) const;
	virtual inline vector<double> gauss_val(const vector<vector<double>>& sol, double Lcoord) const;
	
	// �������� ��������������� ����������
	// ���������� �������� ��������������� �� ��������� ������
	double CFLSpeedMax(const vector<vector<vector<double>>>& SOL) const;
	// ������������� ��������
	double SpeedAlfven(const vector<vector<double>>& sol) const;
	// ������� ��������������� ��������
	double Af(const vector<vector<double>>& sol) const;
	// ��������� ��������������� ��������
	double As(const vector<vector<double>>& sol) const;

	//�������� ����� (LW) � ������ (RW) ����������� �������� �� ���� ����� 
	//(�� ����� �������� ����� - ����� (i-1)-� � i-� ��������
	//������� ������, ��������� � ������ ������������� (�� �����������)
	//�������������� �� �������� (UU) � �������� (VV) �� ���� �����
	//(��� ������ ���)
	void omega(const vector<vector<vector<double>>>& SOL, \
		vector<vector<vector<double>>>& LW, \
		vector<vector<vector<double>>>& RW, \
		const initializer_list<int>& list) const;
	// ������� ����������� �������� �� ������
	void EigenMatricies(const vector<vector<double>>& sol, \
		vector<vector<double>>& LL, \
		vector<vector<double>>& RR) const;
	
	//�������� ����������� ����� (LL) �� ���� �����  
	//������� ������, ��������� � ������ ������������� (�� �����������)
	//(�� ����� �������� ����� - ����� (i-1)-� � i-� ��������
	//�������������� �� �������� (UU) � �������� (VV) �� ���� �����	
	void lambda(const vector<vector<vector<double>>>& SOL, \
		const SoundVelType soundveltype, \
		vector<vector<double>>& LL, \
		const initializer_list<int>& list) const;

	//����������� �������
	//���������� ������ ����. ���������� � ����� x, ����������� �� �������� � ������� Param ��������� ��������
	virtual vector<double> initial_var(const double x) const;

	//����������� �������
	//������ � ��������
	virtual void more_to_file(ostream& str, \
		const vector<vector<vector<double>>>& SOL, int cell) const;
};

#endif
