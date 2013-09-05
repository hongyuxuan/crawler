#include "crawler.h"
#include "include/article.h"

class ByrArticleList : public Crawler
{
public:
	ByrArticleList();
	ByrArticleList(string uri);
	~ByrArticleList();
	
	// override functions
	void setHeaders();
	void setVerbose();
	void start();
	string transferHtmlTag(string s);
	
	// self functions
	void setPageNumber(int p);
	void setArticleList();
	vector<Article> getArticleList();
	void showArticleList();

private:
	vector<Article> articleList;
	int p;
};
