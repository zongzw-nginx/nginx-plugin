#include "fcgi_stdio.h"
#include <stdlib.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define MD5_STRING_LENGTH MD5_DIGEST_LENGTH * 2

int md5(char *data, char *output)
{
        unsigned char md[MD5_DIGEST_LENGTH];
        memset(md, 0, MD5_DIGEST_LENGTH);

        MD5_CTX c;

        if (!MD5_Init(&c))
        {
                printf("MD5_Init failed\n");
                return -1;
        }

        MD5_Update(&c, data, strlen(data));
        MD5_Final(md, &c);

        for (int nIndex = 0; nIndex < MD5_DIGEST_LENGTH; nIndex++)
        {
                sprintf(output + nIndex * 2, "%02x", md[nIndex]);
        }

        return 0;
}

int run_md5_n_times_with_timer(int num)
{
        int st, et, stu, etu; 
        struct timeval tv;

        gettimeofday(&tv, NULL);
        st = tv.tv_sec;
        stu = tv.tv_usec;

        char strMd5[MD5_STRING_LENGTH + 1];
        memset(strMd5, 0, MD5_STRING_LENGTH + 1);

        char numstr[16];
        int i = 0;
        while (i < num)
        {
                sprintf(numstr, "%d", i);
                md5(numstr, strMd5);
                i++;
        }

        gettimeofday(&tv, NULL);
        et = tv.tv_sec;
        etu = tv.tv_usec;

        printf("Content-type: text/html\r\n"
            "\r\n"
            "%s: %s, tv:%d millisecs", strMd5, numstr, (et-st)*1000 + (etu - stu)/1000 );

        return 0;
}

int main(void)
{

    while (FCGI_Accept() >= 0) {
        int num = atoi(getenv("MYNUM"));
        run_md5_n_times_with_timer(num);
    }
        // printf("Content-type: text/html\r\n"
        // "\r\n"
        // "<title>FastCGI Hello!</title>"
        // "<h1>FastCGI Hello!</h1>"
        // "Request number %d running on host <i>%s</i> <i>%s</i>\n",
        // ++count, getenv("SERVER_NAME"), getenv("MYNUM"));

    return 0;
}
