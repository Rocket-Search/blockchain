//clear; rm -frv send_block_to_server.o; g++-7 -g -fPIC -Wall -c send_block_to_server.cpp

//C_C++ Header
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
//algorithm fürs string klein machen
#include <algorithm>
//Zum Casten von Char Hex Array nach string (bei md5sum)
#include <iomanip>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <thread>
#include <time.h>
//Network Header
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <string.h>
#include <stdlib.h> 
#include <vector>
//SSL
#include <errno.h>
#include <malloc.h>
#include <resolv.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
//TLS
#include <tls.h>

using namespace std;

//extern string block_formated_redis;
extern string block_formated;
extern vector<string> config_file_parameter;

void send_block_to_server()
{
	//cout<<"\e[1m"<<"send_block_to_server.cpp"<<"\e[0m"<<endl;
	//cout<<"SENDE BLOCK AN BC SERVER"<<endl;
	//cout<<"block_formated in send_block_to_server.cpp#"<<block_formated<<endl;
	//SSL Initialoiseren

//####################################################################
//Debug to File by sap_bcc.cpp
//ofstream debug_file_3;
//debug_file_3.open ("/tmp/blockchain_daemon.cpp_debug_file.log", ios::app );
//####################################################################
	
	//TLS Initialisierung################################
	//gnuTLS Initilisieren
	int tls_init_status = 666;
	tls_init_status = tls_init();
	//cout<<"tls_init_status#"<<tls_init_status<<endl;
	//###
	struct tls *tls = NULL;
	tls = tls_client();
	//cout<<"tls_client#"<<tls<<endl;
	//###
	struct tls_config *config = NULL;
	config = tls_config_new();
	//cout<<"tls_config_new#"<<config<<endl;
	//###
	tls_config_insecure_noverifycert(config);
	tls_config_insecure_noverifyname(config);
	tls_configure(tls, config);
	//##################################################
	
	string bc_peer_1;
	//string bc_peer_port_1 = "8888";
	string bc_peer_port_1 = config_file_parameter[1];
	//bc_peer_1 = "172.17.190.84";							//BC-Server . aus config lesen
	bc_peer_1 = config_file_parameter[0];							//BC-Server . aus config lesen
	struct hostent *host_1;//Hostname struktuieren
	host_1 = gethostbyname(bc_peer_1.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_1;
	addr_1.sin_addr = *(struct in_addr*)host_1->h_addr;
	int s1; 
	s1 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_1 = atoi(bc_peer_port_1.c_str());
	addr_1.sin_port = htons(bc_peer_port_int_1);//Connection Portnummer des Servers festlegen
	addr_1.sin_family = AF_INET;
	int connect_status_1;
	connect_status_1 = 666;
	connect_status_1 = connect(s1,(struct sockaddr*)&addr_1, sizeof(addr_1));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status_1 == -1)
		{
			cout<<"Socket error auf der Gegenseite send_block_to_server.cpp# "<<connect_status_1<<endl;
			exit(-1);
		}
	string bc_command_1;
	
	bc_command_1 = "set block to bc_server### " + block_formated + "###@###\r\n";
	//cout<<"BC SERVER block_nummer#"<<bc_command_1<<endl;
//debug_file_3<<"bc_command_1 in send_block_to_server.cpp#"<<bc_command_1<<"#"<<endl;

	int tls_connect_socket_status = 666;
	tls_connect_socket_status = tls_connect_socket(tls, s1, "localhost");
	//cout<<"tls_connect_socket_status#"<<tls_connect_socket_status<<endl;
	//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;

	//send(s1, bc_command_1.c_str(), bc_command_1.length(),0);//Daten senden
	int tls_write_status = 666;
	tls_write_status = tls_write(tls, bc_command_1.c_str(), strlen(bc_command_1.c_str()));
	//cout<<"tls_write_status#"<<tls_write_status<<endl;

	//Status Meldung von bc_server abfragen
	char response_1[1024];//Empfangspuffer festlegen
	//int bytes_1; 
	ssize_t bytes_1 = 0;
	string antwort_ausgabe_1;
	bool ende_1 = true;
	bzero (response_1, sizeof(response_1));
	string response_temp_1;
	response_temp_1 = "";
	while(ende_1)
		{

			bytes_1 = tls_read(tls, response_1, sizeof(response_1));
response_temp_1.append(response_1);
			//bytes_1 = recv(s1, response_1, sizeof(response_1), 0);
			//if ( bytes_1 = recv(s1, response_1, sizeof(response_1), 0) != 0 );
			//if ( bytes_1 = recv(s1, response_1, sizeof(response_1), 0) != NULL );
		//{
				if (bytes_1 == 0)
				{	
					close(s1);
					ende_1 = false;
					
				}
				if (bytes_1 == -1)
				{	
					close(s1);
					ende_1 = false;
				}
				//if (bytes_1 <= 1024)
				//{	
				//	close(s1);
				//	ende_1 = false;
				//}
				//if (bytes_1 == 1024)
				//{	
				//	close(s1);
				//	ende_1 = false;
				//}
				if (bytes_1 < 1024)
				{	
					close(s1);
					ende_1 = false;
				}
//response_temp_1.append(response_1);
				//cout<<"redis Datensätze LOKAL in while#"<<response_1<<"#"<<endl;
		//}
		}
	close(s1);
	
	if (response_temp_1 == "")
	{
		cout<<"STATUS # BLOCK IN PEER NETZ NICHT VERTEILT"<<endl;
	}
	else
	{
		cout<<"STATUS :"<<endl<<response_1<<endl;
	}	
	
	tls_close(tls);
	tls_free(tls);
	tls_config_free(config);
	
//###################################################
//Debug file schliesen.
//debug_file_3.close();
//###################################################
//cout<<"ENDE"<<endl;
}
