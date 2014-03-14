#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string s1 = "Hello";
	string s2 = "World!!!";
	string s3 = s1 + "," + s2 + "\n";
	string::size_type ix,ip;
	ip = 0;
	for(ix = 0;ix != s3.size();++ix){
		s3[ix] = tolower(s3[ix]);
		if(ispunct(s3[ix]))
			++ip;}
	cout << s3 << endl;
	cout << ip << endl;
	 

	return 0;
}

