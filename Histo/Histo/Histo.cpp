// Histo.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include <random>
#include <ctime>
#include <chrono>
#include <mutex>
#include <thread>
using namespace std;

unsigned int *Glob;
mutex mutexGisto;
const int N = 1000000, n = 10;
int Min = 1000000, Max = 0;

void histo(int n,int it, int M, int len, int *m)
{
	unsigned int *histo = new unsigned int[n];
	for (int i = 0; i < n; i++)
	{
		histo[i] = 0;
	}

	for (int i = it; i < n; i++)
	{
		histo[m[i] / len]++;
	}

	mutexGisto.lock();
	for (int i = 0; i < M; i++)
	{
		histo[i]+=histo[i];
	}
	mutexGisto.unlock();
	delete[] histo;
}


int _tmain(int argc, _TCHAR* argv[])
{	
	Glob = new unsigned int[n];
	 int  *a = new  int[N];
	 for (int i = 0; i < n; i++) {
		 Glob[i] = 0;
	 }
	/*ofstream Fout("1.txt");
	for (int i = 0; i < N; i++)
	{
		a[i] = rand();
		Fout << a[i] << endl;
		//cout << a[i] << endl;
	}*/
	ifstream Fin("1.txt");
	for (int i = 0; i < N; i++)
	{
		Fin >> a[i];
		//cout << a[i] << endl;
	}
	for (int i = 0; i < N; i++)
	{
		if (Min > a[i]) Min = a[i];
		if (Max < a[i]) Max = a[i];
	}
	int length = Max / n + 1;

	cout << "Minimum = " << Min << endl << "Maximum = " << Max << endl << "Length = " << length << endl << endl;

	//chrono::time_point<chrono::system_clock> t1, t2;
	//t1 = chrono::system_clock::now();

	////for (int i = 0; i < N; i++)
	////{
	////	Glob[a[i]/length]++;
	////}
	//thread tr1(&histom, 500000, 0, 10, length,  a);
	//thread tr2(&histom, 1000000, 500000, 10, length,  a);
	//tr1.join();
	//tr2.join();

	//cout << "Histograma:" << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	cout << Glob[i] << endl;
	//}

	//t1 = chrono::system_clock::now();
	//int elapsed_seconds = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
	//
	//cout << "Duration Time: " << elapsed_seconds << " microsec\n";

	chrono::time_point<chrono::system_clock> t1, t2;
	t1 = chrono::system_clock::now();
	
	thread tr1(&histo, 250000, 0, 10, length, a);
	thread tr2(&histo, 500000, 250000, 10, length, a);
	thread tr3(&histo, 750000, 500000, 10, length, a);
	thread tr4(&histo, 1000000, 750000, 10, length, a);
	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();
	cout << "Histograma:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << Glob[i] << endl;
	}

	t2 = chrono::system_clock::now();
	int elapsed_seconds = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

	cout << "Duration Time: " << elapsed_seconds << " microsec\n";
	
	delete[] a;
	return 0;
}

