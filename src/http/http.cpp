#include <iostream>
#include "http.h"

using namespace std;

HTTP::HTTP()
{
	m_curl = NULL;
	m_headers = NULL;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_curl = curl_easy_init();
    if (m_curl == NULL)
    {
        cout << "Failed to create CURL connection" << endl;
		_exit(0);
    }
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &writer);
//	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &content);
}

size_t HTTP::writer(void * data, size_t size, size_t nmemb, void * userf)
{
    long sizes = size * nmemb;
	string temp((char *)data, sizes);
	m_content += temp;
    return sizes;
}

void HTTP::setHeaders(vector<string> headers)
{
	for(int i=0; i<headers.size(); i++)
	{
		m_headers = curl_slist_append(m_headers, headers[i].c_str());
	}
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
}

void HTTP::setVerbose()
{
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
}

string HTTP::GET(const char * uri)
{
	m_content.erase(); 
	curl_easy_setopt(m_curl, CURLOPT_URL, uri); 
	curl_easy_perform(m_curl);
	return m_content;
}

HTTP::~HTTP()
{
	if (m_headers != NULL)
	{
		curl_slist_free_all(m_headers);
	}
	curl_easy_cleanup(m_curl);
	curl_global_cleanup();
}

string HTTP::m_content = "";

