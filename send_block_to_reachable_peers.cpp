//clear; rm -frv send_block_to_reachable_peers.o; g++-7 -g -fPIC -Wall -c send_block_to_reachable_peers.cpp

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

extern vector<string> erreichbare_peers;
extern string pure_bc_block;
extern vector<string> config_file_parameter;
extern string lokal_ip_adresse;

void send_block_to_reachable_peers()
{
	//cout<<"send_block_to_reachable_peers.cpp"<<endl;
	//cout<<"erreichbare_peers#"<<erreichbare_peers.size()<<endl;
	//cout<<"erreichbare_peers#"<<erreichbare_peers[0]<<endl;
	//cout<<"\e[1m"<<"send_block_to_reachable_peers.cpp"<<"\e[0m"<<endl;
	
	//cout<<"lokal_ip_adresse#"<<lokal_ip_adresse<<endl;

	for (int i = 0; i < erreichbare_peers.size(); i++)
	{
		
		if (lokal_ip_adresse ==  erreichbare_peers[i])
		{
			//cout<<"Lokale IP, ueberspringen"<<endl;
			continue;
		}
		
		//TLS Initialisierung################################
		//gnuTLS Initilisieren
		int tls_init_status = 666;
		tls_init_status = tls_init();
		//cout<<"tls_init_status validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls_init_status<<endl;
		//###
		struct tls *tls = NULL;
		tls = tls_client();
		//cout<<"tls_client validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls<<endl;
		//###
		struct tls_config *config = NULL;
		config = tls_config_new();
		//cout<<"tls_config_new validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<config<<endl;
		//###
		tls_config_insecure_noverifycert(config);
		tls_config_insecure_noverifyname(config);
		tls_configure(tls, config);
		//##################################################
	
		string bc_peer_1;
		//string bc_peer_port_1 = "8888";
		string bc_peer_port_1 = config_file_parameter[1];
		bc_peer_1 = erreichbare_peers[i];						//Ereichbare Peers seit dem start von bc_server
		//cout<<"bc_peer_1 in send_block_to_reachable_peer.cpp z. 83#"<<bc_peer_1<<endl;


		struct hostent *host_1;//Hostname struktuieren
		host_1 = gethostbyname(bc_peer_1.c_str()); //eventuell die IP in DNS Namen umwandeln
		struct sockaddr_in addr_1;
		addr_1.sin_addr = *(struct in_addr*)host_1->h_addr;
		int s1; 
		s1 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		int bc_peer_port_int_1 = atoi(bc_peer_port_1.c_str());
		addr_1.sin_port = htons(bc_peer_port_int_1);//Connection Portnummer des Servers festlegen
		addr_1.sin_family = AF_INET;
		
		struct timeval timeout;
		timeout.tv_sec  = 10;
		timeout.tv_usec = 0;
		setsockopt (s1, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s1, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

		int connect_status_1;
		connect_status_1 = 666;
		connect_status_1 = connect(s1,(struct sockaddr*)&addr_1, sizeof(addr_1));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status_1 == -1)
		{
			//cout<<"Socket error auf der Gegenseite send_block_to_reachable_peers.cpp# "<<connect_status_1<<endl;
			//exit(-1);
		}
		else
		{	
			int tls_connect_socket_status = 666;
			tls_connect_socket_status = tls_connect_socket(tls, s1, "localhost");
			//cout<<"tls_connect_socket_status in validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls_connect_socket_status<<endl;
			//if (tls_connect_socket_status != 0){cout<<" tls_error(tls) in send_block_to_reachable_peers.cpp"<<tls_error(tls)<<endl; exit(-1);}
			if (tls_connect_socket_status != 0){cout<<" tls_error(tls) in send_block_to_reachable_peers.cpp"<<tls_error(tls)<<endl;}
		
			string bc_command_1;

			bc_command_1 = "set block to peer ### " + pure_bc_block + "###@###\r\n";
			//cout<<"send block to peers#"<<bc_command_1<<endl;
			//send(s1, bc_command_1.c_str(), bc_command_1.length(),0);//Daten senden
			
			int tls_write_status = 666;
			tls_write_status = tls_write(tls, bc_command_1.c_str(), strlen(bc_command_1.c_str()));
			//cout<<"tls_write_status validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls_write_status<<endl;
		
			close(s1);
			
			tls_close(tls);
			tls_free(tls);
			tls_config_free(config);
	
		}
}
//cout<<"ENDE"<<endl;
}