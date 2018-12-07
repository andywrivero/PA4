#include <iostream>

using std::cin;
using std::cout;

using std::endl;

int main ()
{
	int a, b, c, d, e, f, 
		g, h, i, t0, t1, 
		t2, t3, t4, t5;

	cout << "Enter input a : "; cin >> a;
	cout << "Enter input b : "; cin >> b;
	cout << "Enter input c : "; cin >> c;
	cout << "Enter input d : "; cin >> d;
	cout << "Enter input e : "; cin >> e;
	cout << "Enter input f : "; cin >> f;
	cout << "Enter input g : "; cin >> g;
	cout << "Enter input h : "; cin >> h;

	t0 = a * b;
	t1 = c * d;
	t2 = e * f;
	t3 = t0 * t1;
	t4 = g * t2;
	t5 = t3 - h;
	i = t5 - t4;

	cout << "i = " << i << endl;

	return 0;
}