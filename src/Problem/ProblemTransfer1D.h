#ifndef PROBLEMTRANSFER1D_H_
#define PROBLEMTRANSFER1D_H_

#define Transfer1D ProblemTransfer1D

#include "Problem.h"
class ProblemTransfer1D :
	public Problem
{
private:
	
protected:

	//����������� �������
	//���������� ������������� ������ �� ��������� ������� �������
	virtual void getFlux(const vector<double>& U, vector<double>& Flux) const;

public:
	ProblemTransfer1D(const BaseParams& prm, int order, vector<std::function<double(const double)>> initv, \
		std::function<double(const double)> vel);
	~ProblemTransfer1D();

	//�������, ������������ �������� ��������
	std::function<double(const double)> physflux;

	//����������� �������
	//���������� �������� (sd = left/right) q-� ���������� �������,
	//�������������� �� ������� (U) � ������� (V)
	virtual inline double side_val(const vector<vector<double>>& sol, var q, side sd) const;
	
	//����������� �������
	//���������� �������� ���������� q � ����� x, ����������� �� �������� � ������� Param ��������� ��������
	// cft = 0 --- ������� ��������
	// cft = 1 --- ������
	virtual double initial_var(const double x, const var q, const int cft) const;

	//����������� �������
	//������ � ��������
	//virtual void more_to_file(ostream& str, \
	//	const vector<vector<double>>& UU, const vector<vector<double>>& VV, int cell) const;

	void EigenMatricies(const vector<vector<double>>& sol, \
		vector<vector<double>>& LL, \
		vector<vector<double>>& RR) const {};
};

#endif