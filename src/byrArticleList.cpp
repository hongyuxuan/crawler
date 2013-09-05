#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include "byrArticleList.h"
#include "include/iconv.h"
#include "include/tokenizor.h"

using namespace std;

ByrArticleList::ByrArticleList()
{
	p = 1;
	isTransfer = false;
	handler = new HTTP();
}

ByrArticleList::ByrArticleList(string uri)
{
	this->uri = uri;
	p = 1;
	isTransfer = false;
	handler = new HTTP();
}

ByrArticleList::~ByrArticleList()
{
	delete handler;
}

void ByrArticleList::setPageNumber(int p)
{
	this->p = p;
}

void ByrArticleList::setHeaders()
{
	vector<string> headers;
	headers.push_back("Accept:*/*");
	headers.push_back("Accept-Language:zh-CN,zh");
	headers.push_back("Connection:keep-alive");
	headers.push_back("Cookie:nforum[BMODE]=2; nforum[XWJOKE]=hoho; nforum[UTMPUSERID]=guest; nforum[UTMPKEY]=4289383; nforum[UTMPNUM]=4483; __utma=217424581.1983493688.1375753346.1377498826.1377692026.28; __utmb=217424581.5.10.1377692026; __utmc=217424581; __utmz=217424581.1375753346.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); left-index=000100000");
	headers.push_back("Host:bbs.byr.cn");
	headers.push_back("Referer:http://bbs.byr.cn/");
	headers.push_back("User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.95 Safari/537.36");
	headers.push_back("X-Requested-With:XMLHttpRequest");
	
	handler->setHeaders(headers);
}

void ByrArticleList::setVerbose()
{
	handler->setVerbose();
}

void ByrArticleList::start()
{
	articleList.clear();
	for(int i=1; i<=p; i++)
	{
		string location = uri + "?p=" + boost::lexical_cast<string>(i);
		string response = handler->GET(location.c_str());
		if (!isTransfer)
		{
			m_content = response;
		}
		else
		{
			int outlen = response.length() * 2;
			char * outbuf;
			outbuf = (char *)malloc(outlen);
			memset(outbuf, 0, outlen);
			Iconv icv = Iconv(fromCharSet, toCharSet);
			icv.convert(const_cast<char *>(response.c_str()), response.length(), outbuf, outlen);
			m_content = outbuf;
			free(outbuf);
		}
		setArticleList();
	}
}

void ByrArticleList::setArticleList()
{
	boost::smatch result;
	boost::regex pattern;
	pattern = "<div class=\"b-content\">(.+)</div><div class=\"t-pre-bottom\">";
	if(boost::regex_search(m_content, result, pattern))
	{
		string mainbody = result[1];
		pattern = "<tbody>(.+)</tbody>";
		if(boost::regex_search(mainbody, result, pattern))
		{
			string list = result[1];
			pattern = "(<tr>)|(</tr>)|(<tr class=\"top\">)";
			string s = boost::regex_replace(list, pattern, "<|>");
			
			vector<string> v = Tokenizor::split(s, "<|>");
			vector<string>::iterator iter;
			for(iter=v.begin(); iter!=v.end(); iter++)
			{
				Article article;
				pattern = "<a href=\"([^<]+)\">([^<]+)</a>";
				if (boost::regex_search(*iter, result, pattern))
				{
					article.setLink("http://bbs.byr.cn" + result[1]);
					article.setTitle(transferHtmlTag(result[2]));
				}
			
				pattern = "<td class=\"title_10\">([^<]+)</td>";
				if (boost::regex_search(*iter, result, pattern))
				{
					article.setTime(transferHtmlTag(result[1]));
				}

				articleList.push_back(article);
			}
		}
	}
}

string ByrArticleList::transferHtmlTag(string s)
{
	boost::regex pattern("&#43;");
	s = boost::regex_replace(s, pattern, "+");

	pattern = "&emsp;";
	s = boost::regex_replace(s, pattern, "  ");

	pattern = "&#45;";
	s = boost::regex_replace(s, pattern, "-");

	pattern = "&#40;";
	s = boost::regex_replace(s, pattern, "(");
	
	pattern = "&#41;";
	s = boost::regex_replace(s, pattern, ")");

	pattern = "&quot;";
	s = boost::regex_replace(s, pattern, "\"");

	pattern = "&amp;";
	s = boost::regex_replace(s, pattern, "&");

	pattern = "&lt;";
	s = boost::regex_replace(s, pattern, "<");

	pattern = "&gt;";
	s = boost::regex_replace(s, pattern, ">");

	return s;
}

vector<Article> ByrArticleList::getArticleList()
{
	return articleList; 
}

void ByrArticleList::showArticleList()
{
	vector<Article>::iterator iter;
	for(iter=articleList.begin(); iter != articleList.end(); iter++)
	{
		cout << (*iter).toString() << endl; 
	}
}
