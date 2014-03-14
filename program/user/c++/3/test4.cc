#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string st("the expense of spirit\n");
	string::size_type size;
	size = st.size();
	cout << size << endl;
	cout << "the size of" << st << "is" << st.size() << endl;
	if(st.empty())
		cout << "empty" << endl;

	return 0;
}

