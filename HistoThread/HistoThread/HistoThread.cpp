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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
