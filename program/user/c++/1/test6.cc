#include <iostream>

int main()
{
	int val;
	int sum = 0;
	/*for(val = 50;val <= 100;++val)
		sum += val;
	*/
	val = 50;
	while(val <= 100)
	{
		sum += val;
		++val;
	}
	std::cout << "sum of 50 to 100 is "<< sum << std::endl;
	return 0;
}
