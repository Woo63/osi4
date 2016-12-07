#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#define RAZSEM "/razsem"
#define PORT 6969
#define BUFSIZE 32
float num1, num2;
int bytes_read, total = 0;
int sock, sock1;
volatile int flag = 0;
struct sockaddr_in addr, addr1;

int main() {
  sem_t *raz = sem_open(RAZSEM, 0);
 sock = socket(AF_INET, SOCK_DGRAM, 0);
 sock1 = socket(AF_INET, SOCK_DGRAM, 0);
 addr.sin_family = AF_INET;
 addr.sin_port = htons(PORT);
 addr.sin_addr.s_addr = inet_addr("127.0.0.2");
 bind(sock, (struct sockaddr *)&addr, sizeof(addr));
 addr1.sin_family = AF_INET;
 addr1.sin_port = htons(PORT);
 addr1.sin_addr.s_addr = inet_addr("127.0.0.5");
 connect(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
 while(1) {
   sem_wait(raz);
   std::cout << "WAITING FOR SIGNAL in raz thread" << std::endl;
   std::cout << "WAITING FOR FIRST NUM...\n";
   bytes_read = recvfrom(sock, &num1, sizeof(float), 0, NULL, NULL);
   total = total + bytes_read;
   std::cout << "Received " << num1 << std::endl;
   std::cout << "WAITING FOR SECOND NUM...\n";
   bytes_read = recvfrom(sock, &num2, sizeof(float), 0, NULL, NULL);
   std::cout << "Received " << num2 << std::endl;
   total = total + bytes_read;
   float res = num1-num2;
   std::cout << "RAZ: " << res << std::endl;
   fflush(stdout);
   std::cout << "Sending data back...\n";
   send(sock1, &res, sizeof(res), 0);
 }
 return 0;
}
