// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <cmath>


using namespace std;

void AlgBoxMuller(int*arr, int it, int n)
{
	for (int i = it; i < n; i++)
	{

	}
}

int main()
{
	const double PI = 3.14159265;
	const int n = 1000000;
	int Max = 0, Min = 1000000;
	int Max1 = 0, Min1 = 1000000;
	unsigned int * a = new unsigned int[n];
	
	//double * DoubleArr = new double[n];
	
	double * DoubleBoxMiller = new double[n];
	for (int i = 0; i < n; i++)
	{
		DoubleBoxMiller[i] = 0;
	}
	
	fstream Fin("1.txt");
	
	for (int i = 0; i < n; i++)
	{
		Fin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		if (Min > a[i]) Min = a[i];
		if (Max < a[i]) Max = a[i];
	}
	cout << Max << endl << Min << endl;

	for (int i = 0; i < n; i+=2)
	{

		//DoubleArr[i]= (double)a[i]/Max;
		double Fi = (double)a[i] / Max;
		//DoubleArr[i+1] = (double)a[i+1] / Max;
		
		double r = (double)a[i+1] / Max;
		double TwoPiFi = 2 * PI*Fi;
		double Cos = cos(TwoPiFi);
		double Koren = sqrt(-2*log(r+0.000001));
		DoubleBoxMiller[i] = Cos*Koren;
		DoubleBoxMiller[i + 1] = sqrt(1.0-Cos*Cos)*Koren;
		//cout << DoubleBoxMiller[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		if (Min1 > DoubleBoxMiller[i]) Min1 = DoubleBoxMiller[i];
		if (Max1 < DoubleBoxMiller[i]) Max1 = DoubleBoxMiller[i];
	}
	cout << Max1 << endl << Min1 << endl;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
