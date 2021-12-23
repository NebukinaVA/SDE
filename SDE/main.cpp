#include <iostream>
#include <string>
#include "DiffEq.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	//	test example(0.0, 1.0, 0.001, 1000, 1e-5, 2, 1e-3);
	//	task1 example(0.0, 1.0, 0.001, 200, 1e-5, 2, 1e-3);
	//	task2 example(0.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.001, 1000, 1e-5, 10.0, 1e-3);
	//	example.calculate_w_error();
	//	std::cout << example;
		// ------------------------
	int task, n;
	double t0, x0, a, h, xmax, prec;
	double D = 0.5;
	std::string str;
	bool flag = true;
	bool method;
	while (flag) {
		std::cout << "Выберите метод:\n0 - Метод Эйлера\n1 - Метод Хюна\n";
		std::cin >> method;
		std::cout << "Введите начальные условия:\n";
		std::cout << "t0 = ";
		std::cin >> t0;
		std::cout << "x0 = ";
		std::cin >> x0;
		bool param;
		std::cout << "Выберите параметр a:\n0 - a = 0.5\n1 - a = 1.5\n";
		std::cin >> param;
		if (param)
			a = 1.5;
		else a = 0.5;
		std::cout << "Задайте начальный шаг:\nh = ";
		std::cin >> h;
		std::cout << "Задайте максимальное число шагов:\nN = ";
		std::cin >> n;
		std::cout << "Задайте правую границу по х:\nxmax = ";
		std::cin >> xmax;
		std::cout << "Задайте точность выхода на правую границу:\nprecision = ";
		std::cin >> prec;
		bool noise;
		std::cout << "Производить расчет с учетом шума?\n1 - Да\n0 - Нет\n";
		std::cin >> noise;
		if (!method && !noise)
			str = "Euler.dat";
		if (!method && noise)
			str = "EulerScheme.dat";	
		if (method && !noise)
			str = "Heun.dat";
		if (method && noise)
			str = "HeunScheme.dat";
		SDE equation(t0, x0, a, h, n, xmax, prec);
		equation.calculate(method, noise, D, str);
		std::cout << equation;
		std::cout << "\nХотите продолжить работу?\n1 - Да\n0 - Нет\n";
		std::cin >> flag;
	}
	return 0;
}