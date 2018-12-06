#include <iostream>

using std::cin;
using std::cout;

using std::endl;

int main ()
{
	int inp;
	int svin2;
	int svin13;
	int svin18;
	int svin26;
	int svin33;
	int svin38;
	int svin39;
	int TWO;
	int svout2;
	int svout13;
	int svout18;
	int svout26;
	int svout33;
	int svout38;
	int svout39;
	int outpi;
	int var3;
	int var32;
	int var12;
	int var20;
	int var25;
	int var21;
	int var24;
	int var19;
	int var27;
	int var11;
	int var22;
	int var29;
	int var9;
	int var30;
	int var8;
	int var31;
	int var7;
	int var10;
	int var28;
	int var41;
	int var6;
	int var15;
	int var35;
	int var4;
	int var16;
	int var36;

	cout << "Enter input inp : "; cin >> inp;
	cout << "Enter input svin2 : "; cin >> svin2;
	cout << "Enter input svin13 : "; cin >> svin13;
	cout << "Enter input svin18 : "; cin >> svin18;
	cout << "Enter input svin26 : "; cin >> svin26;
	cout << "Enter input svin33 : "; cin >> svin33;
	cout << "Enter input svin38 : "; cin >> svin38;
	cout << "Enter input svin39 : "; cin >> svin39;
	cout << "Enter input TWO : "; cin >> TWO;

	var3 = inp + svin2;
	var32 = svin33 + svin39;
	var12 = var3 + svin13;
	var20 = var12 + svin26;
	var25 = var20 + var32;
	var21 = var25 * TWO;
	var24 = var25 * TWO;
	var19 = var12 + var21;
	var27 = var24 + var32;
	var11 = var12 + var19;
	var22 = var19 + var25;
	var29 = var27 + var32;
	var9 = var11 * TWO;
	svout26 = var22 + var27;
	var30 = var29 * TWO;
	var8 = var3 + var9;
	var31 = var30 + svin39;
	var7 = var3 + var8;
	var10 = var8 + var19;
	var28 = var27 + var31;
	var41 = var31 + svin39;
	var6 = var7 * TWO;
	var15 = var10 + svin18;
	var35 = svin38 + var28;
	outpi = var41 * TWO;
	var4 = inp + var6;
	var16 = var15 * TWO;
	var36 = var35 * TWO;
	svout39 = var31 + outpi;
	svout2 = var4 + var8;
	svout18 = var16 + svin18;
	svout38 = svin38 + var36;
	svout13 = var15 + svout18;
	svout33 = svout38 + var35;

	cout << "svout2 = " << svout2 << endl;
	cout << "svout13 = " << svout13 << endl;
	cout << "svout18 = " << svout18 << endl;
	cout << "svout26 = " << svout26 << endl;
	cout << "svout33 = " << svout33 << endl;
	cout << "svout38 = " << svout38 << endl;
	cout << "svout39 = " << svout39 << endl;

	return 0;
}