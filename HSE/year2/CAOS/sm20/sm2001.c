//https://github.com/freepvps/hseos/blob/master/src/sockets/example/main.c
//Читал конспекты
//https://github.com/dbeliakov/hse-os-2018/blob/master/seminars/20/code/host/main.c#L17
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


enum { SZ = 1000 };

int main() {
    char host[SZ];
    char service[SZ];
    struct addrinfo hints, * temp;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    while (scanf("%s%s", host, service) > 0) {
        int stat;
        if ((stat = getaddrinfo(host, service, &hints, &temp)) != 0) {
            printf("%s\n", gai_strerror(stat));
            continue;
        }

        struct sockaddr_in * ptr_in = (struct sockaddr_in *)temp->ai_addr;
        struct addrinfo * next = temp->ai_next;

        while (next != NULL) {
            if (ntohl(ptr_in->sin_addr.s_addr) > 
            ntohl(((struct sockaddr_in *)(next->ai_addr))->sin_addr.s_addr)) {
                ptr_in = (struct sockaddr_in *)next->ai_addr;
            }
            next = next->ai_next;
        }
        printf("%s:%d\n", inet_ntoa(ptr_in->sin_addr), ntohs(ptr_in->sin_port));
    };
    // freeaddrinfo(&hints);
    freeaddrinfo(temp);
    return 0;
}