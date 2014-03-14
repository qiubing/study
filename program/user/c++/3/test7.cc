#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string s1,s2;
	cin >> s1 >> s2;
	if(s1 == s2)
		cout << "equal" << endl;
	else if(s1 > s2)
		cout << "s1 big than s2" << endl;
	else
		cout << "s2 big than s2" << endl;
	 

	return 0;
}

