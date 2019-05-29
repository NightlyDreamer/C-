// 1LabReb.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <mutex>
#include <thread>
using namespace std;
using namespace chrono;

unsigned int *Histo;
const int N = 10;
mutex MutexH;
int Maximum = 0;

void Histo_Hulk(int M, int len, int min, int max, int *p) {
	unsigned int *local_histo = new unsigned int[max];

	for (int i = 0; i < max; i++){
		local_histo[i] = 0;
	}

	for (int i = min; i < max; i++){
		local_histo[p[i] / len]++;
	}

	MutexH.lock();
	for (int i = 0; i < M; i++){
		Histo[i] += local_histo[i];
	}
	MutexH.unlock();

	delete[] local_histo;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	const int S = 1000000;
	//int Maximum = 0;
	int * billion = new  int [S];
	Histo = new unsigned int[N];

	for (int i = 0; i < N; i++){
		Histo[i] = 0;
	}

	for (int i = 0; i < S; i++){
		billion[i] = 0;
	}

	/*ofstream fout("B.txt");	
	for (int i = 0; i < S; i++) {
		billion[i] = rand() % 500;
		fout << billion[i] << endl;
	}*/

	ifstream fin("B.txt");
	for (int i = 0; i < S; i++){
		fin >> billion[i];
		if (Maximum < billion[i])
		{
			Maximum = billion[i];
		}
	}
	cout << "Maximum: " << Maximum << endl;

	int Length = Maximum / N + 1;
	cout << "Length: " << Length << endl << endl;

	time_point<system_clock> start, end;
	start = system_clock::now();

	for (int i = 0; i < S; i++){
		Histo[billion[i] / Length]++;
	}

	end = system_clock::now();
	cout << "Histogramma:"<<endl;

	for (int i = 0; i < N; i++){
		cout << Histo[i] << endl;
	}
	
	int elapsed_seconds = duration_cast<microseconds>(end - start).count();
	cout << "Duration Time (without thread): " << elapsed_seconds << " microsec.\n\n";

	for (int i = 0; i < N; i++) {
		Histo[i] = 0;
	}
	
	time_point<system_clock> start1, end1;
	start1 = system_clock::now();

	thread tr1 (&Histo_Hulk, 10, Length, 0, 1000000, billion);
	tr1.join();

	end1 = system_clock::now();
	cout << "Histogramma 1 thread:" << endl;
	for (int i = 0; i < N; i++) {
		cout << Histo[i] << endl;
	}

	int elapsed_seconds1 = duration_cast<microseconds>(end1 - start1).count();
	cout << "Duration Time (1 thread): " << elapsed_seconds1 << " microsec.\n\n";

	for (int i = 0; i < N; i++) {
		Histo[i] = 0;
	}

	time_point<system_clock> start2, end2;
	start2 = system_clock::now();

	thread tr01(&Histo_Hulk, 10, Length, 0, 500000, billion);
	thread tr02(&Histo_Hulk, 10, Length, 500000, 1000000, billion);
	tr01.join();
	tr02.join();

	end2 = system_clock::now();
	cout << "Histogramma 2 thread:" << endl;
	for (int i = 0; i < N; i++) {
		cout << Histo[i] << endl;
	}

	int elapsed_seconds2 = duration_cast<microseconds>(end2 - start2).count();
	cout << "Duration Time (2 thread): " << elapsed_seconds2 << " microsec.\n\n";

	for (int i = 0; i < N; i++) {
		Histo[i] = 0;
	}

	time_point<system_clock> start4, end4;
	start4 = system_clock::now();

	thread tr11(&Histo_Hulk, 10, Length, 0, 250000, billion);
	thread tr21(&Histo_Hulk, 10, Length, 250000, 500000, billion);
	thread tr31(&Histo_Hulk, 10, Length, 500000, 750000, billion);
	thread tr41(&Histo_Hulk, 10, Length, 750000, 1000000, billion);
	tr11.join();
	tr21.join();
	tr31.join();
	tr41.join();

	end4 = system_clock::now();
	cout << "Histogramma 4 thread:" << endl;

	for (int i = 0; i < N; i++) {
		cout << Histo[i] << endl;
	}

	int elapsed_seconds4 = duration_cast<microseconds>(end4 - start4).count();
	cout << "Duration Time (4 thread): " << elapsed_seconds4 << " microsec.\n\n";

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
