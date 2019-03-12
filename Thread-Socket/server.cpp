#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

enum ordem { DECRESCENTE, CRESCENTE };

void server_processor(long long* input){
   sort(input+1, input+input[0], less<long long>());
}

void get_cfg(int& port, int& len){
   ifstream file("cfg.txt");
   if(file.is_open()){
      file >> port >> len;
      file.close();
      return;
   }
   exit(EXIT_FAILURE);
}

int main(){
   vector<thread> ts; // threads
   int server_fd, new_socket, valread, PORT, BUFFER_SIZE;
   get_cfg(PORT, BUFFER_SIZE);
   sockaddr_in address;
   const int opt = 1;
   int addrlen = sizeof(address);
   long long* buffer = new long long[BUFFER_SIZE];
   unsigned long count = 1;

   // CRIANDO UM SOCKET
   if((server_fd = socket(AF_INET, SOCK_STREAM,  IPPROTO_TCP)) == false) {
      perror("[ERRO] Socket falhou");
      exit(EXIT_FAILURE);
   }

   address.sin_addr.s_addr = inet_addr("127.0.0.1");
   address.sin_family = AF_INET;
   address.sin_port = htons(PORT);
   memset(address.sin_zero, 0, sizeof(address.sin_zero));

   if(bind(server_fd, (sockaddr*)&address, addrlen) < 0){
      perror("[ERRO] Bind");
      exit(EXIT_FAILURE);
   }

   if(listen(server_fd, 20) < 0){
      perror("[ERRO] Listen");
      exit(EXIT_FAILURE);
   }
   cout << "[STATUS] Executando servidor de ordenação..." << endl;

   sockaddr_in remoto;
   socklen_t remoto_len = sizeof(remoto);
   while(true){

      if((new_socket = accept(server_fd, (sockaddr*) &remoto, &remoto_len)) < 0){
         perror("[ERRO] Accept");
         exit(EXIT_FAILURE);
      }

      cout << "[STATUS] Conectado ao usuario." << count << endl;

      if((valread = recv(new_socket, (void*)buffer, sizeof(long long)*BUFFER_SIZE, 0)) < 0){
         perror("[ERRO] Erro na leitura do vetor");
         exit(EXIT_FAILURE);
      }

      cout << "[STATUS] Mensagem recebida." << endl;

      ts.push_back(thread(server_processor, ref(buffer)));
      ts[count-1].join();

      if((valread = send(new_socket, (void*)buffer, sizeof(long long)*BUFFER_SIZE, 0)) <= 0) {
         perror("[ERRO] Erro na resposta");
         exit(EXIT_FAILURE);
      }

      cout << "[STATUS] Usuario " << count << " respondido." << endl;

      count++;
      shutdown(new_socket, SHUT_RDWR);
      close(new_socket);

   }
   close(server_fd);
   delete[] buffer;
   return 0;
}
