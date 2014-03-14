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
    for(vector<int>::const_iterator iter = text.begin(); iter != text.end();++iter)
	{
		cout << *iter << endl;
	}
	if(text.size()%2 != 0)
	{
    	cout << "the last number no sum" << endl;
		cout << text[text.size()-1] << endl;
	}
	vector<int>::iterator mid = text.begin() + text.size()/2; 
	cout << *mid << endl;
	return 0;

}
