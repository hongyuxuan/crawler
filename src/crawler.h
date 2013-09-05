#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <vector>
#include <boost/regex.hpp>

#include "http/http.h"

using namespace std;

class Crawler
{
public:
	Crawler();
	~Crawler();

	void setUri(string uri);
	void setTransferCoding(bool tag, string fromCharSet, string toCharSet);
	string getContent();

	virtual void setHeaders();
	virtual void setVerbose();
	virtual void start();
	virtual string transferHtmlTag(string s);

protected:
	string uri;
	HTTP * handler;
	bool isTransfer;
	string fromCharSet;
	string toCharSet;
	string m_content;
};

#endif
