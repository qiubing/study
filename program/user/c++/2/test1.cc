#include <iostream>

int main()
{
	int v1,v2;
	std::cout << "enter two number; base first,exponent next :" << std::endl;
	std::cin >> v1 >> v2;
	int result = 1;
	int power;
	for(power = 0; power != v2; ++power)
		result *= v1;
	std::cout << "result is " << result << std::endl;
	return 0;
}
