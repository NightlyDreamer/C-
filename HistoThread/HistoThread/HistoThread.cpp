#include <iostream>
#include <valarray>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;

class Matrix {
	valarray<int> vect;
	valarray<int> Matr;
	valarray<int> ArrayRes;
	int str;
	int st;
	int per;

public:
	Matrix(string p, int strok, int stolb) : vect(strok), Matr(strok * stolb), ArrayRes(stolb) {

		str = strok;
		st = stolb;
		ifstream f(p);
		for (int i = 0; i < strok * stolb; i++) {
			f >> Matr[i];
		}
		for (int i = 0; i < strok; i++) {
			f >> vect[i];
		}
	}

	void multiply(int rows) {
		ArrayRes[rows] = (Matr[slice(st*rows, st, 1)] * vect).sum();
	}
	void print() {
		for (int i = 0; i < st; i++) {
			cout << ArrayRes[i] << " ";
		}
	}
};




int main() {
	string s = "Matrix.txt";
	Matrix m(s, 3, 4);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	thread tr1([&m]() { m.multiply(0); });
	thread tr2([&m]() { m.multiply(2); });
	thread tr3([&m]() { m.multiply(3); });
	tr1.join();
	tr2.join();
	tr3.join();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	m.print();
	cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count();


	//system("pause");
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
