#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <bitset>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::bitset;
using std::vector;


int main()
{
	const size_t array_size = 10;
	int a[] = {0,1,2,3,4,5,6,7,8,9};
	int b[array_size];
	for(size_t ix =0; ix != array_size;++ix)
	{
		b[ix] = a[ix];
		cout << b[ix] << endl;
	}
	int s;
	vector<int> vec;
	vector<int>::size_type ix,ip;
	for(ix = 0;ix != 10;++ix)
	{
		cin >> s;
		vec.push_back(s);
	}

	vector<int> vec1(10);
	for(ip = 0;ip != vec1.size();++ip)
	{
		vec1[ip] = vec[ip];
	}

	vector<int>::iterator iter;

	for(iter = vec1.begin();iter != vec1.end();++iter)
		cout << *iter << endl;
		
	return 0;

}
