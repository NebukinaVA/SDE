#include <iostream>
#include <string>
#include "DiffEq.h"

int main()
{
	setlocale(LC_ALL, "Russian");	
	int n;
	double t0, x0, a, h, xmax, prec;
	double D = 0.5;
	std::string str;
	bool flag = true;
	bool method;
	while (flag) {
		std::cout << "�������� �����:\n0 - ����� ������\n1 - ����� ����\n";
		std::cin >> method;
		std::cout << "������� ��������� �������:\n";
		std::cout << "t0 = ";
		std::cin >> t0;
		std::cout << "x0 = ";
		std::cin >> x0;
		bool param;
		std::cout << "�������� �������� a:\n0 - a = 0.5\n1 - a = 1.5\n";
		std::cin >> param;
		if (param)
			a = 1.5;
		else a = 0.5;
		std::cout << "������� ��������� ���:\nh = ";
		std::cin >> h;
		std::cout << "������� ������������ ����� �����:\nN = ";
		std::cin >> n;
		std::cout << "������� ������ ������� �� �:\nxmax = ";
		std::cin >> xmax;
		std::cout << "������� �������� ������ �� ������ �������:\nprecision = ";
		std::cin >> prec;
		bool noise;
		std::cout << "����������� ������ � ������ ����?\n1 - ��\n0 - ���\n";
		std::cin >> noise;
		if (!(method) && !(noise))
			str = "Euler.txt";
		if (!(method) && noise)
			str = "EulerScheme.txt";	
		if (method && !(noise))
			str = "Heun.txt";
		if (method && noise)
			str = "HeunScheme.txt";
		SDE equation(t0, x0, a, h, n, xmax, prec);
		equation.calculate(method, noise, D, str);
		std::cout << equation;
		std::cout << "\n������ ���������� ������?\n1 - ��\n0 - ���\n";
		std::cin >> flag;
	}
	return 0;
}