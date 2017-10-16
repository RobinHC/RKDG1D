#ifndef DEFS_H_
#define DEFS_H_

#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>

using namespace std;

//��� ������ "������� ����������"
enum var { r = 0, U = 0, \
	       rvx = 1, rvy = 2, rvz = 3, e = 4, \
		   Hy = 5, Hz = 6, \
		   vx = 101, vy = 102, vz = 103, p = 104 };

//������� ���������� �������� �����
enum SoundVelType { RoeSoundVel = 0, EinfeldtSoundVel = 1, SemisumSoundVel = 2 };

typedef struct
{
	double L;     // ����� ������� �������
	double T;     // ��������� ����� �������������

	int nx;       // ����� ����� �� ������������
	double Co;    // ����� �������
	int deltacnt; // ��� ������ � ����

	double h;     // ��� �� ������������
	double tau;   // ��� �� �������
} BaseParams;

//��� ������ "��������� ��������"
enum side { left, right };

//���������� ����� � �������
inline double sqr(const double p) { return p*p; };

//����������� � ������ �������� ������� ������� �������� �������
vector<vector<vector<double>>>& operator += (vector<vector<vector<double>>>& a, const vector<vector<vector<double>>>& b);

//����������� � ������ ���������� ������� ������� ���������� �������
vector<vector<double>>& operator += (vector<vector<double>>& a, const vector<vector<double>>& b);

//��������� �� ������ ���������� ������� ������� ���������� �������
vector<vector<double>>& operator -= (vector<vector<double>>& a, const vector<vector<double>>& b);

//���������� ����������� ������� �� �����
vector<vector<vector<double>>>& operator *= (vector<vector<vector<double>>>& a, const double b);
vector<vector<vector<double>>> operator * (const vector<vector<vector<double>>>& a, const double b);

//���������� ���������� ������� �� �����
vector<vector<double>>& operator *= (vector<vector<double>>& a, const double b);
vector<vector<double>> operator * (const vector<vector<double>>& a, const double b);

//���������� ������� �� �����
vector<double>& operator *= (vector<double>& a, const double b);
vector<double> operator * (const vector<double>& a, const double b);
vector<double> operator / (const vector<double>& a, const double b);

//����������� � ������ ������� �������
vector<double>& operator += (vector<double>& a, const vector<double>& b);

//��������� �� ������ ������� �������
vector<double>& operator -= (vector<double>& a, const vector<double>& b);


//��������� ������� �� ������
void prodMatrVec(const vector<vector<double>>& A, \
    const vector<double>& b, \
    vector<double>& c);

//��������� ������ �� ����������� �������� � ������. ����� (��� ���)
void prodWrAbsLWl(const vector<vector<double>>& Wr, \
    const vector<vector<double>>& Wl, \
    const vector<double>& L, \
    vector<vector<double>>& Prod);

#endif
