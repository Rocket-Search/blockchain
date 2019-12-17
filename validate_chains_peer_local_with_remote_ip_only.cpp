//clear; rm -frv  validate_chains_peer_local_with_remote_ip_only.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local_with_remote_ip_only.cpp

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

//extern vector<string> erreichbare_peers;
extern string remote_ip;
//compare_blocks_peer_local();
extern string local_block;
extern string peer_block;
extern string block_nummer;
extern bool compare_blocks_peer_local_bool;
//Public Variablen für Object Files
//compare_hashes_single_peer_local()
extern bool compare_hashes_local;
extern bool compare_hashes_peer;
//write_to_db();
extern string write_block_to_db;
extern vector<string> config_file_parameter;
extern bool exit_validate_chains_peer_local_with_remote_ip_only_cpp;
extern unsigned long long local_kette_laenge;
extern int remote_kettten_laenge;
string remote_letzter_block;

void validate_chains_peer_local_with_remote_ip_only()
{
//BSP. Kette auf 172.17.190.84 ist länger als auch 172.17.190.78

	//cout<<"\e[1m"<<"validate_chains_peer_local_with_remote_ip_only.cpp"<<"\e[0m"<<endl;
	//cout<<"validate_chains_peer_local_with_remote_ip_only.cpp"<<endl;
	//cout<<"extern remote_ip#"<<remote_ip<<endl;
	//cout<<"Validiere beide Ketten bis zum Punkt an dem die remote Kette länger ist"<<endl;
	//Alle Blöcke von remote ip empfanfen bis kette remot elänger

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
	bc_peer = remote_ip;
	//bc_peer = "172.17.190.86";
	//cout<<"Hole Blöcke von remote_ip zur validierung #"<<remote_ip<<endl;
	//cout<<"local_kette_laenge#"<<local_kette_laenge<<endl;
	//cout<<"remote_kettten_laenge#"<<remote_kettten_laenge<<endl;

//#######################################################################################################################################################
//Remote Ketten Länger herausfinden######################################################################################################################

	struct hostent *host;//Hostname struktuieren
	host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr;
	addr.sin_addr = *(struct in_addr*)host->h_addr;
	int s6 = 666; 
	s6 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	//cout<<"socket s6#"<<s6<<endl;
	int bc_peer_port_int = atoi(bc_peer_port.c_str());
	addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
	addr.sin_family = AF_INET;
	int connect_status;
	connect_status = 666;
	connect_status = connect(s6,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
	//cout<<"connect_status validate_chains_peer_local_with_remote_ip_only.cpp #"<<connect_status<<endl;
	//string cin_input;
	//cin>>cin_input;
	//cout<<cin_input;
	if (connect_status == -1)
	{
		cout<<"Socket error auf der Gegenseite 1 return# "<<connect_status<<endl;
		exit(-1);
		//return;
	}
	//cout<<"getchar()"<<endl;getchar();
	int tls_connect_socket_status = 666;
	tls_connect_socket_status = tls_connect_socket(tls, s6, "localhost");
	//cout<<"tls_connect_socket_status in validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls_connect_socket_status<<endl;
	//if (tls_connect_socket_status != 0){cout<<" tls_error(tls)"<<tls_error(tls)<<endl; exit(-1);}
	if (tls_connect_socket_status != 0){cout<<"tls_connect_socket_status tls_error(tls)"<<tls_error(tls)<<endl;exit(-1);}
	//cout<<"getchar()"<<endl;getchar();

	//An Peer Senden das unsere ketten länger sind 
	//und Peer veranlassen unsere Ketten zu laden, nach vlaidierung
	string bc_command;
	bc_command = "get chain size\r\n";
	//cout<<"bc_command#"<<bc_command<<"#"<<endl;
	//cout<<"getchar()"<<endl;getchar();
	//send(s6, bc_command.c_str(), bc_command.length(),0);//Daten senden

	int tls_write_status = 666;
	tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
	//cout<<"tls_write_status validate_chains_peer_local_with_remote_ip_only.cpp 1#"<<tls_write_status<<endl;
	//cout<<"getchar()"<<endl;getchar();
	//if (tls_write_status == -1){cout<<"TLS Error"<<tls_error(tls)<<endl; getchar();}
	//if (tls_write_status == -1){cout<<"TLS Error# "<<tls_error(tls)<<endl;}
	if (tls_write_status == -1){cout<<"tls_write_status TLS Error# "<<tls_error(tls)<<endl;exit(-1);}
	//cout<<"getchar()"<<endl;getchar();
	//cout<<"s#"<<s6<<endl;
	//Empfange Ketten größe
	char response[1024];//Empfangspuffer festlegen
	//int bytes;
	ssize_t bytes = 0;	
	//string antwort_ausgabe;
	bool ende = true;
	bzero (response, sizeof(response));
	string response_temp;
	//response_temp = "";

	while(ende)
	{
		//bytes = recv(s6, response, sizeof(response), 0);

		bytes = tls_read(tls, response, sizeof(response));
		response_temp.append(response);
		
		bzero (response, sizeof(response));
		
		if (bytes == 0)
		{	
			close(s6);
			ende = false;
		}
		if (bytes == -1)
		{	
			close(s6);
			ende = false;
		}
		if (bytes < 1024)
		{	
			close(s6);
			ende = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
				
		//response_temp.append(response);
		//cout<<"Remote Kettenlänge response#"<<response<<"#"<<endl;
	}
	close(s6);

	bzero (response, sizeof(response));

	//cout<<"Remote Kettenlänge response#"<<response_temp<<"#"<<endl;

	tls_close(tls);
	tls_free(tls);
	tls_config_free(config);

	//cout<<"Remote Kettenlänge response in validate_chains_peer_local_with_remote_ip_only.cpp#"<<response_temp<<"#"<<endl;
	string remote_ketten_laenge = response_temp;
response_temp = "";
//string test123; cout<<"CIN"<<endl; cin>>test123;
//#######################################################################################################################################################

//Anzahle der erhaltenden kette bis zur Nummer der größeren valideren und die letzten ketten von Peer/Zugreiffer laden.

	//lokale Ketten Länge ermitteln
	string bc_peer_2;
	//string bc_peer_port_2 = "6379";
	string bc_peer_port_2 = config_file_parameter[3];
	//bc_peer_2 = "127.0.0.1";
	bc_peer_2 = config_file_parameter[2];
	struct hostent *host_2;//Hostname struktuieren
	host_2 = gethostbyname(bc_peer_2.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_2;
	addr_2.sin_addr = *(struct in_addr*)host_2->h_addr;
	int s7; 
	s7 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_2 = atoi(bc_peer_port_2.c_str());
	addr_2.sin_port = htons(bc_peer_port_int_2);//Connection Portnummer des Servers festlegen
	addr_2.sin_family = AF_INET;
	int connect_status_2;
	connect_status_2 = 666;
	connect_status_2 = connect(s7,(struct sockaddr*)&addr_2, sizeof(addr_2));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
	if (connect_status_2 == -1)
	{
		cout<<"Socket error auf der Gegenseite# "<<connect_status_2<<endl;
		exit(-1);
	}

	string bc_command_2;
	bc_command_2 = "LLEN blockchain_list\r\n";
	//cout<<"bc_command_2#"<<bc_command_2<<endl;
	send(s7, bc_command_2.c_str(), bc_command_2.length(),0);//Daten senden
	char response_2[1024];//Empfangspuffer festlegen
	int bytes_2; 
	string antwort_ausgabe_2;
	bool ende_2 = true;
	bzero (response_2, sizeof(response_2));
	string response_temp_2;
	response_temp_2 = "";

	while(ende_2)
		{
			//bytes_2 = recv(s7, response_2, sizeof(response_2), 0);
			//if ( bytes_2 = recv(s7, response_2, sizeof(response_2), 0) != 0 );
			if ( bytes_2 = recv(s7, response_2, sizeof(response_2), 0) != NULL );
			{
				if (bytes_2 == 0)
				{	
					close(s7);
					ende_2 = false;
					
				}
				if (bytes_2 == -1)
				{	
					close(s7);
					ende_2 = false;
				}
				if (bytes_2 <= 1024)
				{	
					close(s7);
					ende_2 = false;
				}
				response_temp_2.append(response_2);
				//cout<<"redis Datensätze LOKAL in while#"<<response_2<<"#"<<endl;
			}
		}
	close(s7);
	//cout<<"redis Datensätze LOKAL#"<<response_temp_2<<"#"<<endl;

	//Validate Chains
	//cout<<"Validiere Blocks bis zum Fehlenden Block"<<endl;
	//ketten Anzahl in "unsigend long long" umwandeln
	unsigned long long anzahl_ketten_lokal ;
	//cout<<"response"<<response<<endl;
	string anzahl_ketten_lokal_string = response_temp_2;
	//anzahl_ketten_lokal_string = anzahl_ketten_lokal_string.substr(1,anzahl_ketten_lokal_string.length());
	try{anzahl_ketten_lokal_string = anzahl_ketten_lokal_string.substr(1,anzahl_ketten_lokal_string.length());}catch( std::out_of_range& exception ){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp anzahl_ketten_lokal_string std::out_of_range"<<endl;}

	//cout<<"anzahl_ketten_lokal_string#"<<anzahl_ketten_lokal_string<<endl;
	//anzahl_ketten_lokal =  stoll(anzahl_ketten_lokal_string.c_str());
	try{anzahl_ketten_lokal =  stoll(anzahl_ketten_lokal_string.c_str());}catch(std::invalid_argument& exception){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp anzahl_ketten_lokal stoll invaild argument z254"<<endl;exit(-1);}

	//cout<<"unsigned long long # anzahl_ketten_lokal#"<<anzahl_ketten_lokal<<endl;

	unsigned long long anzahl_ketten_remote ;
	//remote_ketten_laenge = remote_ketten_laenge.substr(1,remote_ketten_laenge.length());
	//cout<<"remote_ketten_laenge#"<<remote_ketten_laenge<<"#"<<endl;

	//#########################	
	//Notwendig da die Ketten nicht länger sind als auf dem Peer und es zu einem "out of range" kommt
	//prüfe auf exit_validate_chains_peer_local_with_remote_ip_only_cpp = true
	//cout<<"exit_validate_chains_peer_local_with_remote_ip_only_cpp#"<<exit_validate_chains_peer_local_with_remote_ip_only_cpp<<endl;

	if (exit_validate_chains_peer_local_with_remote_ip_only_cpp == true)
		{
			//cout<<"Keine Valdidierung weiter notwendig da die Ketten von remote kommen"<<endl;
			exit_validate_chains_peer_local_with_remote_ip_only_cpp = false;
			//Exit Object File only
			//exit(-1);
			//exit(0);
			terminate();
			//return(0);
			//abort();
		}

	//try{remote_ketten_laenge = remote_ketten_laenge.substr(1,remote_ketten_laenge.length());}catch( std::out_of_range& exception ){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp remote_ketten_laenge std::out_of_range"<<endl;exit(-1);}
	try{remote_ketten_laenge = remote_ketten_laenge.substr(1,remote_ketten_laenge.length());}catch( std::out_of_range& exception ){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp remote_ketten_laenge std::out_of_range"<<endl;}

	//try{anzahl_ketten_remote = stoll(remote_ketten_laenge);}catch(std::invalid_argument& exception){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp anzahl_ketten_remote stoll invaild argument"<<endl;exit(-1);}
	try{anzahl_ketten_remote = stoll(remote_ketten_laenge);}catch(std::invalid_argument& exception){cout<<"Error validate_chains_peer_local_with_remote_ip_only.cpp anzahl_ketten_remote stoll invaild argument"<<endl;}
	//#########################

	//cout<<"anzahl_ketten_remote LONG LONG#"<<anzahl_ketten_remote<<endl;

	unsigned long long offset_fuer_lokal_redis_id ;
	unsigned long long offset_fuer_lokal_redis_id_temp ;
	//signed long long offset_fuer_lokal_redis_id ;
	//signed long long offset_fuer_lokal_redis_id_temp ;
	offset_fuer_lokal_redis_id = anzahl_ketten_remote - anzahl_ketten_lokal;
	//cout<<"offset_fuer_lokal_redis_id#"<<offset_fuer_lokal_redis_id<<endl;

//cout<<"Remote Peer Zugreifer#"<<bc_peer<<endl;
//cout<<"Remote Datensätze#"<<response_temp<<endl;
//cout<<"remote_ketten_laenge#"<<remote_ketten_laenge<<endl;
	
//string remote_letzter_block;

//Nun alle Blöcke durchgegehn bzw. alle lokalen blöcke, da die remote kette ja länger ist#######################
	for (unsigned long long i = 0; i < anzahl_ketten_remote; i++)
//for (unsigned long long i = 0; i < anzahl_ketten_lokal; i++)			//Funktioniert für das Vergleichen
	//for (unsigned long long i = 1; i < anzahl_ketten_lokal; i++)
	//for (unsigned long long i = anzahl_ketten_lokal; i > 0 ; i--)
	{
	//Remote Blöcke laden . get singel block nummer i
	//cout<<"i#"<<i<<endl;
	string bc_peer_3;
//Erstes i merken für späteren einsiegtspunkt beim l
	
	//TLS Initialisierung################################
	//gnuTLS Initilisieren
	int tls_init_status2 = 666;
	tls_init_status2 = tls_init();
	//cout<<"tls_init_status validate_chains_peer_local_with_remote_ip_only.cpp 2 #"<<tls_init_status2<<endl;
	//###
	struct tls *tls2 = NULL;
	tls2 = tls_client();
	//cout<<"tls_client validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls2<<endl;
	//###
	struct tls_config *config2 = NULL;
	config2 = tls_config_new();
	//cout<<"tls_config_new validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<config2<<endl;
	//###
	tls_config_insecure_noverifycert(config2);
	tls_config_insecure_noverifyname(config2);
	tls_configure(tls2, config2);
	//##################################################
			
	//string bc_peer_port_3 = "8888";
	string bc_peer_port_3 = config_file_parameter[1];
	bc_peer_3 = bc_peer;
	struct hostent *host_3;//Hostname struktuieren
	host_3 = gethostbyname(bc_peer_3.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_3;
	addr_3.sin_addr = *(struct in_addr*)host_3->h_addr;
	int s8; 
	s8 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_3 = atoi(bc_peer_port_3.c_str());
	addr_3.sin_port = htons(bc_peer_port_int_3);//Connection Portnummer des Servers festlegen
	addr_3.sin_family = AF_INET;
	int connect_status_3;
	connect_status_3 = 666;
	connect_status_3 = connect(s8,(struct sockaddr*)&addr_3, sizeof(addr_3));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status_3 == -1)
		{
			cout<<"Socket error auf der Gegenseite connect_status_3 2#"<<connect_status_3<<endl;
			exit(-1);
		}

	int tls_connect_socket_status2 = 666;
	tls_connect_socket_status2 = tls_connect_socket(tls2, s8, "localhost");
	//cout<<"tls_connect_socket_status in validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls_connect_socket_status2<<endl;
	//if (tls_connect_socket_status2 != 0){cout<<" tls_error(tls) in validate_chains_peer_local_with_remote_ip_only.cpp "<<tls_error(tls2)<<endl; exit(-1);}
	if (tls_connect_socket_status2 != 0){cout<<" tls_connect_socket_status2 tls_error(tls) in validate_chains_peer_local_with_remote_ip_only.cpp "<<tls_error(tls2)<<endl;}

	string bc_command_3;
	string block_nummer;
unsigned long long i_temp = - 1;
i_temp = anzahl_ketten_remote - anzahl_ketten_lokal + i;
//cout<<"remote offset i_temp"<<i_temp<<endl;
		stringstream strstream;
		strstream << i_temp;
		strstream >> block_nummer;
	bc_command_3 = "get single block " + block_nummer  + "\r\n";
//cout<<"REMOTE block_nummer#"<<block_nummer<<endl;
	//send(s8, bc_command_3.c_str(), bc_command_3.length(),0);//Daten senden

	int tls_write_status2 = 666;
	tls_write_status2 = tls_write(tls2, bc_command_3.c_str(), strlen(bc_command_3.c_str()));
	//cout<<"tls_write_status2 validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls_write_status2<<endl;
	if (tls_write_status2 == -1){cout<<"tls_write_status2 TLS Error# "<<tls_error(tls2)<<endl;exit(-1);}
	
	//close(s8);tls_close(tls2);tls_free(tls2);tls_config_free(config2);getchar();}/*

	char response_3[999999];//Empfangspuffer festlegen
	//int bytes_3;
	ssize_t bytes_3 = 0;		
	string antwort_ausgabe_3;
	bool ende_3 = true;
	bzero (response_3, sizeof(response_3));
	string response_temp_3;
	response_temp_3 = "";
	while(ende_3)
		{
			//bytes_3 = recv(s8, response_3, sizeof(response_3), 0);
			//if ( bytes_3 = recv(s8, response_3, sizeof(response_3), 0) != 0 );
			//if ( bytes_3 = recv(s8, response_3, sizeof(response_3), 0) != NULL );
			if (bytes_3 = tls_read(tls2, response_3, sizeof(response_3)) != NULL );
			{
				if (bytes_3 == 0)
				{	
					close(s8);
					ende_3 = false;
					
				}
				if (bytes_3 == -1)
				{	
					close(s8);
					ende_3 = false;
				}
				if (bytes_3 <= 999999)
				{	
					close(s8);
					ende_3 = false;
				}
				response_temp_3.append(response_3);
				//cout<<"redis Datensätze LOKAL in while#"<<response_3<<"#"<<endl;
			}
		}
	close(s8);
	
	tls_close(tls2);
	tls_free(tls2);
	tls_config_free(config2);

	//cout<<"REMOTE BLOCK validate_chains_peer_local_with_remote_ip_only#"<<response_temp_3<<"#"<<endl;
	//cout<<"REMOTE BLOCK #"<<response_temp_3<<"#"<<endl;
if (i == 0)
{
	//string remote_letzter_block;
	remote_letzter_block = response_temp_3;
}
	//Lokale Blöcke Laden####################
		string bc_peer_4;
		//string bc_peer_port_4 = "6379";
		string bc_peer_port_4 = config_file_parameter[3];
		//bc_peer_4 = "127.0.0.1";
		bc_peer_4 = config_file_parameter[2];
		struct hostent *host_4;//Hostname struktuieren
		host_4 = gethostbyname(bc_peer_4.c_str()); //eventuell die IP in DNS Namen umwandeln
		struct sockaddr_in addr_4;
		addr_4.sin_addr = *(struct in_addr*)host_4->h_addr;
		int s9; 
		s9 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		int bc_peer_port_int_4 = atoi(bc_peer_port_4.c_str());
		addr_4.sin_port = htons(bc_peer_port_int_4);//Connection Portnummer des Servers festlegen
		addr_4.sin_family = AF_INET;
		int connect_status_4;
		connect_status_4 = 666;
		connect_status_4 = connect(s9,(struct sockaddr*)&addr_4, sizeof(addr_4));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
			if (connect_status_4 == -1)
			{
				//cout<<"Socket error auf der Gegenseite# "<<connect_status_4<<endl;
				//exit(-1);
			}

//offset_fuer_lokal_redis_id_temp = i - offset_fuer_lokal_redis_id;
//offset_fuer_lokal_redis_id_temp = offset_fuer_lokal_redis_id - i;
offset_fuer_lokal_redis_id_temp = i;
//cout<<"offset_fuer_lokal_redis_id_temp#"<<offset_fuer_lokal_redis_id_temp<<endl;
string bc_command_4;
string block_nummer_4;
stringstream strstream_4;
strstream_4 << offset_fuer_lokal_redis_id_temp;
strstream_4 >> block_nummer_4;
bc_command_4 = "LINDEX blockchain_list " + block_nummer_4 + "\r\n";
//cout<<"bc_command_4#"<<bc_command_4<<endl;

		send(s9, bc_command_4.c_str(), bc_command_4.length(),0);//Daten senden
		char response_4[999999];//Empfangspuffer festlegen
		int bytes_4; 
		string antwort_ausgabe_4;
		bool ende_4 = true;
		bzero (response_4, sizeof(response_4));
		string response_temp_4;
		response_temp_4 = "";
		while(ende_4)
			{
				//bytes_4 = recv(s9, response_4, sizeof(response_4), 0);
				//if ( bytes_4 = recv(s9, response_4, sizeof(response_4), 0) != 0 );
				if ( bytes_4 = recv(s9, response_4, sizeof(response_4), 0) != NULL );
				{
					if (bytes_4 == 0)
					{	
						close(s9);
						ende_4 = false;
					}
					if (bytes_4 == -1)
					{	
						close(s9);
						ende_4 = false;
					}
					//if (bytes_4 <= 999999)
					//{	
					//	close(s9);
					//	ende_4 = false;
					//}
					if (bytes_4 <= 999999)
					{	
						close(s9);
						ende_4 = false;
					}
					response_temp_4.append(response_4);
					//cout<<"redis Datensätze LOKAL in while#"<<response_4<<"#"<<endl;
				}
			}
		close(s9);
//cout<<"LOKAL BLOCK#"<<response_temp_4<<"#"<<endl;
	
		//Beider Blöcke validieren/comparen
		//int wo_ist_redis_err  = -1;
		//wo_ist_redis_err = response_temp_4.find("-ERR");
		//cout<<"wo_ist_redis_err#"<<wo_ist_redis_err<<endl;

		int wo_ist_dollar_minus_1 = -1;
		wo_ist_dollar_minus_1 = response_temp_4.find("$-1");
		//cout<<"wo_ist_dollar_minus_1#"<<wo_ist_dollar_minus_1<<endl;
		
		//if (wo_ist_redis_err == -1)
		//if ((response_temp_4 != "$-1") && (response_temp_3 != "$-1"))
		if (wo_ist_dollar_minus_1 == -1)
		{
			//Blöcke validieren
			//cout<<"IF wo_ist_redis_err#"<<wo_ist_redis_err<<endl;
		
//reiner Zeichensatzvergelich#########################################################
			local_block = response_4;
			peer_block = response_temp_3;
			block_nummer = block_nummer_4;			//Blocknummer LOKAL
			compare_blocks_peer_local_bool = false;
			void compare_blocks_peer_local();
			compare_blocks_peer_local();
			//cout<<"compare_blocks_peer_local_bool# "<<compare_blocks_peer_local_bool<<endl;
			if (compare_blocks_peer_local_bool == false)
			{
				cout<<"ZEICHENSATZ DES BLOCKS NICHT VALIDE, MANUELLE TÄTIGKEITEN NOTWENDIG!!!"<<endl;
				cout<<"local_block#"<<local_block<<endl;
				cout<<"peer_block#"<<" IP:"<<bc_peer<<" "<<peer_block<<endl;
				cout<<"block_nummer#"<<block_nummer_4<<endl;
				
				//PROGRAMM STOPPEN WENN EINE NICHT VALIDE KETTE GEFUNDEN WURDE!!!
				exit(-1);

			}
			else
			{
				//cout<<"LOKAL <-> REMOTE BLOCK GLEICH"<<endl;
				//cout<<"local_block#"<<local_block<<endl;
				//cout<<"peer_block#"<<" IP:"<<bc_peer<<" "<<peer_block<<endl;
				//cout<<"block_nummer#"<<block_nummer_4<<endl;
			}


//Hashes verhgleichen#########################################################
			local_block = response_4;
			compare_hashes_local = false;
			peer_block = response_temp_3;
			compare_hashes_peer =  false;
			void compare_hashes_single_peer_local();
			compare_hashes_single_peer_local();
			//cout<<"compare_hashes_local# "<<compare_hashes_local<<endl;
			//cout<<"compare_hashes_peer# "<<compare_hashes_peer<<endl;

			if (compare_hashes_local == false)
			{
				cout<<"HASH DES LOKALEN BLOCKS NICHT VALIDE, MANUELLE TÄTIGKEITEN NOTWENDIG!!!"<<endl;
				cout<<"local_block#"<<local_block<<endl;
				cout<<"block_nummer#"<<block_nummer_4<<endl;
				
				//PROGRAMM STOPPEN WENN EINE NICHT VALIDE KETTE GEFUNDEN WURDE!!!
				exit(-1);
			}
			if(compare_hashes_peer == false)
			{
				cout<<"HASH DES REMOTE BLOCKS NICHT VALIDE, MANUELLE TÄTIGKEITEN NOTWENDIG!!!"<<endl;
				cout<<"local_block#"<<peer_block<<endl;
				cout<<"block_nummer#"<<block_nummer<<endl;
				
				//PROGRAMM STOPPEN WENN EINE NICHT VALIDE KETTE GEFUNDEN WURDE!!!
				exit(-1);
			}
			
		}
		else
		{
			//cout<<"REMOTE BLOCK Nummer: "<<i<<" nicht LOKAL"<<endl;
			//Remote Block in RedisDB schreiben

//check_block_exists
//cout<<"response_temp_3"<<response_temp_3<<endl;
//cout<<"i #"<<i<<endl;

//###########################################
//for (unsigned long long j = anzahl_ketten_lokal ; j < anzahl_ketten_remote; j++)
//{
//cout<<"Temp Block Nummer#"<<j<<endl;

//Blöcke Anhand der Nummer von remote laden (get singele block)#################################################
	//cout<<"peer_block#"<<peer_block<<"#"<<endl;
	//
	//TLS Initialisierung################################
	//gnuTLS Initilisieren
	int tls_init_status3 = 666;
	tls_init_status3 = tls_init();
	//cout<<"tls_init_status validate_chains_peer_local_with_remote_ip_only.cpp 2 #"<<tls_init_status2<<endl;
	//###
	struct tls *tls3 = NULL;
	tls3 = tls_client();
	//cout<<"tls_client validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls2<<endl;
	//###
	struct tls_config *config3 = NULL;
	config3 = tls_config_new();
	//cout<<"tls_config_new validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<config2<<endl;
	//###
	tls_config_insecure_noverifycert(config3);
	tls_config_insecure_noverifyname(config3);
	tls_configure(tls3, config3);
	//##################################################
	//string bc_peer_port_3 = "8888";
	string bc_peer_port_4 = config_file_parameter[1];
	bc_peer_4 = bc_peer;
	struct hostent *host_4;//Hostname struktuieren
	host_4 = gethostbyname(bc_peer_4.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_4;
	addr_4.sin_addr = *(struct in_addr*)host_4->h_addr;
	int s15; 
	s15 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_3 = atoi(bc_peer_port_4.c_str());
	addr_4.sin_port = htons(bc_peer_port_int_3);//Connection Portnummer des Servers festlegen
	addr_4.sin_family = AF_INET;
	int connect_status_4;
	connect_status_4 = 666;
	connect_status_4 = connect(s15,(struct sockaddr*)&addr_4, sizeof(addr_4));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status_4 == -1)
		{
			cout<<"Socket error auf der Gegenseite connect_status_4 2#"<<connect_status_4<<endl;
			exit(-1);
		}
	int tls_connect_socket_status3 = 666;
	tls_connect_socket_status3 = tls_connect_socket(tls3, s15, "localhost");
	//cout<<"tls_connect_socket_status in validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls_connect_socket_status3<<endl;
	//if (tls_connect_socket_status3 != 0){cout<<" tls_error(tls) in validate_chains_peer_local_with_remote_ip_only.cpp "<<tls_error(tls2)<<endl; exit(-1);}
	if (tls_connect_socket_status3 != 0){cout<<" tls_connect_socket_status3 tls_error(tls) in validate_chains_peer_local_with_remote_ip_only.cpp "<<tls_error(tls3)<<endl;}

	//Offset berechnen
	//cout<<"anzahl_ketten_lokal#"<<anzahl_ketten_lokal<<"#"<<endl;
	unsigned long long offset_remote_block_fuer_db = - 1;

//#############
//i_temp = anzahl_ketten_remote - anzahl_ketten_lokal + i;
//for (unsigned long long j = anzahl_ketten_lokal ; j < anzahl_ketten_remote; j++)
//{
//	cout<<"Temp Block Nummer#"<<j<<endl;
//}
//##########################
offset_remote_block_fuer_db = i - anzahl_ketten_lokal;
//offset_remote_block_fuer_db = j;
//offset_remote_block_fuer_db = (i - anzahl_ketten_lokal) + 1;
//getchar();

		string bc_command_4;
		string block_nummer_2;
		stringstream strstream;
		strstream << offset_remote_block_fuer_db;
		strstream >> block_nummer_2;
	bc_command_4 = "get single block " + block_nummer_2  + "\r\n";
	//cout<<"REMOTE block_nummer#"<<block_nummer_2<<endl;
//#############
	int tls_write_status3 = 666;
	tls_write_status3 = tls_write(tls3, bc_command_4.c_str(), strlen(bc_command_4.c_str()));
	//cout<<"tls_write_status2 validate_chains_peer_local_with_remote_ip_only.cpp 2#"<<tls_write_status2<<endl;
	if (tls_write_status3 == -1){cout<<"tls_write_status3 TLS Error# "<<tls_error(tls3)<<endl;exit(-1);}
	char response_5[999999];//Empfangspuffer festlegen
	ssize_t bytes_5 = 0;		
	string antwort_ausgabe_5;
	bool ende_5 = true;
	bzero (response_5, sizeof(response_5));
	string response_temp_5;
	response_temp_5 = "";
	while(ende_5)
		{
			if (bytes_5 = tls_read(tls3, response_5, sizeof(response_5)) != NULL );
			{
				if (bytes_5 == 0)
				{	
					close(s15);
					ende_5 = false;
					
				}
				if (bytes_5 == -1)
				{	
					close(s15);
					ende_5 = false;
				}
				if (bytes_5 <= 999999)
				{	
					close(s15);
					ende_5 = false;
				}
				response_temp_5.append(response_5);
				//cout<<"redis Datensätze LOKAL in while#"<<response_3<<"#"<<endl;
			}
		}

	close(s15);
	tls_close(tls3);
	tls_free(tls3);
	tls_config_free(config3);

	//cout<<"Remote Block in DB Schreiben#"<<response_temp_5<<"#"<<endl;
//###########################################

//####################################################################################################################
			write_block_to_db = response_temp_5;
			//cout<<"write to DB #"<<write_block_to_db<<"#"<<endl;
			//cout<<"Letzer Remote Block der loakl auch exitiert#"<<remote_letzter_block<<"#"<<endl;
			//void write_to_db();
			//write_to_db();
		//LINSERT BEFORE .... ##########
			void write_to_db_linsert();
			write_to_db_linsert();
			
		}
	}

	//##############################

//cout<<"ENDE"<<endl;
//cout<<"getchar();"<<endl;getchar();
}


