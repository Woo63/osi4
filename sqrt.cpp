#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <math.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define SQRTSEM "/sqrtsem"
#define PORT 6969
#define BUFSIZE 32
float num;
int bytes_read, total = 0;
int sock, sock1;
struct sockaddr_in addr, addr1;

int main() {
 sem_t *sqrts = sem_open(SQRTSEM, 0);
 sock = socket(AF_INET, SOCK_DGRAM, 0); //создаём сокеты
 sock1 = socket(AF_INET, SOCK_DGRAM, 0);
 addr.sin_family = AF_INET;
 addr.sin_port = htons(PORT);
 addr.sin_addr.s_addr = inet_addr("127.0.0.3");
 bind(sock, (struct sockaddr *)&addr, sizeof(addr));
 addr1.sin_family = AF_INET;
 addr1.sin_port = htons(PORT);
 addr1.sin_addr.s_addr = inet_addr("127.0.0.5");
 connect(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
 while(1) {
   sem_wait(sqrts);
   std::cout << "WAITING FOR DATA...\n";
   bytes_read = recvfrom(sock, &num, sizeof(float), 0, NULL, NULL);
   std::cout << "Received " << num << std::endl;
   float res = sqrt(num);
   fflush(stdout);
   send(sock1, &res, sizeof(res), 0);
 }
 return 0;
}
