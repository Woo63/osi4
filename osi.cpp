#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#define PROIZSEM "/proizsem" 
#define RAZSEM "/razsem"
#define SQRTSEM "/sqrtsem"
#define DELSEM "/delsem"
#define PORT 6969 //порт для сокета
#define PROIZIP "127.0.0.1" //айпи для сокетов
#define RAZIP "127.0.0.2"
#define SQRTIP "127.0.0.3"
#define DELIP "127.0.0.4"
#define MYSOCK "127.0.0.5"
#define BUFSIZE 16 // размер буфера сокета
int proizsock, razsock, sqrtsock, delsock, mysock; //сокеты
char buf[BUFSIZE]; //буффер
struct sockaddr_in addr1,addr2,addr3,addr4; //структуры адресов сокетов
int bytes_read, total = 0; //количество прочитаных из сокета байтов и общее число прочитаных байтов
pid_t p1, p2, p3, p4; 
using namespace std; 
int main() {
  sem_t *sqrts = sem_open(SQRTSEM, O_CREAT, 0644, 0); 
  sem_t *raz = sem_open(RAZSEM, O_CREAT, 0644, 0);
  sem_t *proiz = sem_open(PROIZSEM, O_CREAT, 0644, 0);
  sem_t *del = sem_open(DELSEM, O_CREAT, 0644, 0);
  p1=fork(); 
  p2=fork();
  p3=fork();
  p4=fork();
  if (p1 == 0) // если первый дочерний процесс то в нём запускается процесс корня
  {
    execl("./sqrt", "");
  }
  else
  if (p2 == 0) //иначе квадрат
  {
    execl("./proiz", "");
  }
  else
  if (p3==0) //иначе сумма
  {
    execl("./raz", "");
  }
  else
  if (p4==0) //иначе сумма
  {
    execl("./del", "");
  }
  else //иначе основной процесс
  {
  mysock = socket(AF_INET, SOCK_DGRAM, 0); //создаём сокет
  addr5.sin_family = AF_INET; 
  addr5.sin_port = htons(PORT); 
  addr5.sin_addr.s_addr = inet_addr(MYSOCK); 
  bind(mysock, (struct sockaddr *)&addr5, sizeof(addr5)); //забиваем сокет для того, чтобы его слушать.
 
  proizsock = socket(AF_INET, SOCK_DGRAM, 0); 
  addr1.sin_family = AF_INET;
  addr1.sin_port = htons(PORT);
  addr1.sin_addr.s_addr = inet_addr(SQIP);
  connect(proizsock, (struct sockaddr *)&addr1, sizeof(addr1));
  
  razsock = socket(AF_INET, SOCK_DGRAM, 0); 
  addr2.sin_family = AF_INET;
  addr2.sin_port = htons(PORT);
  addr2.sin_addr.s_addr = inet_addr(SUMIP);
  connect(razsock, (struct sockaddr *)&addr2, sizeof(addr2));
  
  sqrtsock = socket(AF_INET, SOCK_DGRAM, 0);
  addr3.sin_family = AF_INET;
  addr3.sin_port = htons(PORT);
  addr3.sin_addr.s_addr = inet_addr(SQRTIP);
  connect(sqrtsock, (struct sockaddr *)&addr3, sizeof(addr3));

  delsock = socket(AF_INET, SOCK_DGRAM, 0);
  addr4.sin_family = AF_INET;
  addr4.sin_port = htons(PORT);
  addr4.sin_addr.s_addr = inet_addr(SUMIP);
  connect(delsock, (struct sockaddr *)&addr4, sizeof(addr4));

  float a,b,c, b2, 4a, 4ac, d;
  cout << "Input 3 numbers greater then zero.\n";
  cin >>a >> b>> c; 
  if (a<=0 || b<=0)

  cout << "A: " << a << " B: " << b << "C:" << c << endl;
  c=4*c;
  cout << "Sending a" << endl;
  sem_post(proiz); //открываем семафор 
  send(proizsock, &b, sizeof(b), 0);
  send(proizsock, &b, sizeof(b), 0);
  bytes_read=recvfrom(mysock, &b2, sizeof(float), 0, NULL, NULL); //читаем результат
  total+=bytes_read;
  cout << "Reciving b2 " << b2 << endl;
  cout << "Sending b2" << endl;

  sem_post(proiz); 
  send(proizsock, &a, sizeof(a), 0);
  send(proizsock, &c, sizeof(c), 0); 
  bytes_read=recvfrom(mysock, &c, sizeof(float), 0, NULL, NULL); 
  total+=bytes_read;
  cout << "Reciving 4ac " << c << endl;
  cout << "Sending 4ac" << endl;

  sem_post(raz);
  send(razsock, &b2, sizeof(b2), 0); 
  send(razsock, &c, sizeof(c), 0); 
  bytes_read=recvfrom(mysock, &d, sizeof(float), 0, NULL, NULL); 
  cout << "Reciving disk " << d << endl;
  total+=bytes_read;
  cout << "Sending raz" << endl;

  sem_post(sqrts); //тут сука мы блять корень хотим получить
  send(sqrtsock, &d, sizeof(d), 0); //отправляем блядскую сумму
  bytes_read=recvfrom(mysock, &d, sizeof(float), 0, NULL, NULL); //читаем блядский результат
  cout << "Reciving sqrt " << d << endl;
  total+=bytes_read;

  sem_post(raz); 
  send(razsock, &d, sizeof(d), 0);
  send(razsock, &b, sizeof(b), 0); 
  bytes_read=recvfrom(mysock, &x1, sizeof(float), 0, NULL, NULL);  
  total+=bytes_read;
  
  a=2*a;
  d=-d;

  sem_post(raz); 
  send(razsock, &d, sizeof(d), 0); 
  send(razsock, &b, sizeof(b), 0); 
  bytes_read=recvfrom(mysock, &x2, sizeof(float), 0, NULL, NULL); 
 
  total+=bytes_read;
 
  sem_post(del); 
  send(proizsock, &x1, sizeof(x1), 0);
  send(proizsock, &a, sizeof(a), 0);
  bytes_read=recvfrom(mysock, &x1, sizeof(float), 0, NULL, NULL); 
  total+=bytes_read;
  cout << "Reciving x1 " << x1 << endl;
  cout << "Sending x1" << endl;

  sem_post(del); 
  send(proizsock, &x2, sizeof(x2), 0); 
  send(proizsock, &a, sizeof(a), 0); 
  bytes_read=recvfrom(mysock, &x2, sizeof(float), 0, NULL, NULL); 
  total+=bytes_read;
  cout << "Reciving x2 " << x2 << endl;
  cout << "Sending x2" << endl;


  cout << "RESULT: " << x1 << x2 << endl; 
  cout << "TOTAL BYTES READ: " << total << endl;
  return 0;
}
}
