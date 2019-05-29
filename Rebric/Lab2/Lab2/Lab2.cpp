// Lab2.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <cmath>
#define Pi  3.14159265359


using namespace std;
const int N = 10, n = 1000000, z =1000000;

double * DoubleBoxMiller = new double[n];
mutex mutexHisto;

void AlgBoxMuller(int*arr, int it, int n, int Max){

	double *BoxMuller = new double[z];

	for (int i = it; i < n; i+=2){

		double Fi = (double)arr[i] / Max;
		double r = (double)arr[i + 1] / Max;

		double Cos = cos(2. * Pi*Fi);
		double Sin = sin(2.*Pi*Fi);
		double SQRT = sqrt(-2.*log(r));

		BoxMuller[i] = Cos * SQRT;
		BoxMuller[i + 1] = Sin *SQRT;
	}

	for (int i = it; i < n; i++){

		DoubleBoxMiller[i] = BoxMuller[i];
	}

	delete []BoxMuller;
}

int main()
{
	const int n = 1000000;
	int Max = 0, Min = 1000000;
	double Max1 = 0, Min1 = 1000000;
	int * a = new  int[n];

	unsigned int * Histo;
	Histo = new unsigned int[N];
	for (int i = 0; i < N; i++){

		Histo[i] = 0;
	}
	
	fstream Fin("B.txt");
	for (int i = 0; i < n; i++){

		Fin >> a[i];
		a[i] += 1;
	}

	for (int i = 0; i < n; i++){

		if (Min > a[i]) Min = a[i];
		if (Max < a[i]) Max = a[i];
	}
	cout << Max << endl << Min << endl << endl;

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	thread tr1(&AlgBoxMuller, a, 0, 500000, Max);
	thread tr2(&AlgBoxMuller, a, 500000, 1000000, Max);
	tr1.join();
	tr2.join();

	end = chrono::system_clock::now();

	for (int i = 0; i < n; i++){

		if (Min1 > DoubleBoxMiller[i]) Min1 = DoubleBoxMiller[i];
		if (Max1 < DoubleBoxMiller[i]) Max1 = DoubleBoxMiller[i];
	}
	cout << Max1 << endl << Min1 << endl << endl;

	for (int i = 0; i < n; i++){

		if (DoubleBoxMiller[i] < 0)
			Histo[(int)floor(DoubleBoxMiller[i] + -Min1)]++;//trunc, round
		else 
			Histo[(int)ceil(DoubleBoxMiller[i] + Max1)]++;
	}

	for (int i = 0; i < N; i++){

		cout <<Histo[i]<<endl;
	}

	int elapsed_seconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "Duration Time (2 thread): " << elapsed_seconds << " microsec\n" << endl;
	
	for (int i = 0; i < N; i++){

		Histo[i] = 0;
	}

	chrono::time_point<chrono::system_clock> start2, end2;
	start2 = chrono::system_clock::now();

	thread tr21(&AlgBoxMuller, a, 0, 1000000, Max);
	tr21.join();

	end2 = chrono::system_clock::now();

	for (int i = 0; i < n; i++){

		if (Min1 > DoubleBoxMiller[i]) Min1 = DoubleBoxMiller[i];
		if (Max1 < DoubleBoxMiller[i]) Max1 = DoubleBoxMiller[i];
	}
	cout << Max1 << endl << Min1 << endl << endl;

	for (int i = 0; i < n; i++)
	{
		if (DoubleBoxMiller[i] < 0)
			Histo[(int)floor(DoubleBoxMiller[i] + -Min1)]++;//trunc, round
		else
			Histo[(int)ceil(DoubleBoxMiller[i] + Max1)]++;
	}
	for (int i = 0; i < N; i++){
		cout << Histo[i] << endl;
	}

	int elapsed_seconds2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
	cout << "Duration Time (1 thread): " << elapsed_seconds2 << " microsec\n" << endl;

	delete[] DoubleBoxMiller;

}

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
