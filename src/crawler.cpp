#include <iostream>
#include "crawler.h"

using namespace std;


Crawler::Crawler()
{

}

Crawler::~Crawler()
{

}

void Crawler::setUri(string uri)
{
	this->uri = uri;
}

void Crawler::setTransferCoding(bool tag, string fromCharSet, string toCharSet)
{
	this->isTransfer = tag;
	this->fromCharSet = fromCharSet;
	this->toCharSet = toCharSet;
}

void Crawler::setHeaders()
{

}

void Crawler::setVerbose()
{

}

void Crawler::start()
{

}

string Crawler::transferHtmlTag(string s)
{

}

string Crawler::getContent()
{
	return m_content;
}
