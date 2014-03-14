#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string s1;
//	while(cin >> s1)
//		cout << s1 << endl;
    while(getline(cin,s1))
		cout << s1 << endl;
	return 0;
}
