//clear; rm -frv get_last_block.o; g++-7 -g -fPIC -Wall -c get_last_block.cpp

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

extern string vorhandene_ketten;
extern string last_block_chain_id;
extern string previous_hash_block;
extern vector<string> config_file_parameter;

void get_last_block()
{
	//cout<<"get_last_block.cpp"<<endl;
	//cout<<"\e[1m"<<"get_last_block.cpp"<<"\e[0m"<<endl;
	
//####################################################################
//Debug to File by sap_bcc.cpp
//ofstream debug_file_2;
//debug_file_2.open ("/tmp/blockchain_daemon.cpp_debug_file.log", ios::app );
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

	//##############################################################################################################################
	//GET CHAIN SIZE . GGF deaktivieren da nur Block 0 angefortert wird
		//Netzwerkverbidnung definieren####
		string bc_peer_1;
	//string bc_peer_port_1 = "8888";
	string bc_peer_port_1 = config_file_parameter[1];
	//bc_peer_1 = "172.17.190.84";
	bc_peer_1 = config_file_parameter[0];
	
	struct hostent *host_1;//Hostname struktuieren
	host_1 = gethostbyname(bc_peer_1.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_1;
	addr_1.sin_addr = *(struct in_addr*)host_1->h_addr;
	int s1; 
	s1 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_1 = atoi(bc_peer_port_1.c_str());
	addr_1.sin_port = htons(bc_peer_port_int_1);//Connection Portnummer des Servers festlegen
	addr_1.sin_family = AF_INET;
	
	//bc_server Time Out über config file steuern
	struct timeval timeout;
	timeout.tv_sec  = 30;
	timeout.tv_usec = 0;
	setsockopt (s1, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
	setsockopt (s1, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

	int connect_status_1;
	connect_status_1 = 666;
	connect_status_1 = connect(s1,(struct sockaddr*)&addr_1, sizeof(addr_1));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
	if (connect_status_1 == -1)
	{
		cout<<"Socket error auf der Gegenseite get_last_block.cpp# "<<connect_status_1<<endl;
		exit(-1);
	}
	string bc_command_1;
	bc_command_1 = "get chain size\r\n";
	//cout<<"REMOTE block_nummer#"<<block_nummer<<endl;
	//cout<<"bc_command_1#"<<bc_command_1<<endl;
	
	int tls_connect_socket_status = 666;
	tls_connect_socket_status = tls_connect_socket(tls, s1, "localhost");
	//cout<<"tls_connect_socket_status#"<<tls_connect_socket_status<<endl;
	//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;

	//send(s1, bc_command_1.c_str(), bc_command_1.length(),0);//Daten senden
	int tls_write_status = 666;
	tls_write_status = tls_write(tls, bc_command_1.c_str(), strlen(bc_command_1.c_str()));
	//cout<<"tls_write_status#"<<tls_write_status<<endl;

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
			//bytes_1 = tls_read(tls, response_1, 1000);
			//cout<<"bytes_1#"<<bytes_1<<endl;
			//cout<<"response_1#"<<response_1<<endl;

			//bytes_1 = recv(s1, response_1, sizeof(response_1), 0);
			//if ( bytes_1 = recv(s1, response_1, sizeof(response_1), 0) != 0 );
			//if ( bytes_1 = recv(s1, response_1, sizeof(response_1), 0) != NULL );
			if ( bytes_1 = tls_read(tls, response_1, sizeof(response_1)) != NULL );
			{
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
				if (bytes_1 <= 1024)
				{	
					close(s1);
					ende_1 = false;
				}
				if (bytes_1 == 1024)
				{	
					close(s1);
					ende_1 = false;
				}
				if (bytes_1 < 1024)
				{	
					close(s1);
					ende_1 = false;
				}
				response_temp_1.append(response_1);
				//cout<<"redis Datensätze auf BC_SERVER#"<<response_1<<"#"<<endl;
				//cout<<"bytes_1#"<<bytes_1<<endl;
				//cout<<"response_1#"<<response_1<<endl;

			}

		}
	close(s1);
	bzero (response_1, sizeof(response_1));
	tls_close(tls);
	tls_free(tls);
	tls_config_free(config);
	
	//cout<<"redis Datensätze in BC-SERVER #"<<response_temp_1<<"#"<<endl;
	
	//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db#"<<blocks_from_db<<endl;
	//response_temp_1 = response_temp_1.substr(1,response_temp_1.length());
	
	try{response_temp_1 = response_temp_1.substr(1,response_temp_1.length());}catch( std::out_of_range& exception ){cout<<"Error get_last_block.cpp response_temp_1 z.190 std::out_of_range"<<endl;}

	//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db#"<<blocks_from_db<<endl;
	//unsigned long long anzahl_lokaler_ketten_long = stoll(response_temp_1);
	unsigned long long anzahl_lokaler_ketten_long;
	try{anzahl_lokaler_ketten_long = stoll(response_temp_1);}catch(std::invalid_argument& exception){cout<<"Error get_last_block.cpp anzahl_lokaler_ketten_long stoll invaild argument z.197"<<endl;exit(-1);}
	//cout<<"anzahl_lokaler_ketten_long#"<<anzahl_lokaler_ketten_long<<endl;

//##############################################################################################################################
//GET SINGLE BLOCK bzw. den letzten Block anhand der Kettenlänge


	//TLS Initialisierung################################
	//gnuTLS Initilisieren
	int tls_init_status_2 = 666;
	tls_init_status_2 = tls_init();
	//cout<<"tls_init_status_2#"<<tls_init_status_2<<endl;
	//###
	struct tls *tls2 = NULL;
	tls2 = tls_client();
	//cout<<"tls_client#"<<tls<<endl;
	//###
	struct tls_config *config2 = NULL;
	config2 = tls_config_new();
	//cout<<"tls_config_new2#"<<config<<endl;
	//###
	tls_config_insecure_noverifycert(config2);
	tls_config_insecure_noverifyname(config2);
	tls_configure(tls2, config2);
	//##################################################

	string bc_peer_2;
	//string bc_peer_port_2 = "8888";
	//bc_peer_2 = "172.17.190.84";							//BC-Server . aus config lesen
	string bc_peer_port_2 = config_file_parameter[1];
	bc_peer_2 = config_file_parameter[0];
	struct hostent *host_2;//Hostname struktuieren
	host_2 = gethostbyname(bc_peer_2.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_2;
	addr_2.sin_addr = *(struct in_addr*)host_2->h_addr;
	int s2; 
	s2 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_2 = atoi(bc_peer_port_2.c_str());
	addr_2.sin_port = htons(bc_peer_port_int_2);//Connection Portnummer des Servers festlegen
	addr_2.sin_family = AF_INET;
	
	//struct timeval timeout;
	timeout.tv_sec  = 10;
	timeout.tv_usec = 0;
	setsockopt (s2, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
	setsockopt (s2, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

	int connect_status_2;
	connect_status_2 = 666;
	connect_status_2 = connect(s2,(struct sockaddr*)&addr_2, sizeof(addr_2));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status_2 == -1)
		{
			cout<<"Socket error auf der Gegenseite get_last_block.cpp# "<<connect_status_2<<endl;
			exit(-1);
		}
	string bc_command_2;
	string block_nummer;
		stringstream strstream;
		strstream << anzahl_lokaler_ketten_long;
		strstream >> block_nummer;
	//bc_command_2 = "get single block " + block_nummer + "\r\n";
	bc_command_2 = "get single block 0\r\n";							//Letzter Block in Kette
	//cout<<"bc_command_2#"<<bc_command_2<<endl;

	int tls_connect_socket_status_2 = 666;
	tls_connect_socket_status_2 = tls_connect_socket(tls2, s2, "localhost");
	//cout<<"tls_connect_socket_status_2#"<<tls_connect_socket_status_2<<endl;
	if (tls_connect_socket_status_2 == -1){cout<<"tls problem#"<<tls_error(tls2)<<"#"<<endl;exit(-1);}

	//send(s2, bc_command_2.c_str(), bc_command_2.length(),0);//Daten senden
	int tls_write_status_2 = 666;
	tls_write_status_2 = tls_write(tls2, bc_command_2.c_str(), strlen(bc_command_2.c_str()));
	//cout<<"tls_write_status_2#"<<tls_write_status_2<<endl;
	if (tls_write_status_2 == -1){cout<<"TLS Schreib Problem MINUS EINS#"<<tls_error(tls2)<<"#"<<endl; exit(-1);}
	if (tls_write_status_2 == -2){cout<<"TLS Schreib Problem MINUS ZWEI#"<<tls_error(tls2)<<"#"<<endl; exit(-1);}
	
//char response_2[1024];//Empfangspuffer festlegen
char response_2[999999];//Empfangspuffer festlegen
	//int bytes_2 = -1 ; 
	ssize_t bytes_2 = 0;
	string antwort_ausgabe_2;
	bool ende_2 = true;
	bzero (response_2, sizeof(response_2));
	string response_temp_2;
	response_temp_2 = "";
	while(ende_2)
		{
			//Alte Socket API recv() Funktion
			//bytes_2 = recv(s2, response_2, sizeof(response_2), 0);
			//if ( bytes_2 = recv(s2, response_2, sizeof(response_2), 0) != 0 );
			//if ( bytes_2 = recv(s2, response_2, sizeof(response_2), 0) != NULL );
			//cout<<"tls_read im gange"<<endl;
			//cout<<"response_2#"<<response_2<<endl;
			//TLS tls_read() funktion
			bytes_2 = tls_read(tls2, response_2, sizeof(response_2));
			//cout<<"bytes_2#"<<bytes_2<<endl;
			response_temp_2.append(response_2);
			//if ( bytes_2 = tls_read(tls, response_2, sizeof(response_2)) != NULL );
			//if ( bytes_2 = tls_read(tls, response_2, sizeof(response_2)) != NULL);
			//if (bytes_2 = tls_read(tls, response_2, sizeof(response_2)) <= 0) break;
			//if ( bytes_2 = tls_read(tls, response_2, sizeof(response_2)) != 0);
			//if ( tls_read(tls, response_2, sizeof(response_2)) != NULL);
			//if ( tls_read(tls, response_2, sizeof(response_2)) != 0);
			//if (bytes_2 = tls_read(tls, response_2, sizeof(response_2)) <= 0);
			//{
				//cout<<"bytes_2#"<<bytes_2<<endl;
				//cout<<"response_2#"<<response_2<<endl;
				if (bytes_2 == 0)
				{	
					close(s2);
					ende_2 = false;
					//cout<<"CLOSE == 0"<<endl;
					bzero (response_2, sizeof(response_2));					
				}
				if (bytes_2 == -1)
				{	
					close(s2);
					ende_2 = false;
					//cout<<"CLOSE == -1"<<endl;
					bzero (response_2, sizeof(response_2));
				}
				//if (bytes_2 <= 1024)
				//{	
				//	close(s2);
				//	ende_2 = false;
				//}
				//if (bytes_2 == 1024)
				//{	
				//	close(s2);
				//	ende_2 = false;
				//}
				if (bytes_2 < 999999)
				{	
					close(s2);
					ende_2 = false;
					//cout<<"CLOSE < 999999"<<endl;
					bzero (response_2, sizeof(response_2));
				}
				//response_temp_2.append(response_2);
				//debug_file_2<<"response_temp_2 in get_last_block.cpp#"<<response_temp_2<<"#"<<endl;
				//cout<<"redis LETZTER Datensätze auf BC_SERVER response_2#"<<response_2<<"#"<<endl;
				bzero (response_2, sizeof(response_2));
			//}
		}
		
	close(s2);
	bzero (response_2, sizeof(response_2));
	tls_close(tls2);
	tls_free(tls2);
	tls_config_free(config2);
	
	//cout<<"redis LETZTER Datensätze auf BC_SERVER#"<<response_temp_2<<"#"<<endl;
	//debug_file_2<<"response_temp_2 in get_last_block.cpp#"<<response_temp_2<<"#"<<endl;
	vorhandene_ketten = response_temp_2;

//###########################################################################################################################	
//ID und Previous Hash filtern
//Filter ID und hash######################
	
	//Filter last ID
	string block_chain_id, hash, last_block_id;
	int finde_gatter;
	
	//bc-id: 555 # timestamp: 16.09.2018 16:30:30.307151371 # data: Transaktion 4 , 50€ an Alex # prevoius_hash_bc-id 3: 2ee034b218c32646dfa1020d93cc2c2155237c8ab0b779889825dce44fdca61ad0ac1d5c9a368ffeb1a42cc5133066db0681145f7f633bc15dc94f4e029ef2ef # hash_block_4: abb81850d8dd577b
	finde_gatter = vorhandene_ketten.find("#");
	
	//cout<<"finde_gatter#"<<finde_gatter<<endl;
	
	//last_block_id = vorhandene_ketten.substr(0, finde_gatter);
	try{last_block_id = vorhandene_ketten.substr(0, finde_gatter);}catch( std::out_of_range& exception ){cout<<"Error get_last_block.cpp last_block_id z.364 std::out_of_range"<<endl;}

	//cout<<"last_block_id#"<<last_block_id<<endl;
	
	int finde_string_bc_id;
	finde_string_bc_id = last_block_id.find("bc-id:");
	
	//last_block_id = last_block_id.substr(finde_string_bc_id + 7, 999);
	//if(finde_string_bc_id != 1){last_block_id = last_block_id.substr(finde_string_bc_id + 7, 999);}else{cout<<"PROBLEM in get_last_block.cpp last_block_id z. 365 "<<endl;}
	try{last_block_id = last_block_id.substr(finde_string_bc_id + 7, 999);}catch( std::out_of_range& exception ){cout<<"PROBLEM in get_last_block.cpp last_block_id z. 373 "<<endl;}

	//cout<<"last_block_id#"<<last_block_id<<endl;

	last_block_id = last_block_id.erase(last_block_id.find_last_not_of(" ")+1);
	//cout<<"last_block_id#"<<last_block_id<<endl;
	last_block_chain_id = last_block_id;
	
	
	//Filter Hash
	int finde_string_hash_block_id;
	
	//hash_block_<Block-ID-Nummer>
	string suchstrig = "hash_block " + last_block_id + ":";
	//cout<<"suchstrig#"<<suchstrig<<"#"<<endl;

	finde_string_hash_block_id = vorhandene_ketten.find(suchstrig);
	//cout<<"finde_string_hash_block_id#"<<finde_string_hash_block_id<<endl;

	//previous_hash_block = vorhandene_ketten.substr(finde_string_hash_block_id + suchstrig.length() + 1, 128);
	//if(finde_string_hash_block_id != -1){previous_hash_block = vorhandene_ketten.substr(finde_string_hash_block_id + suchstrig.length() + 1, 128);}else{cout<<"PROBLEM in get_last_block.cpp previous_hash_block z. 365 "<<endl;}
	try{previous_hash_block = vorhandene_ketten.substr(finde_string_hash_block_id + suchstrig.length() + 1, 128);}catch( std::out_of_range& exception ){cout<<"PROBLEM in get_last_block.cpp previous_hash_block z. 3394 "<<endl;}
	
	//cout<<"previous_hash_block in get_last_block.cpp#"<<previous_hash_block<<endl;
	

//###################################################
//Debug file schliesen.
//debug_file_2.close();
//###################################################
//cout<<"ENDE"<<endl;
}
