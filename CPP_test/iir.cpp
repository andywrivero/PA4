#include <iostream>

using std::cin;
using std::cout;

using std::endl;

int main ()
{
	int a1;
	int y1;
	int a2;
	int y2;
	int b0;
	int x0;
	int b1;
	int x1;
	int b2;
	int x2;
	int yout;
	int r1;
	int r2;
	int r3;
	int r4;
	int r5;
	int r6;
	int r7;
	int r8;

	cout << "Enter input a1 : "; cin >> a1;
	cout << "Enter input y1 : "; cin >> y1;
	cout << "Enter input a2 : "; cin >> a2;
	cout << "Enter input y2 : "; cin >> y2;
	cout << "Enter input b0 : "; cin >> b0;
	cout << "Enter input x0 : "; cin >> x0;
	cout << "Enter input b1 : "; cin >> b1;
	cout << "Enter input x1 : "; cin >> x1;
	cout << "Enter input b2 : "; cin >> b2;
	cout << "Enter input x2 : "; cin >> x2;

	r1 = a1 * y1;
	r2 = a2 * y2;
	r3 = b0 * x0;
	r4 = b1 * x1;
	r5 = b2 * x2;
	r6 = r1 + r2;
	r7 = r3 + r4;
	r8 = r7 + r5;
	yout = r6 + r8;

	cout << "yout = " << yout << endl;

	return 0;
}