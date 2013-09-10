#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <sstream>

using namespace std;

int main()
{
    int sock;
    int recbytes;
    int sin_size;
    char buffer[102400] = {0};   
    struct sockaddr_in s_add,c_add;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock)
    {
        printf("socket fail ! \r\n");
        close(sock);
        exit(-1);
    }
    printf("socket ok !\r\n");

    /*
    int errno;
    if((errno = fcntl(sock, F_GETFL, 0)) < 0) 
    {
        cout << "fcntl get fd state failed" << endl;
        close(sock);
        exit(-1);                           
    }
    if(fcntl(sock, F_SETFL, errno | O_NONBLOCK) < 0) 
    {
        cout << "fcntl set fd state failed" << endl;
        close(sock);
        exit(-1);
    }*/

    bzero(&s_add, sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = inet_addr("123.127.134.62");
    s_add.sin_port = htons(80);

    if(-1 == connect(sock, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("connect fail !\r\n");
        close(sock);
        exit(-1);
    }
    printf("connect ok !\r\n");

    stringstream httpHeader;
    httpHeader << "GET /board/Job HTTP/1.1\r\n"
               << "Host: bbs.byr.cn\r\n"
               << "Cache-Control: max-age=0\r\n"
               << "Accept: */*\r\n"
               << "Accept-Language: zh-CN,zh\r\n"
               << "Connection: keep-alive\r\n"
               << "X-Requested-With: XMLHttpRequestr\r\n"
               << "Referer: http://bbs.byr.cn/\r\n"
               << "User-Agent: hongyuxuan\r\n"
               << "Cookie:nforum[UTMPUSERID]=hongyuxuan; nforum[PASSWORD]=yQaArXCzPA8OlAjUHBGfzA%3D%3D; nforum[BMODE]=2; nforum[UTMPKEY]=10874084; nforum[UTMPNUM]=2068; nforum[XWJOKE]=hoho; __utma=217424581.1983493688.1375753346.1378795554.1378805929.50; __utmb=217424581.7.10.1378805929; __utmc=217424581; __utmz=217424581.1375753346.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); left-index=000100000"
               << "\r\n";

    if(send(sock, httpHeader.str().c_str(), httpHeader.str().length(), 0) < 0)
    {
        cout << "send message to server failed" << endl;
        close(sock);
        exit(-1);
    }

    if(-1 == (recbytes = read(sock, buffer, 10240)))
    {
        printf("read data fail !\r\n");
        close(sock);
        exit(-1);
    }
    buffer[recbytes-1]='\0';
    cout << buffer << endl;
    close(sock);
}
