/*-------------------------------------------------------------*/
/* Exemplo Socket Raw - Captura pacotes recebidos na interface */
/*-------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos   	  	        */

#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP

#include <netinet/in_systm.h> //tipos de dados

#define BUFFSIZE 1518

// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.

  unsigned char buff1[BUFFSIZE]; // buffer de recepcao

  int sockd;
  int on;
  struct ifreq ifr;

// Contadores:
int totalCounter = 0;
int ipv4Counter = 0;
int ipv6Counter = 0;
int arpCounter = 0;
int icmpCounter = 0;
int icmpv6Counter = 0;
int tcpCounter = 0;
int udpCounter = 0;

void aplicacao(){
	switch(){

	}
}

void tcp(){
	//TODO: Exibir todos protocolos até aqui
	tcpCounter++;

	//TODO: Verificar protocolos de aplicação com base na porta, tanto de destino(pos 25 e 26) como origem(pos 23 e 24)
	if(buff1[23] == )
	buff1[23] == 
}

void udp(){
	//TODO: Verificar protocolos de aplicação com base na porta, tanto de destino(pos 25 e 26) como origem(pos 23 e 24)
	//TODO: Exibir todos protocolos até aqui
	udpCounter++;
}

void arp(){
	//TODO: Exibir todos protocolos até aqui
	arpCounter++;
}

void ipv6(){
	ipv6Counter++;
	//UDP
	if(buff1[20] == 0x11){
		udp();
	}
	//TCP
	else if(buff1[20] == 0x06 ){
		tcp()

	}
	//ICMPV6
	else if(buff1[20] == 0x3a ){
		//TODO: Exibir todos protocolos até aqui
		icmpv6Counter++;
	}
}

void ipv4(){
	ipv4Counter++;
	//UDP
	if(buff1[24] == 0x11){
		udp();
	}
	//TCP
	else if(buff1[24] == 0x06 ){
		tcp();
	}
	//ICMP
	else if(buff1[24] == 0x01 ){
		//TODO: Exibir todos protocolos até aqui
		icmpCounter++;
	}
}

int main(int argc,char *argv[])
{
    /* Criacao do socket. Todos os pacotes devem ser construidos a partir do protocolo Ethernet. */
    /* De um "man" para ver os parametros.*/
    /* htons: converte um short (2-byte) integer para standard network byte order. */
    if((sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
       printf("Erro na criacao do socket.\n");
       exit(1);
    }

	// O procedimento abaixo eh utilizado para "setar" a interface em modo promiscuo
	strcpy(ifr.ifr_name, "wlp2s0");
	if(ioctl(sockd, SIOCGIFiINDEX, &ifr) < 0)
		printf("erro no ioctl!");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);

	// recepcao de pacotes
	while (1) {
   		recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
		// impress�o do conteudo - exemplo Endereco Destino e Endereco Origem
		//printf("MAC Destino: %x:%x:%x:%x:%x:%x \n", buff1[0],buff1[1],buff1[2],buff1[3],buff1[4],buff1[5]);
		//printf("MAC Origem:  %x:%x:%x:%x:%x:%x \n\n", buff1[6],buff1[7],buff1[8],buff1[9],buff1[10],buff1[11]);
		
		//printf("%x:%x\n", buff1[12], buff1[13]);
		
		// IPv6
		if(buff1[12] == 0x86 && buff1[13] == 0xdd){
			totalCounter++;
			ipv6();
			printf("ipv6");
		}
		// ARP
		else if(buff1[12] == 0x08 && buff1[13] == 0x06){
			totalCounter++;
			arp();
			printf("arp");
		}
		//IPV4
		else if(buff1[12] == 0x08 && buff1[13] == 0x00){
			totalCounter++;
			ipv4();
			printf("ipv4");
		}
	}
}