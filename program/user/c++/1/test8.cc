#include <iostream>

int main()
{
	std::cout << "Enter two number:" << std::endl;
	int v1,v2;
	std::cin >> v1 >> v2;
	int lower,upper;
	if(v1 <= v2)
	{
		lower = v1;
		upper = v2;
	}else
	{
		lower = v2;
		upper = v1;
	}

	int sum = 0;
	int val;
	for(val = lower; val <= upper;++val)
		sum += val;

	std::cout << "sum of " << lower << "to" << upper << "is " << sum << std::endl;
	return 0;
}
