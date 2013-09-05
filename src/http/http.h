#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>
#include <string>
#include <vector>
using namespace std;

const long CONTENT_MAX_LENGTH = 102400;     // 100KB

class HTTP
{
public:
	HTTP();
	~HTTP();
	static size_t writer(void * data, size_t size, size_t nmemb, void * userf);
	void setHeaders(vector<string> headers);
	void setVerbose();
	string GET(const char * uri);

private:
	CURL * m_curl;
	CURLcode m_errno;
	struct curl_slist * m_headers;
	static string m_content;
};

#endif
