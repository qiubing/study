#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::deque;

int main()
{
	string word;
	vector<string> text;
	deque<string> text1;
	while(cin >> word)
	{
		text.push_back(word);
		text1.push_front(word);
	}

	for(vector<string>::iterator iter = text.begin(); iter != text.end();++iter)
		cout << *iter << endl;
	cout << text1.front()<< endl;
	cout << text1.back()<< endl;
	cout << text1[0] << endl;
	cout << text1.at(0) << endl;
	for(deque<int>::size_type ix = 0; ix != text1.size(); ++ix)
		cout << text1[ix] << endl;

}
