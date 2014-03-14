#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstddef>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::bitset;
using std::vector;

int main()
{
	string str("110011000011");
	bitset<32> bitvec;
	bool is_set = bitvec.any();
	bool is_not_set = bitvec.none();
	bitset<32> bitvec1(str);
	bitset<32> bitvec2(str,3,5);
	size_t bits_set = bitvec1.count();
	size_t sz = bitvec2.size();

	cout << is_set << endl;
	cout << is_not_set << endl;
	cout << bits_set << endl;
	cout << sz << endl;
	for(int index = 0; index != 32; index +=2)
		bitvec[index] = 1;
	size_t sz1 = bitvec.count();
	cout << sz1 << endl;
	cout << "bitvec:" << bitvec << endl;
	unsigned long ulong = bitvec.to_ulong();
	cout << "ulong =" << ulong << endl;
	return 0;
}
