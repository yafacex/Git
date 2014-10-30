//
//  main.cpp
//  httpClient
//
//  Created by yafacex on 14-10-30.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(55741);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    
    if (result == -1)
    {
        printf("connect failded");
        perror("oops: client1");
        _exit(1);
    }
    printf("try send\n");
    char buff[15] = "wo shi sha bi\n";
//    send(sockfd, buff, 14, 0);
    write(sockfd, &buff, 15);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    _exit(0);
    return 1;
}

