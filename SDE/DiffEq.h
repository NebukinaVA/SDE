#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
#include <iomanip>
#include <random>
#include <ctime>

// dx/dt = a - sin(x) = f

class SDE
{
private:
	double t0, x0;
	double tmax, prec; // right boarder
	double a; // coeff a
	double h; // step
	int n; // max number of steps
	std::vector<double> arg; //t
	std::vector<double> res; //x
	std::vector<double> steps; //h
	double func(double x)
	{
		return (a - sin(x));
	}
public:
	SDE(double _t0, double _x0, double _a, double _h, int _n, double _tmax, double _prec)
	{
		t0 = _t0;
		x0 = _x0;
		a = _a;
		h = _h;
		n = _n;
		tmax = _tmax;
		prec = _prec;
	}
	void reset(double _t0, double _x0, double _a, double _h, int _n, double _tmax, double _prec)
	{
		arg.clear();
		res.clear();
		steps.clear();
		t0 = _t0;
		x0 = _x0;
		a = _a;
		h = _h;
		n = _n;
		tmax = _tmax;
		prec = _prec;
	}
	double Euler(double tn, double xn, double h)
	{
		xn += h * func(xn);
		return xn;
	}
	double Heun(double tn, double xn, double h)
	{
		double k1 = func(xn);
		double k2 = func(xn + h * k1);
		xn += h * (k1 + k2) / 2.0;
		return xn;
	}
	double EulerScheme(double tn, double xn, double h, double r)
	{
		std::random_device rd;
		std::mt19937 RNG(rd());
		std::normal_distribution<double> dist(0.0, 1.0);
		xn += r * dist(RNG) + h * func(xn);		
		return xn;
	}
	double HeunScheme(double tn, double xn, double h, double r)
	{
		std::random_device rd;
		std::mt19937 RNG(rd());
		std::normal_distribution<double> dist(0.0, 1.0);
		double k1 = func(xn);
		double k2 = func(xn + r * dist(RNG) + h * k1);
		xn += r * dist(RNG) + h * (k1 + k2) / 2.0;
		return xn;
	}
	std::vector<double> calculate(bool method, bool noise, double D, std::string filename) // 0 - Euler, 1 - Heun
	{	                                                                         // 0 - basic, 1 - with noise
		std::ofstream file;
		file.open(filename);
		arg.push_back(t0);
		res.push_back(x0);
		steps.push_back(0.0);
		if (!(file.is_open()))
			return res;
		double tn = t0;
		double xn = x0;
		int i = 0;		
		double r = sqrt(2.0 * D * h);
		file << t0 << '\t' << x0 << std::endl;
		while (i < n)
		{
			if ((tn >= (tmax - prec)) && (tn <= tmax))
			{
				break;
			}
			else 
			{
				if ((tn + h) > tmax)
				{
					h = tmax - tn - prec / 2.0;
				}
				if (method)
				{
					if (noise)						
						xn = HeunScheme(tn, xn, h, r);
					else
						xn = Heun(tn, xn, h);
				}
				else
				{
					if (noise) 
						xn = EulerScheme(tn, xn, h, r);
					else
						xn = Euler(tn, xn, h);
				}
				tn += h;
				i++;
				file << tn << '\t' << xn << std::endl;
				arg.insert(arg.begin() + i, tn);
				res.insert(res.begin() + i, xn);
				steps.insert(steps.begin() + i, h);					
			}
		}	
		file.close();
		return res;
	}
	friend std::ostream & operator<<(std::ostream &out, SDE &sde)
	{
		if (sde.res.empty())
			out << "There are no calculated results yet.";
		else {
			out << "Расчет произведен\n" << std::endl;
			out << std::setw(5) << "n" << std::setw(12) << "h n-1" << std::setw(10) << "tn" << std::setw(15) << "xn" << std::endl;
			out << "------------------------------------------" << std::endl;
			for (int i = 0; i < sde.res.size(); i++)
			{
				out << std::setw(5) << i << std::setw(12) << sde.steps[i] << std::setw(10) << sde.arg[i] << std::setw(15) << sde.res[i] << std::setw(10) << std::endl;
			}
		}
		return out;
	}
};