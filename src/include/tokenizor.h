#include <iostream>
#include <vector>

using namespace std;

class Tokenizor
{
public:
	static vector<string> split(string s, const string& seperator)
	{
		vector<string> v;
		int pos=0;
		while(true) 
		{
			pos = s.find(seperator, 0);
			if (pos == string::npos)
			{
				if (!s.empty())
					v.push_back(s);
				break;
			}
			if (pos != 0)
				v.push_back(s.substr(0, pos));
			s = s.substr(pos + seperator.length(), s.length());
		}

		return v;
	}
};
