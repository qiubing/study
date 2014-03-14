#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string s1;
	cin >> s1;
	cout << s1 << endl;
	string s2(s1);
	string s3("world");
	string s4(9,'k');
	cout << s1 << s2 << s3 << s4 << endl;
	return 0;
}
