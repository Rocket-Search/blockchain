//clear; rm -frv  send_peer_local_chain_longer_and_send_blocks.o; g++-7 -g -fPIC -Wall -c  send_peer_local_chain_longer_and_send_blocks.cpp

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
extern vector<string> config_file_parameter;
extern string blocks_from_db;
extern string redis_command_from_main;
extern string remote_ip;
extern string ip_fuer_block_senden;

void send_peer_local_chain_longer_and_send_blocks()
{
	//cout<<"send_peer_local_chain_longer_and_send_blocks"<<endl;
	//cout<<"\e[1m"<<"send_peer_local_chain_longer_and_send_blocks.cpp"<<"\e[0m"<<endl;	
	//cout<<"erreichbare_peers"<<erreichbare_peers[0]<<endl;
	//cout<<"SENDE FEHLENDE BLÖCKE AN REMOTE PEER"<<endl;

	//Sende BC Protokoll Kommando an remote Peer
//for(unsigned int i = 0 ; i < erreichbare_peers.size(); i++)
//{
		//cout<<"Sende Bc-Protokoll Kommando an Remote Peer"<<endl;
		//cout<<"erreichbare_peers#"<<erreichbare_peers[i]<<endl;

		//TLS Initialisierung################################
		//gnuTLS Initilisieren
		int tls_init_status = 666;
		tls_init_status = tls_init();
		//cout<<"tls_init_status send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<tls_init_status<<endl;
		//###
		struct tls *tls = NULL;
		tls = tls_client();
		//cout<<"tls_client send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<tls<<endl;
		//###
		struct tls_config *config = NULL;
		config = tls_config_new();
		//cout<<"tls_config_new send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<config<<endl;
		//###
		tls_config_insecure_noverifycert(config);
		tls_config_insecure_noverifyname(config);
		tls_configure(tls, config);
		//##################################################
	
		string bc_peer;
	
		//string bc_peer_port = "8888";
		string bc_peer_port = config_file_parameter[1];
	
		//Sende an 172.17.190.78 das die ketten LOKAL (172.17.190.84) Länger sind
		//bc_peer = "172.17.190.86";
		//bc_peer = erreichbare_peers[i];
		bc_peer = ip_fuer_block_senden;
		//bc_peer = remote_ip;
		//cout<<"erreichbare_peers 1"<<bc_peer<<endl;

		//cout<<"erreichbare_peers[i] in send_peer_local_chain_longer_and_send_block.cpp"<<erreichbare_peers[i]<<endl;	
		
		//cout<<"bc_peer#"<<bc_peer<<endl;
		
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		int s5; 
		
		s5 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int bc_peer_port_int = atoi(bc_peer_port.c_str());
		
		addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET;
		
		int connect_status;
		connect_status = 666;
		
		connect_status = connect(s5,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
				
		if (connect_status == -1)
		{
			//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
			//continue;
			//return;
			cout<<"send_peer_local_chain_longer_and_send_blocks.cpp exit -1"<<endl;
			exit(-1);
		}
		
		//An Peer Senden das unsere ketten länger sind 
		//und Peer veranlassen unsere Ketten zu laden, nach vlaidierung
		string bc_command;
		bc_command = "local chain longer send get chain command\r\n";
		//cout<<"bc_command send to bc_server"<<bc_command<<endl;
		
		int tls_connect_socket_status = 666;
		tls_connect_socket_status = tls_connect_socket(tls, s5, "localhost");
		//cout<<"tls_connect_socket_status in send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<tls_connect_socket_status<<endl;
		//if (tls_connect_socket_status != 0){cout<<" tls_error(tls) in tls_connect_socket_status.cpp"<<tls_error(tls)<<endl; exit(-1);}
		if (tls_connect_socket_status != 0){cout<<" tls_error(tls) in tls_connect_socket_status.cpp"<<tls_error(tls)<<endl;}

		//bc_command = "local chain longer send get chain command";
		//bc_command = "local chain longer send get chain command\n";
		//cout<<"bc_command#"<<bc_command<<"#"<<endl;
		//send(s5, bc_command.c_str(), bc_command.length(),0);//Daten senden

		int tls_write_status = 666;
		tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
		//cout<<"tls_write_status send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<tls_write_status<<endl;
		if (tls_write_status == -1){cout<<"tls_write_status TLS Error# "<<tls_error(tls)<<endl;exit(-1);}
		
		//cout<<"s#"<<s5<<endl;

		close(s5);
		tls_close(tls);
		tls_free(tls);
		tls_config_free(config);
	

/*	
//##################################################################################################################################
//##################################################################################################################################
//##################################################################################################################################

//NUN die Fehlenden Blöcke senden ##############
		//Protokoll: "set block to bc_server###"
cout<<"SENDE Fehlende Blöcke"<<endl;
		//Eigenen Block aus DB holen und dann senden		

//Kettenlänge ermitteln
		redis_command_from_main = "";
		redis_command_from_main = "LLEN blockchain_list\r\n";
		void read_all_chains_from_db();
		read_all_chains_from_db();
cout<<"Lokale Block Anzahl blocks_from_db"<<blocks_from_db<<endl;
		//Kettenzahl nach long long konvertieren
		long long anzahl_ketten_lokal = 0;
		string anzahl_ketten_lokal_string = blocks_from_db;
		
		//anzahl_ketten_lokal_string = anzahl_ketten_lokal_string.substr(1,anzahl_ketten_lokal_string.length());
		try{anzahl_ketten_lokal_string = anzahl_ketten_lokal_string.substr(1,anzahl_ketten_lokal_string.length());}catch( std::out_of_range& exception ){cout<<"Error send_peer_local_chain_longer_and_send_blocks.cpp anzahl_ketten_lokal_string std::out_of_range"<<endl;}
		anzahl_ketten_lokal =  stoll(anzahl_ketten_lokal_string.c_str());
		//cout<<"unsigned long long # anzahl_ketten_lokal#"<<anzahl_ketten_lokal<<endl;

//Blockanzahl mit for durchlaufen und jeden Block laden
		//for (unsigned long long i = 0; i < anzahl_ketten_lokal; i++)
		for (long long i = anzahl_ketten_lokal - 1; i > -1; i--)
		{
			string block_nummer;
				stringstream strstream;
				strstream << i;
				strstream >> block_nummer;
			redis_command_from_main = "";
			redis_command_from_main = "LINDEX blockchain_list " + block_nummer + "\r\n";
			//cout<<"redis_command_from_main Block Nummer#"<<redis_command_from_main<<endl;
			void read_all_chains_from_db();
			read_all_chains_from_db();
			//cout<<"Block Nummer " + block_nummer +" #"<<blocks_from_db<<endl;
			
//##################################################################################################################################
			//Block senden

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
			string bc_peer;
			//string bc_peer_port = "8888";
			//cout<<"config_file_parameter[1]#"<<config_file_parameter[1]<<endl;
			string bc_peer_port = config_file_parameter[1];
//bekommt falsche REMOTE IP, überdenken
bc_peer = ip_fuer_block_senden;
//bc_peer = "172.17.190.84";
cout<<"remote_ip 2#"<<bc_peer<<endl;
//string test_cin; cout<<"CIN"<<endl;cin>>test_cin;

			struct hostent *host;//Hostname struktuieren
			host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
			struct sockaddr_in addr;
			addr.sin_addr = *(struct in_addr*)host->h_addr;
			int s12 = 666; 
			s12 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
			//cout<<"socket s12#"<<s12<<endl;
			int bc_peer_port_int = atoi(bc_peer_port.c_str());
			addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
			addr.sin_family = AF_INET;
			int connect_status;
			connect_status = 666;
			connect_status = connect(s12,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
			cout<<"connect_status send_peer_local_chain_longer_and_send_blocks.cpp #"<<connect_status<<endl;
			//string cin_input;
			//cin>>cin_input;
			//cout<<cin_input;
			if (connect_status == -1)
			{
				cout<<"Socket error auf der Gegenseite 1 in send_peer_local_chain_longer_and_send_blocks.cpp# "<<connect_status<<endl;
				//exit(-1);
			}
			int tls_connect_socket_status = 666;
			tls_connect_socket_status = tls_connect_socket(tls, s12, "localhost");
			cout<<"tls_connect_socket_status in send_peer_local_chain_longer_and_send_blocks.cpp 1#"<<tls_connect_socket_status<<endl;
			//if (tls_connect_socket_status != 0){cout<<" tls_error(tls)"<<tls_error(tls)<<endl; exit(-1);}
			if (tls_connect_socket_status != 0){cout<<" tls_error(tls)"<<tls_error(tls)<<endl;}

			string bc_command;
			//bc_command = "set block to bc_server### " + blocks_from_db + "###@###\r\n";
			bc_command = "set block to peer ### " + blocks_from_db + "###@###\r\n";

			cout<<"bc_command#"<<bc_command<<"#"<<endl;
			int tls_write_status = 666;
			tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
			if (tls_write_status == -1){cout<<"tls_write_status TLS Error send_peer_local_chain_longer_and_send_blocks.cpp# "<<tls_error(tls)<<endl;exit(-1);}
			

//			//Sende Exit Command für "validate_chains_peer_local_with_remote_ip_only.cpp" -> exit_validate_chains_peer_local_with_remote_ip_only_cpp = true
//			//Notwendig für "out of range" in validate_chains_peer_local_with_remote_ip_only_cpp Zeile 263
//			//bc_command = "exit_validate_chains_peer_local_with_remote_ip_only_cpp " + exit_validate_chains_peer_local_with_remote_ip_only_cpp + " \r\n";
//			bc_command = "exit_validate_chains_peer_local_with_remote_ip_only_cpp\r\n";
//			cout<<"SENDE exit_validate_chains_peer_local_with_remote_ip_only_cpp"<<endl;
//			
//			tls_write_status = 666;
//			tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));

			
//close(s12);
//tls_close(tls);
//tls_free(tls);
//tls_config_free(config);

		}	

//##################################################################################################################################
//##################################################################################################################################
//##################################################################################################################################


		
		
	}
	
*/			
cout<<"ENDE"<<endl;
//cout<<"getchar();"<<endl;getchar();
}