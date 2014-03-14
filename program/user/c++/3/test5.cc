#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string s1 = "hello";
	string s2 = "world";
	string s3 = s1 + "," + s2 + "\n";
	cout << s3 << endl;
	string::size_type ix;
	for(ix = 0;ix != s3.size();++ix)
	 s3[ix] = '*';
	cout << s3 << endl;
	string s4 = s1+"hello" + ",";
	cout << s4 << endl;

	return 0;
}

