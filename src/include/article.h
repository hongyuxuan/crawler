#include <iostream>

using namespace std;

class Article
{
public:
	Article(){};
	
	void setTitle(string title)
	{
		this->title = title;
	}
	
	string getTitle()
	{
		return title;
	}

	void setTime(string time)
	{
		this->time = time;
	}

	string getTime()
	{
		return time;
	}

	void setLink(string link)
	{
		this->link = link;
	}

	string getLink()
	{
		return link;
	}

	string toString()
	{
		return time + " [" + link + "] " + title;
	}

private:
	string time;
	string title;
	string link;
};

