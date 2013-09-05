#include <iostream>
#include <vector>
#include "byrArticleList.h"

using namespace std;


int main()
{
	ByrArticleList * crawler = new ByrArticleList();
	crawler->setTransferCoding(true, "gbk", "utf-8");
	crawler->setHeaders();
/*
	crawler->setUri("http://bbs.byr.cn/board/Job");
	crawler->setPageNumber(2);
	crawler->start();
	crawler->showArticleList();

	cout << endl;
*/

	crawler->setUri("http://bbs.byr.cn/board/Friends");
	crawler->setPageNumber(2);
	crawler->start();
	vector<Article> v = crawler->getArticleList();
	vector<Article>::iterator iter;
	for(iter = v.begin(); iter != v.end(); iter++)
	{
		if ((*iter).getTitle().find("王道") != string::npos)
		{
			cout << (*iter).toString() << endl;
		}
	}

	delete crawler;
}
