#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

//
//gcc -g -o a.out -I /usr/local/opt/openssl/include/ -L /usr/local/opt/openssl/lib/ -lcrypto md5.c

/**
 * brew install openssl  // optional if errors
 */

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

// printf("%s: %ld\n", argv[1], fibonacci(atoi(argv[1])));
// long fibonacci(int num)
// {
//         long n0 = 1;
//         long n1 = 1;
//         if (num == 0)
//                 return 0;
//         if (num == 1)
//                 return n0;
//         if (num == 2)
//                 return n1;
//         long tm;
//         for (int i = 3; i <= num; i++)
//         {
//                 tm = n0 + n1;
//                 n0 = n1;
//                 n1 = tm;
//         }

//         return tm;
// }

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

        printf("%s: %s, tv:%d millisecs\n", strMd5, numstr, (et-st)*1000 + (etu - stu)/1000 );

        return 0;
}

int main(int argc, char **argv)
{
        if (argc != 2)
        {
                printf("%s <num>\n", argv[0]);
                return -1;
        }

        run_md5_n_times_with_timer(atoi(argv[1]));

        return 0;
}
