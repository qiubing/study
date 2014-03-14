#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;

int main()
{
	string word;
	vector<string> text;
	vector<string>::size_type size,ix;
	while(cin >> word)
		text.push_back(word);
	size = text.size();
	for(ix = 0; ix != size; ++ix)
		cout << text[ix] << endl;
	cout << size << endl;

	

	return 0;

}
