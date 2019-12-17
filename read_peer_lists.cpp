//clear; rm -frv read_peer_lists.o; clear; g++-7 -g -fPIC -Wall -c read_peer_lists.cpp

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

using namespace std;

extern vector<string> peer_lists;
extern vector<string> config_file_parameter;
extern string lokal_ip_adresse;

void read_peer_lists()
	{
		//cout<<"\e[1m"<<"read_peer_lists.cpp"<<"\e[0m"<<endl;
		//peer_lists.push_back("PEER 1");
		
//Liste aus Datei lesen
		ifstream fileoperation_conf;
		fileoperation_conf.open("/etc/blockchain/peer_lists.cfg", ios::in); 
		
		string config_parameter = "";
		//string config_parameter_2 = "";
		//int gleich_gefunden = 0;
		
		while (!fileoperation_conf.eof())
		{
			getline(fileoperation_conf, config_parameter);
			//cout<<"config_parameter: "<<config_parameter<<endl;
			//Filter der einzelnen Parameter######

			if (config_parameter == "")
			{
				//cout<<"leer config_parameter_2"<<config_parameter<<endl;
				continue;
			}

			/*
			gleich_gefunden = config_parameter.find_last_of("=");
			//cout<<"config_parameter: "<<config_parameter.substr(gleich_gefunden + 1 ,99)<<endl;
			config_parameter_2 = config_parameter.substr(gleich_gefunden + 2 ,999);						//auskommentiert
			//cout<<config_parameter_2<<endl;
			config_file_parameter.push_back(config_parameter_2);
			*/
			peer_lists.push_back(config_parameter);

		}

		fileoperation_conf.close();
		
//###########################################################################################
//Peer Liste von den Peers erfragen

		//Alle Peers einzelnt anfragen. Peerliste abgleichen
		int anzahl_peers_aus_datei = 0;
		anzahl_peers_aus_datei = peer_lists.size();
		//cout<<"anzahl_peers_aus_datei#"<<anzahl_peers_aus_datei<<endl;
				
		for (int i = 0; i < anzahl_peers_aus_datei; i++)
		{

			//string bc_peer = "127.0.0.1";
			//string bc_peer_port = "6379";
			string bc_peer;
			//string bc_peer_port = "8888";
			string bc_peer_port = config_file_parameter[1];
			bc_peer = peer_lists[i];
			if (bc_peer == lokal_ip_adresse)
			{
				//cout<<"Eigene IP"<<endl;
				continue;
			}

			//TLS Initialisierung################################
			//gnuTLS Initilisieren
			int tls_init_status = 666;
			tls_init_status = tls_init();
			//cout<<"tls_init_status read_peer_lists.cpp#"<<tls_init_status<<endl;
			//###
			struct tls *tls = NULL;
			tls = tls_client();
			//cout<<"tls_client read_peer_lists.cpp#"<<tls<<endl;
			//###
			struct tls_config *config = NULL;
			config = tls_config_new();
			//cout<<"tls_config_new read_peer_lists.cpp#"<<config<<endl;
			//###
			tls_config_insecure_noverifycert(config);
			tls_config_insecure_noverifyname(config);
			tls_configure(tls, config);
			//##################################################
/*
//string bc_peer = "127.0.0.1";
//string bc_peer_port = "6379";
string bc_peer;
//string bc_peer_port = "8888";
string bc_peer_port = config_file_parameter[1];

bc_peer = peer_lists[i];
*/		
			//bc_peer = "172.17.190.80";
			//cout<<"bc_peer#"<<bc_peer<<endl;
			//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
			struct hostent *host;//Hostname struktuieren
			host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
			
			struct sockaddr_in addr;
			addr.sin_addr = *(struct in_addr*)host->h_addr;
			int s11; 
			
			s11 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
			
			int bc_peer_port_int = atoi(bc_peer_port.c_str());
			addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
			
			addr.sin_family = AF_INET;

			struct timeval timeout;
			timeout.tv_sec  = 1;
			timeout.tv_usec = 0;
			setsockopt (s11, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
			setsockopt (s11, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
		
			int connect_status = 666;
			connect_status = connect(s11,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
			//cout<<"connect_status read_peer_lists.cpp #"<<connect_status<<endl;
			if (connect_status == -1)
			{
				//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
				//cout<<"bc_peer read_peer_lists.cpp"<<bc_peer<<endl;
				continue;
			}
			
			//Redis Command Anzahl der Werte in der Liste
			//string bc_command = "LLEN blockchain_list\r\n";
			string bc_command;
			bc_command = "get peer list\r\n";
			//cout<<"bc_command#"<<bc_command<<"#"<<endl;

			int tls_connect_socket_status = 666;
			tls_connect_socket_status = tls_connect_socket(tls, s11, "localhost");
			//cout<<"tls_connect_socket_status in read_peer_lists.cpp#"<<tls_connect_socket_status<<endl;
			//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;
			
			//char* request = (char*)bc_command.c_str();
			//cout<<"request#"<<request<<"#"<<endl;

				//send(s, request, strlen(request),0);//Daten senden
			//send(s11, bc_command.c_str(), bc_command.length(),0);//Daten senden
			//cout<<"s11#"<<s11<<endl;

			int tls_write_status = 666;
			tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
			//cout<<"tls_write_status read_peer_lists.cpp#"<<tls_write_status<<endl;

			char response[999999];//Empfangspuffer festlegen
			//int bytes;
			ssize_t bytes = 0;
			string antwort_ausgabe;
			vector<string> vektor;
			//int i=0;
			bool ende = true;
			bzero (response, sizeof(response));

			while(ende)
			{

				bytes = tls_read(tls, response, sizeof(response));
				//cout<<"bytes read_peer_lists.cpp#"<<bytes<<endl;

				//bytes = recv(s, response, sizeof(response), 0);
				
				//i = i + 1;
				//cout<<"i#"<<i<<endl;
				//cout<<endl<<response;
				//cout<<"REMOTE peer_lists von " + bc_peer + "#"<<response<<"#"<<endl;;

				//blocks_from_db.append(response);
				//cout<<"response#"<<response<<"#"<<endl;
				//response_temp = response;
				//response_temp.append(response_temp + "@");
				int no_peers = strcmp(response, "##NO PEERS##"); 
				if (no_peers == 0)
				{
					//cout<<"read_peer_lists.cpp NO PEERS continue"<<endl;
					close(s11);
					ende = false;
					continue;
				}
				else
				{
					peer_lists.push_back(response);
				}
				
				//peer_lists.push_back("#");
				//cout<<"response read_peer_lists.cpp#"<<response<<endl;
				
				bzero (response, sizeof(response));
				if (bytes == 0)
				{	
					close(s11);
					ende = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				if (bytes < 999999)
				{	
					close(s11);
					ende = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				if (bytes == -1)
				{	
					close(s11);
					ende = false;
					//cout<<"Last Block in redis#"<<response<<endl;
				}
				//bzero (response, sizeof(response));
			}
		
			tls_close(tls);
			tls_free(tls);
			tls_config_free(config);

		}

//Array überprüfen und doppelte Einträge löschen

//Sich selbst rausfiletren falls die IP vom Remote Server kommt.
//cout<<"peer_lists.size() in read_peer_lists.cpp#"<<peer_lists.size()<<endl;
//cout<<"peer_lists[0] in read_peer_lists.cpp#"<<peer_lists[0]<<endl;
//###############################################################################
//ENDE
//cout<<"ENDE"<<endl;
	}