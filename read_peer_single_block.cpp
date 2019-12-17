//clear; rm -frv read_peer_single_block.o; g++-7 -g -fPIC -Wall -c read_peer_single_block.cpp

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
//TLS
#include <tls.h>
#include <errno.h>
#include <gnutls/gnutls.h>

using namespace std;

extern string blocks_from_db;
//extern string bc_command_from_main;
//extern string read_loacal_db_records;
extern string erreichbare_peers_fuer_read_peer_single_block;
extern unsigned long long block_nummer_fuer_read_peer_single_block;
extern vector<string> config_file_parameter;
extern string lokal_ip_adresse;

void read_peer_single_block()
	{
		//cout<<"read_peer_single_block"<<endl;
		//cout<<"\e[1m"<<"read_peer_single_block.cpp"<<"\e[0m"<<endl;
	

	
		//cout<<"blocks_from_db#"<<blocks_from_db<<"#"<<	endl;
		
		//string bc_server = "127.0.0.1";
		string bc_server = erreichbare_peers_fuer_read_peer_single_block;
		//cout<<"remote bc_server#"<<bc_server<<"#"<<endl;
		//string bc_port = "8888";
		string bc_port = config_file_parameter[1];
		//cout<<"bc_port#"<<bc_port<<endl;

		//Eigene IP überspringen
		//cout<<"lokal_ip_adresse#"<<lokal_ip_adresse<<"#"<<endl;
		//if (lokal_ip_adresse == bc_server);
		//if (lokal_ip_adresse.compare(0,99,bc_server) == 0);
		int result = strcmp(lokal_ip_adresse.c_str(), bc_server.c_str());		
		//cout<<"strcmp result#"<<result<<endl;
		if (result == 0)
		{
			//cout<<"Eigene IP"<<endl;
			return;
		}

		//cout<<"Lese single Block via BC Protokoll"<<endl;
		
		//TLS Initialisierung################################
		//libressl_TLS Initilisieren
		int tls_init_status = 666;
		tls_init_status = tls_init();
		//cout<<"tls_init_status read_peer_single_block.cpp#"<<tls_init_status<<endl;
		//###
		struct tls *tls = NULL;
		tls = tls_client();
		//cout<<"tls_client read_peer_single_block.cpp#"<<tls<<endl;
		//###
		struct tls_config *config = NULL;
		config = tls_config_new();
		//cout<<"tls_config_new read_peer_single_block.cpp#"<<config<<endl;
		//###
		tls_config_insecure_noverifycert(config);
		tls_config_insecure_noverifyname(config);
		tls_configure(tls, config);
		//##################################################
		
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(bc_server.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		int s4; 
		
		s4 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int bc_port_int = atoi(bc_port.c_str());
		addr.sin_port = htons(bc_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET; 

		struct timeval timeout;
		timeout.tv_sec  = 10;
		timeout.tv_usec = 0;
		setsockopt (s4, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s4, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

		int connect_status = 666;
		connect_status = connect(s4,(struct sockaddr*)&addr, sizeof(addr));
		//cout<<"connect_status in read_peer_single_block.cpp z. 113# "<<connect_status<<endl;

		if (connect_status == -1)
		{
			//cout<<"Socket error auf der Gegenseite read_peer_single_block.cpp# "<<connect_status<<endl;
			//cout<<"bc_server#"<<bc_server<<endl;
			//exit(-1);
			//continue;
			//return (1);
			//terminate();
			//goto jmp;
			//return 0;
			//goto exit;
			//break;
			//exit(0);
			//exit;
			//return;
		}
		else
		{
			int tls_connect_socket_status = 666;
			tls_connect_socket_status = tls_connect_socket(tls, s4, "localhost");
			//cout<<"tls_connect_socket_status in read_peer_single_block.cpp #"<<tls_connect_socket_status<<endl;
			if (tls_connect_socket_status < 0)
			{
				cout<<" tls_error(tls)"<<tls_error(tls)<<endl;
			}

			//Redis Command Anzahl der Werte in der Liste
			//string bc_command = "LLEN blockchain_list\r\n";
			string bc_command;
			//bc_command = bc_command_from_main;
			//cout<<"block_nummer_fuer_read_peer_single_block#"<<block_nummer_fuer_read_peer_single_block<<endl;
				string block_nummer_fuer_read_peer_single_block_string;
				stringstream strstream;
				strstream << block_nummer_fuer_read_peer_single_block;
				strstream >> block_nummer_fuer_read_peer_single_block_string;
			bc_command = "get single block " + block_nummer_fuer_read_peer_single_block_string + "\r\n";
			//bc_command = "get single block\r\n";
			//cout<<"bc_command in #"<<bc_command<<endl;
			//cout<<"bc_command_in read all chains#"<<bc_command<<endl;
			
			char* request = (char*)bc_command.c_str();
			//cout<<"request#"<<request<<endl;

			//send(s4, request, strlen(request),0);//Daten senden
			int tls_write_status = 666;
			tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
			//cout<<"tls_write_status read_peer_single_block.cpp #"<<tls_write_status<<endl;
		
			char response[999999];//Empfangspuffer festlegen
			//char response[1024];//Empfangspuffer festlegen
			//int bytes; 
			ssize_t bytes = 0;
			string antwort_ausgabe;
			vector<string> vektor;
			//int i=0;
			bool ende3 = true;
			bzero (response, sizeof(response));
			bytes = 0;
			
			//string last_block_id ;
		
			while(ende3)
			{
				//bytes = recv(s4, response, sizeof(response), 0);
				bytes = tls_read(tls, response, sizeof(response));
				//i = i + 1;
				//cout<<"i#"<<i<<endl;
				//cout<<"response"<<response<<endl;
				//cout<<"packet groesse bytes#"<<bytes<<endl;
				
				//blocks_from_db = response
				blocks_from_db.append(response);

				//if (blocks_from_db != "")
				//{
					//cout<<"response NICHT leer"<<endl;
					//blocks_from_db = blocks_from_db.erase(blocks_from_db.find_last_not_of("\n"));
					//cout<<"blocks_from_db in_read_SINGLE BLOCK#"<<blocks_from_db<<endl;
				//}
				
				//cout<<"blocks_from_db in_read_SINGLE BLOCK#"<<blocks_from_db<<endl;
						
				bzero (response, sizeof(response));
				if (bytes == 0)
				{	
					close(s4);
					ende3 = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				/*
				if (bytes < 1024)
				{	
					close(s4);
					ende3 = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				*/
				if (bytes == -1)
				{	
					close(s4);
					ende3 = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				if (bytes == 999999)
				{	
					//close(s4);
					//cout<<"bytes == 1024"<<endl;
					ende3 = true;
				}
				if (bytes < 999999)
				{	
					//close(s4);
					//cout<<"bytes < 1024"<<endl;
					//
					ende3 = false;
				}
							
				//bzero (response, sizeof(response));
			}
			
			//cout<<"Schliesse S4 in read_peer_single_block"<<endl;
			close(s4);
			//cout<<"Response REMOTE Block#"<<blocks_from_db<<"#"<<endl;
			tls_close(tls);
			tls_free(tls);
			tls_config_free(config);
}
//jmp: cout<<"ENDE JUMP"<<endl;
//exit:
//    return 0;
//cout<<"ENDE"<<endl;

	}
