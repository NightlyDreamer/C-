// Laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <random>
#include <thread>

using namespace std;

complex <double> ** Mas(int t,int m, int n, complex <double> **Lmas) {
	
	for (int j = t; j < m; j++) {
		for (int i = 0; i < n; i++) {
			double x, y, Re, Im;
			x = rand() % 10;
			y = rand() % 10;
			Re = exp(x) * cos(y);
			Im = exp(x) * sin(y);
			Lmas[j][i] = complex <double> (Re,Im);
		}
	}
	return Lmas;
}

void txt(complex <double> **G,int m,int n) {
	ofstream fout("x.txt");
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			fout << G[j][i] << ' ';
		}
		fout << endl;
	}
}
 
int main(){
	const int m = 1000, n = 1000;
	
	complex <double> **Arr = new complex <double> *[m];

	for (int i = 0; i < m; i++) {
		Arr[i] = new complex <double>[n];
	}
	
	thread tr1(&Mas, 0, 250, n, Arr);
	thread tr2(&Mas, 250, 500, n, Arr);
	thread tr3(&Mas, 500, 750, n, Arr);
	thread tr4(&Mas, 750, m, n, Arr);
	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();

	txt(Arr, m, n);
	return 0;
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
