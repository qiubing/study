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
	int x;
	int sum = 0;
	vector<int> text;
	while(cin >> x)
		text.push_back(x);
	vector<int>::size_type ix;
//	for(ix = 0;ix < text.size();ix=ix+2)
//	{
//		sum = text[ix]+text[ix+1];
//		cout << sum << endl;

//	}
    for(ix = 0;ix != text.size();++ix)
	{
		sum = text[ix] + text[text.size()-ix-1];
		cout << sum << endl;
	}
	if(text.size()%2 != 0)
	{
    	cout << "the last number no sum" << endl;
		cout << text[text.size()-1] << endl;
	}
	return 0;

}
