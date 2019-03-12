#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

enum ordem { DECRESCENTE, CRESCENTE };

void preenche_vetor(long long*& vet, long long& len){
   int i=0;

   cout << "[INPUT] Qual o tamanho do vetor? ";
   cin >> len;
   len++;
   vet = new long long[len];
   vet[i++] = len;
   while(i < len) {
      cout << "[INPUT] Insira o item " << i << ": ";
      cin >> vet[i++];
   }
}

void ler_vetor(long long* buffer) {
   long long len = buffer[0];
   for(int i=1; i<len; i++) {
      cout << "[RESPOSTA] " << buffer[i] << endl;
   }
}

void get_cfg(int& port, int& len){
   ifstream file("cfg.txt");
   string temp;
   if(file.is_open()){
      file >> temp >> port;
      file >> temp >> len;
      file.close();
      return;
   }
   exit(EXIT_FAILURE);
}

int main(){
   int sock = 0, valread, PORT, BUFFER_SIZE;
   get_cfg(PORT, BUFFER_SIZE);
   sockaddr_in serv_addr;
   long long* buffer = new long long[BUFFER_SIZE];
   unsigned long count = 1;


   // CRIANDO UM SOCKET
   if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("[ERRO] Socket falhou.");
      exit(EXIT_FAILURE);
   }

   memset(&serv_addr, '0', sizeof(serv_addr));

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);

   if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
      cerr << "[ERRO] Endereço IP invalido ou nao suportado." << endl;
      exit(EXIT_FAILURE);
   }

   cout << "[STATUS] Executando cliente..." << endl;

   if(connect(sock, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
         cerr << "[ERRO] Conexao falhou" << endl;
         exit(EXIT_FAILURE);
   }

   long long *vet, len;
   preenche_vetor(vet, len);

   auto answ = send(sock, (void*)vet, sizeof(long long)*len, 0);
   if(answ <= 0) {
      cerr << "[ERRO] Falha no envio" << endl;
      exit(EXIT_FAILURE);
   }

   cout << "[STATUS] Mensagem enviada ao servidor de ordenação." << endl;

   if((valread = read(sock, (void*)buffer, sizeof(long long)*BUFFER_SIZE)) < 0) {
      perror("[ERRO] Erro na leitura do vetor ordenado.");
      exit(EXIT_FAILURE);
   }

   ler_vetor(buffer);


   close(sock);
   delete[] buffer;
   delete[] vet;
   return 0;
}