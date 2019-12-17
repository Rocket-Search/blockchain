//clear; rm -frv  read_peer_blocks.o; clear; g++-7 -g -fPIC -Wall -c  read_peer_blocks.cpp

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

//extern vector<string> peer_lists;
extern vector<string> peer_lists_temp;
string write_block_to_db;
extern string blocks_from_db;
vector<string> erreichbare_peers;
unsigned long long anzahl_ketten_db_records_int ;
string rpoplpush_redis_blocks_from_db;
string rpoplpush_redis_redis_command_from_main;
unsigned long long zufall_pruef_nummer; 
bool komme_von_read_peer_blocks_remote_kette_laenger = false;
//unsigned long long ubergabe_block_nummer = 0;
extern vector<string> config_file_parameter;
extern string lokal_ip_adresse;
extern bool datensatz_existiert;
extern string remote_ip;
string ip_fuer_block_senden;
extern bool local_chain_longer_than_remote;
extern unsigned long long local_kette_laenge;
extern int remote_kettten_laenge;


void read_peer_blocks()
{
	//cout<<"READ PEER BLOCK INFOS"<<endl;
	//cout<<"\e[1m"<<"read_peer_blocks.cpp"<<"\e[0m"<<endl;
	int peer_lists_size = peer_lists_temp.size();
	//cout<<"peer_lists_size#"<<peer_lists_size<<endl;
	//cout<<"remote_ip in read_peer_blocks:"<<remote_ip<<endl;

	//vector<string> erreichbare_peers;

//###########################################################################################################################################
//ereichbarkeit prüfen. Nicht so sinnvoll wenn der Server erst später online geht. Prüfen ????
/*		
	int s1; 

//Prüfe jeden Host auf ereichbarkeit , falls nicht, aus Array löschen######################################
	for (int i = 0; i < peer_lists_size ; i++)
	{
		//cout<<"peer_lists#"<<peer_lists_temp[i]<<endl;
		//cout<<"i#"<<i<<endl;
		
		//string bc_peer = "127.0.0.1";
		//string bc_peer_port = "6379";
	
		string bc_peer;
		
		//string bc_peer_port = "8888";
		string bc_peer_port = config_file_parameter[1];
		
bc_peer = peer_lists_temp[i];
//bc_peer = "172.17.190.80";
cout<<"bc_peer#"<<bc_peer<<endl;
		//if (bc_peer == "##NO PEERS##");
		//{
		//	cout<<"NO PEERS#"<<bc_peer<<endl;
		//	bc_peer = "";
		//	continue;
		//}
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
	
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		//int s; 
		
		s1 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int bc_peer_port_int = atoi(bc_peer_port.c_str());
		addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET;
		
		int connect_status = 666;
		
		//connect() timeout setzen 					//http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap11-015.htm#RxxKap11015040003941F043100			//https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
		struct timeval timeout;
		timeout.tv_sec  = 1;
		timeout.tv_usec = 0;
//ggf. Werte auch hier in aus condig file holen ????
		setsockopt (s1, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s1, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
		connect_status = connect(s1,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		cout<<"connect_status#"<<connect_status<<endl;
		if (connect_status == -1)
		{
			cout<<"Socket error auf der Gegenseite read_peer_blocks.cpp#"<<connect_status<<endl;
			//Aus Array löschen.
			//cout<<"peer_lists_temp[i]"<<peer_lists_temp[i]<<endl;
			//cout<<"peer_lists_temp.size 1#"<<peer_lists_temp.size()<<endl;
			//peer_lists_temp.pop_back();
			//erreichbare_peers.push_back(peer_lists_temp[i]);
			//cout<<"peer_lists_temp.size 2#"<<peer_lists_temp.size()<<endl;
			bc_peer = "";
			continue;
		}
		
		cout<<"Ereichbare peer_lists_temp read_peer_blocks.cpp#"<<peer_lists_temp[i]<<endl;
		
		erreichbare_peers.push_back(peer_lists_temp[i]);
	
		close(s1);
	}
*/	
	erreichbare_peers = peer_lists_temp;
//###########################################################################################################################################


//Erreichbare Peers Ketten größe abfragen########################################################
	//https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
	srand (time(NULL));
//Zufallsnummer anhand der Kettengröße festlegen
	zufall_pruef_nummer = rand() % 50 + 25; 
	//cout<<"zufall_pruef_nummer read_peer_blocks.cpp ###"<<zufall_pruef_nummer<<"###"<<endl;

	int erreichbare_peers_array_size = erreichbare_peers.size();
	//cout<<"erreichbare_peers_array_size#"<<erreichbare_peers_array_size<<endl;
	
	string anzahl_ketten_db_records = ":0" ;
	int s2, s3; 
	string redis_command_from_main;
	//string blocks_from_db;
	
	for (int i = 0; i < erreichbare_peers_array_size; i++)
	{
		//cout<<"erreichbare_peers[i] read_peer_blocks.cpp#"<<erreichbare_peers[i]<<endl;
		
		//cout<<"LLEN Blockgröße anfordern"<<endl;

		//TLS Initialisierung################################
		//gnuTLS Initilisieren
		int tls_init_status = 666;
		tls_init_status = tls_init();
		//cout<<"tls_init_status read_peer_blocks.cpp#"<<tls_init_status<<endl;
		//###
		struct tls *tls = NULL;
		tls = tls_client();
		//cout<<"tls_client read_peer_blocks.cpp#"<<tls<<endl;
		//###
		struct tls_config *config = NULL;
		config = tls_config_new();
		//cout<<"tls_config_new read_peer_blocks.cpp#"<<config<<endl;
		//###
		tls_config_insecure_noverifycert(config);
		tls_config_insecure_noverifyname(config);
		tls_configure(tls, config);
		//##################################################

		string bc_peer;
		
		//string bc_peer_port = "8888";
		string bc_peer_port = config_file_parameter[1];
		
		bc_peer = erreichbare_peers[i];
		//bc_peer = "172.17.190.80";
//cout<<"bc_peer#"<<bc_peer<<endl;
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
	
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		//int s; 
		
		s2 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int bc_peer_port_int = atoi(bc_peer_port.c_str());
		addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET;
		
		struct timeval timeout;
		timeout.tv_sec  = 10;
		timeout.tv_usec = 0;
		setsockopt (s2, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s2, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
				
		int connect_status = 666;

		
		//connect() timeout setzen 					//http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap11-015.htm#RxxKap11015040003941F043100			//https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
		//struct timeval timeout;
		//timeout.tv_sec  = 1;
		//timeout.tv_usec = 0;
		//setsockopt (s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		//setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
		connect_status = connect(s2,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		if (connect_status == -1)
		{
			//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
			continue;
		}
		
		int tls_connect_socket_status = 666;
		tls_connect_socket_status = tls_connect_socket(tls, s2, "localhost");
		//cout<<"tls_connect_socket_status in read_peer_blocks.cpp#"<<tls_connect_socket_status<<endl;
		//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;
	
		//Redis Command Anzahl der Werte in der Liste
		//string bc_command = "LLEN blockchain_list\r\n";
		string bc_command;
		bc_command = "get chain size\r\n";
		//cout<<"bc_command read_peer_blocks.cpp#"<<bc_command<<"#"<<endl;
		//send(s2, bc_command.c_str(), bc_command.length(),0);//Daten senden
		//cout<<"s#"<<s<<endl;

		int tls_write_status = 666;
		tls_write_status = tls_write(tls, bc_command.c_str(), strlen(bc_command.c_str()));
		//cout<<"tls_write_status read_peer_blocks.cpp#"<<tls_write_status<<endl;

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
			//bytes = recv(s2, response, sizeof(response), 0);
			//cout<<"response get chain size#"<<response<<"#"<<endl;;

			bytes = tls_read(tls, response, sizeof(response));

			//cout<<"response get chain size#"<<response<<"#"<<endl;;
			
			anzahl_ketten_db_records = response;
			
			bzero (response, sizeof(response));
			if (bytes == 0)
			{	
				close(s2);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			if (bytes < 999999)
			{	
				close(s2);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			if (bytes == -1)
			{	
				close(s2);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			//bzero (response, sizeof(response));
		}
		
		tls_close(tls);
		tls_free(tls);
		tls_config_free(config);

		//cout<<"anzahl_ketten_db_records auf PEER#"<<anzahl_ketten_db_records<<"#"<<endl;
		//cout<<"Schliese s2"<<endl;
		close(s2);
			
//Prüfen ob lokale Ketten vorhanden sind
		//###########
		redis_command_from_main = "LLEN blockchain_list\r\n";
		//cout<<"redis_command_from_main in read_peer_blocks.cpp #"<<redis_command_from_main<<endl;
		void read_all_chains_from_db();	
		read_all_chains_from_db();
		//cout<<"read_all_chains_from_db in read_peer_blocks#"<<blocks_from_db<<endl;		
		//cout<<"\e[1m"<<"read_peer_blocks.cpp"<<"\e[0m"<<endl;

		//ggf. hier etwas filtern
		//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db#"<<blocks_from_db<<endl;

		//################################
		//bis bc-id filtern (\n newline wegmachen)
		int wo_ist_newline = -1;
		//cout<<"Filter Newline"<<endl;
		//cout<<"wo_ist_newline#"<<wo_ist_newline<<"#"<<endl;
		if (wo_ist_newline != -1)
		{
			try{blocks_from_db = blocks_from_db.substr(wo_ist_newline + 1, blocks_from_db.length() );}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp blocks_from_db z309 std::out_of_range"<<endl;}
		}
		//blocks_from_db = blocks_from_db.substr(1,blocks_from_db.length());
		//try{blocks_from_db = blocks_from_db.substr(1,blocks_from_db.length());}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp blocks_from_db std::out_of_range"<<endl;}

		//Alles bis zu bc-id entfernen
		int wo_ist_bc_id = -1;
		wo_ist_bc_id =  blocks_from_db.find("bc-id:");
		//cout<<"wo_ist_bc_id#"<<wo_ist_bc_id<<"#"<<endl;
		if (wo_ist_bc_id > 0)
		{
			//cout<<"Fiter BC-ID"<<endl;
			try{blocks_from_db = blocks_from_db.substr(wo_ist_bc_id,blocks_from_db.length());}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp blocks_from_db z318 std::out_of_range"<<endl;}
			//cout<<"SCHREIBE DATENSATZ in DB in write_to_db.cpp z. 132#"<<write_block_to_db<<"#"<<endl;
		}
		else
		{
			try{blocks_from_db = blocks_from_db.substr(1,blocks_from_db.length());}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp blocks_from_db std::out_of_range"<<endl;}
		}
		//################################
		//cout<<"blocks_from_db in read_peer_blocks.cpp z326 #"<<blocks_from_db<<"#"<<endl;

		//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db#"<<blocks_from_db<<endl;
		unsigned long long anzahl_lokaler_ketten_long = 0;
		//try{anzahl_lokaler_ketten_long = stoll(blocks_from_db);}catch(std::invalid_argument& exception){cout<<"Error read_peer_blocks.cpp anzahl_lokaler_ketten_long z327 stoll zinvaild argument"<<endl;exit(-1);}
		//try{anzahl_lokaler_ketten_long = stoll(blocks_from_db);}catch(std::invalid_argument& exception){cout<<"Error read_peer_blocks.cpp anzahl_lokaler_ketten_long z327 stoll zinvaild argument: Block:"<<blocks_from_db<<endl;}
		try{anzahl_lokaler_ketten_long = stoll(blocks_from_db);}catch(std::invalid_argument& exception)
		{
			//cout<<"Error read_peer_blocks.cpp anzahl_lokaler_ketten_long z327 stoll zinvaild argument: Block:"<<endl;
		}
		//cout<<"anzahl_lokaler_ketten_long#"<<anzahl_lokaler_ketten_long<<endl;
		//###########

//Prüfen wieviel Ketten in Peer Datenbank sind
		//cout<<"Anzahl Ketten#"<<anzahl_ketten_db_records<<endl;
		//anzahl_ketten_db_records = anzahl_ketten_db_records.substr(1, anzahl_ketten_db_records.length());
		try{anzahl_ketten_db_records = anzahl_ketten_db_records.substr(1, anzahl_ketten_db_records.length());}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp anzahl_ketten_db_records std::out_of_range"<<endl;}
		
		//cout<<"PEER Anzahl Ketten#"<<anzahl_ketten_db_records<<endl;
		//unsigned long long anzahl_ketten_db_records_int = stoll(anzahl_ketten_db_records.c_str());
		anzahl_ketten_db_records_int = stoll(anzahl_ketten_db_records.c_str());

//string test;
//cout<<"Anzahl LOKALER Blöcker#"<<anzahl_lokaler_ketten_long<<"#"<<endl;
//cout<<"REMOTE Blöcke#"<<anzahl_ketten_db_records_int<<"#"<<endl;
//cin>>test;

//#################################################################################################		
//Validierungs Optionen

//#################################################################################################		
//#################################################################################################		
//Wenn lokale und Peer ketten gleich lang sind. Beide prüfen.?
if ((anzahl_ketten_db_records_int == anzahl_lokaler_ketten_long ))
{
			//cout<<"ANZAHL DER BLÖCKE IST GLEICH"<<endl;
			//Ketten von beiden Peers validieren
			
			//cout<<"validate_chains_peer_local"<<endl;
			void validate_chains_peer_local();
			validate_chains_peer_local();
			//cout<<"\e[1m"<<"read_peer_blocks.cpp"<<"\e[0m"<<endl;
}

//#################################################################################################		
//#################################################################################################
//Wenn die lokale Kette länger ist als die Remote Kette, Peer fragen ob er die fehlenden Blöcke möchte
//ERST AUFRUFEN WENN DIE GEGENSEITE AUF LISTEN STEHT !!!!!
//string test123; cout<<"CIN"<<endl; cin>>test123;

if (anzahl_lokaler_ketten_long > anzahl_ketten_db_records_int)
{
	//cout<<"LOKALE KETTE LÄNGER"<<endl;
	//cout<<"LOKALE kettenlänge#"<<anzahl_lokaler_ketten_long<<endl;
	//cout<<"REMOTE kettenlänge#"<<anzahl_ketten_db_records_int<<endl;
	//cout<<"CHECK PEER"<<endl;
	//cout<<"BAUSTELLE"<<endl;
	//cout<<"bc_peer#"<<bc_peer<<endl;
	ip_fuer_block_senden = bc_peer;
	//Kann nur gesendet werden wenn der Server schon gestartet ist. Hier ist das aber in der Startphase, deshalb funktioniert das nicht.
	//An Peer Senden das unsere ketten länger sind 
	//und Peer veranlassen unsere Ketten zu laden, nach vlaidierung
	//IP vom Geber übergeben
	//cout<<"remote_ip in read_peer_blocks:"<<remote_ip<<endl;
	local_chain_longer_than_remote = true;

	local_kette_laenge = anzahl_lokaler_ketten_long;
	remote_kettten_laenge = anzahl_ketten_db_records_int;

	//nun alles überspringen und warten bis der lokale Server gestartet ist und auf listen steht

	//cout<<"starte send_peer_local_chain_longer_and_send_blocks"<<endl;
	//string test123; cout<<"CIN and return()"<<endl; cin>>test123;
	return;
/*
void send_peer_local_chain_longer_and_send_blocks();
send_peer_local_chain_longer_and_send_blocks();
*/
}
//#################################################################################################
//#################################################################################################
//Wenn Lokalen Kette kleiner ist als Remote Kette, Kette laden
//if (anzahl_lokaler_ketten_long < anzahl_ketten_db_records_int) 
//if ((anzahl_ketten_db_records_int > 0) && (anzahl_lokaler_ketten_long == 0))
if ((anzahl_lokaler_ketten_long < anzahl_ketten_db_records_int) && ( anzahl_lokaler_ketten_long != 0))
{
	//cout<<"PEER KETTE LÄNGER"<<endl;
	//cout<<"HOLE ALLE VALIDEN KETTEN VON PEER"<<endl;
	//cout<<"BAUSTELLE"<<endl;
	//string test2;
	//cout<<"Anzahl LOKALER Blöcker#"<<anzahl_lokaler_ketten_long<<"#"<<endl;
	//cout<<"REMOTE Blöcke#"<<anzahl_ketten_db_records_int<<"#"<<endl;
	//cin>>test2;

	//anzahl_lokaler_ketten_long = 0 //redis flushen und ketten von peer laden
	//Peer Ketten bis zum längeren Abschnit valideren und
	//dann die längeren restlichen ketten laden
	
	//die Block ID differenz zwischen lokal und Remote identifizieren.
	//cout<<"Anzahl LOKALER Blöcker#"<<anzahl_lokaler_ketten_long<<"#"<<endl;
	//cout<<"REMOTE Blöcke#"<<anzahl_ketten_db_records_int<<"#"<<endl;
	unsigned long long block_nummer_remote_offset_long = 0;
	string block_nummer_remote_offset_string;

	for (int i = 0; i < erreichbare_peers_array_size; i++)
		//for (int i = 0; i < anzahl_ketten_db_records_int; i++)
		{
			bc_peer = erreichbare_peers[i];
			//cout<<"EREICHBARE REMOTE SERVER#"<<bc_peer<<" # "<<i<<endl;
			
			//Eigene IP Adress übersprinegnen continue/return
			if (lokal_ip_adresse == bc_peer)
			{
				//cout<<"Continue eigene IP"<<endl;
				//tls_close(tls2);
				//tls_free(tls2);
				//tls_config_free(config2);
				continue;
			}
	
			//Block von Peer laden
			//Laden Blocknummer (Offset mit Nummern die fehlenden Blöcke).
			block_nummer_remote_offset_long = anzahl_ketten_db_records_int - anzahl_lokaler_ketten_long - 1;
			//block_nummer_remote_offset_long = anzahl_ketten_db_records_int - anzahl_lokaler_ketten_long ;
			//cout<<"block_nummer_remote_offset_long#"<<block_nummer_remote_offset_long<<"#"<<endl;
			//string test;
			//for (unsigned long long j = 0; j < block_nummer_remote_offset_long; j++ )
			//for (unsigned long long j = block_nummer_remote_offset_long; j >= 0; j-- )
			//for (unsigned long long j = block_nummer_remote_offset_long; j > 0; j-- )
			//for (unsigned long long j = anzahl_lokaler_ketten_long; j <= anzahl_ketten_db_records_int; j++ )
			//for (unsigned long long j = block_nummer_remote_offset_long; j >= 0; j-- )
			for (long long j = block_nummer_remote_offset_long; j >= 0; j-- )
				{
					//cin>>test;
									//cout<<"Durchlauf Nr. # "<<j<<" # "<<endl;
									//block_nummer_remote_offset_long = anzahl_ketten_db_records_int - anzahl_lokaler_ketten_long;
					//block_nummer_remote_offset_long-- + 1; //Block um ein veringern, da der lokale Block um 1 vergrößert wurde, zumindest nach write_to_db()
					//cout<<"REMOTE Blöcke Nummer#"<<j<<"#"<<endl;
					//cin>>test;

					if (anzahl_ketten_db_records_int == anzahl_lokaler_ketten_long)
					{
						//cout<<"Block Anzahl NUN GLEICH"<<endl;
						//cout<<"continue"<<endl;
						continue;
					}

						//block_nummer_remote_offset_long = anzahl_ketten_db_records_int - anzahl_lokaler_ketten_long;
						//block_nummer_remote_offset_long = anzahl_ketten_db_records_int - j;
						//cout<<"Hohle Block Nummer von REMOTE#"<<j<<endl;
						
						//get single block Nummer block_nummer_remote_offset
						//TLS Initialisierung################################
						//gnuTLS Initilisieren
						int tls_init_status4 = 666;
						tls_init_status4 = tls_init();
						//cout<<"tls_init_status read_peer_lists.cpp#"<<tls_init_status4<<endl;
						//###
						struct tls *tls4 = NULL;
						tls4 = tls_client();
						//cout<<"tls_client read_peer_lists.cpp#"<<tls4<<endl;
						//###
						struct tls_config *config4 = NULL;
						config4 = tls_config_new();
						//cout<<"tls_config_new read_peer_lists.cpp#"<<config4<<endl;
						//###
						tls_config_insecure_noverifycert(config4);
						tls_config_insecure_noverifyname(config4);
						tls_configure(tls4, config4);
						//##################################################
						//##################################################
						bc_peer_port = config_file_parameter[1];		// 8888
						//bc_peer = erreichbare_peers[i];				//bc_server IP
						//cout<<"Connect bc_server IP#"<<bc_peer<<endl;
						//struct hostent *host;//Hostname struktuieren
						host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
						//struct sockaddr_in addr;
						addr.sin_addr = *(struct in_addr*)host->h_addr;
						int s5;
						s5 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
						bc_peer_port_int = atoi(bc_peer_port.c_str());
						addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
						addr.sin_family = AF_INET;
						struct timeval timeout_3;
						timeout_3.tv_sec  = 10;
						timeout_3.tv_usec = 0;
						setsockopt (s5, SOL_SOCKET, SO_SNDTIMEO, &timeout_3, sizeof (timeout_3));
						setsockopt (s5, SOL_SOCKET, SO_RCVTIMEO, &timeout_3, sizeof (timeout_3));
						connect_status = 666;
						connect_status = connect(s5,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
						if (connect_status == -1)
						{
							//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
							continue;
						}
						char response3 [999999];
						tls_connect_socket_status = 666;
						tls_connect_socket_status = tls_connect_socket(tls4, s5, "localhost");
						//cout<<"tls_connect_socket_status in read_peer_lists.cpp#"<<tls_connect_socket_status<<endl;
						if (tls_connect_socket_status == -1){cout<<" tls_error(tls) tls_connect_socket PROBLEM"<<tls_error(tls)<<endl;}
						string bc_command;
							block_nummer_remote_offset_string = "";
							stringstream strstream;
							strstream << j;
							strstream >> block_nummer_remote_offset_string;
						bc_command = "get single block " + block_nummer_remote_offset_string + "\r\n";
						int tls_write_status = 666;
						tls_write_status = tls_write(tls4, bc_command.c_str(), strlen(bc_command.c_str()));
						//cout<<"tls_write_status read_peer_lists.cpp#"<<tls_write_status<<endl;
						if (tls_write_status == -1){cout<<"tls_error(tls) tls_write PROBLEM"<<tls_error(tls)<<endl;}
						//Empfange bc_server blöcke
						ssize_t bytes = 0;
						bool ende = true;
						bzero (response3, sizeof(response3));
						string peer_fehlender_remote_block;
						while(ende)
						{
							bytes = tls_read(tls4, response3, sizeof(response3));
							peer_fehlender_remote_block.append(response3);								
							if (bytes == 0)
							{	
								close(s5);
								ende = false;
								
							}
							if (bytes == -1)
							{	
								close(s5);
								ende = false;
							}
							if (bytes < 999999)
							{		
								close(s5);
								ende = false;
							}
						}
						
						close(s5);
						tls_close(tls4);
						tls_free(tls4);
						tls_config_free(config4);
						//cout<<"Fehlender block von REMOTE#"<<peer_fehlender_remote_block<<"#"<<endl;

//##############################################################

						//prüfen ob Blöcke lokal schon exitieren
						komme_von_read_peer_blocks_remote_kette_laenger = true;
						//ubergabe_block_nummer = 0;
						write_block_to_db = peer_fehlender_remote_block;
						//cout<<"write_block_to_db in read_peer_blocks.cpp z548 ###"<<write_block_to_db<<"###"<<endl;
						void check_block_exists();
						check_block_exists();
						komme_von_read_peer_blocks_remote_kette_laenger = false;
						//cout<<"datensatz_existiert#"<<datensatz_existiert<<"#"<<endl;
						//string test_2; cout<<"CIN"<<endl; cin>>test_2;

						if (datensatz_existiert == false)
						{
							void write_to_db();
							write_to_db();
							//cout<<"schreibe datensatz in DB virteull"<<endl;
						}

						datensatz_existiert = false;

//##############################################################		
				}
			}

//cout<<"EXIT for DEBUG read_peer_blocks.cpp z358"<<endl;//exit(-1);

}

//#################################################################################################
//#################################################################################################
//NUR Wenn keine lokalen Ketten vorhanden sind, alle Ketten von Peer(s) laden.
if ((anzahl_ketten_db_records_int > 0) && (anzahl_lokaler_ketten_long == 0))
{
			//cout<<"KEINE LOKALE KETTE VORHANDEN"<<endl;
			//cout<<"anzahl_ketten_db_records_int REMOTE KETTEN"<<anzahl_ketten_db_records_int<<endl;
			//cout<<"anzahl_lokaler_ketten_long LOKAL KETTEN"<<anzahl_lokaler_ketten_long<<endl;
			//cout<<"Peer Ketten vorhanden aber keine lokalen"<<endl;
			//cout<<"Lese Ketten von Peer"<<endl;
		//###################################################################################
		//Ketten Abmischen

			//cout<<"erreichbare_peers_array_size#"<<erreichbare_peers_array_size<<endl;
			//cout<<"anzahl_ketten_db_records_int#"<<anzahl_ketten_db_records_int<<endl;
			for (int i = 0; i < erreichbare_peers_array_size; i++)
			//for (int i = 0; i < anzahl_ketten_db_records_int; i++)
			{
				//Falls lokal keine Ketten vorhanden, alle Ketten laden
			//{
				
				
				//TLS Initialisierung################################
				//gnuTLS Initilisieren
				int tls_init_status2 = 666;
				tls_init_status2 = tls_init();
				//cout<<"tls_init_status read_peer_lists.cpp#"<<tls_init_status2<<endl;
				//###
				struct tls *tls2 = NULL;
				tls2 = tls_client();
				//cout<<"tls_client read_peer_lists.cpp#"<<tls2<<endl;
				//###
				struct tls_config *config2 = NULL;
				config2 = tls_config_new();
				//cout<<"tls_config_new read_peer_lists.cpp#"<<config2<<endl;
				//###
				tls_config_insecure_noverifycert(config2);
				tls_config_insecure_noverifyname(config2);
				tls_configure(tls2, config2);
				//##################################################
				
				//cout<<"KEINE LOKALEN KETTEN VORHANDEN, LADE KETTEN VON PEER"<<endl;
				//cout<<"Lese Ketten von Peer#"<<erreichbare_peers[i]<<endl;;
				//cout<<"erreichbare_peers[i]#"<<erreichbare_peers[i]<<endl;
				
				//LLEN Blockgröße anforfern
			
				string bc_peer;
				
				//string bc_peer_port = "8888";
				string bc_peer_port = config_file_parameter[1];
				
				bc_peer = erreichbare_peers[i];
				//bc_peer = "172.17.190.80";
				//cout<<"bc_peer#"<<bc_peer<<"#"<<endl;
				//cout<<"lokal_ip_adresse#"<<lokal_ip_adresse<<"#"<<endl;
				if (lokal_ip_adresse == bc_peer)
				{
					//cout<<"Continue eigene IP"<<endl;
					tls_close(tls2);
					tls_free(tls2);
					tls_config_free(config2);

					continue;
				}
				//cout<<"Lese vorhandene Block Ketten ein"<<endl;
				
			
				struct hostent *host;//Hostname struktuieren
				host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
				
				struct sockaddr_in addr;
				addr.sin_addr = *(struct in_addr*)host->h_addr;
				//int s; 
				
				s3 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
				
				int bc_peer_port_int = atoi(bc_peer_port.c_str());
				addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
				
				addr.sin_family = AF_INET;

				struct timeval timeout;
				timeout.tv_sec  = 10;
				timeout.tv_usec = 0;
				setsockopt (s3, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
				setsockopt (s3, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

				int connect_status = 666;
				connect_status = connect(s3,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
				if (connect_status == -1)
				{
					//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
					continue;
				}
				int tls_connect_socket_status2 = 666;
				tls_connect_socket_status2 = tls_connect_socket(tls2, s3, "localhost");
				//cout<<"tls_connect_socket_status in read_peer_lists.cpp#"<<tls_connect_socket_status2<<endl;
				//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;
				if (tls_connect_socket_status2 == -1)
				{
					cout<<"tls_connect_socket_status2 = -1"<<endl;
					continue;
				}
			
				//Redis Command Anzahl der Werte in der Liste
				//string bc_command = "LLEN blockchain_list\r\n";
				string bc_command;
				
				//bc_command = "flushall\r\n";
				//cout<<"bc_command#"<<bc_command<<"#"<<endl;
				//send(s3, bc_command.c_str(), bc_command.length(),0);//Daten senden
								
				//bc_command = "get chain\r\n";
				bc_command = "get chain size\r\n";
				//cout<<"bc_command z. 463#"<<bc_command<<"#"<<endl;
				//send(s3, bc_command.c_str(), bc_command.length(),0);//Daten senden
				int tls_write_status = 666;
				tls_write_status = tls_write(tls2, bc_command.c_str(), strlen(bc_command.c_str()));
				//cout<<"tls_write_status read_peer_lists.cpp#"<<tls_write_status<<endl;
				//cout<<"s#"<<s<<endl;
			
				char response[1024];//Empfangspuffer festlegen
				//char response[2048];//Empfangspuffer festlegen
				//char response[99999];//Empfangspuffer festlegen
				//char response[512];//Empfangspuffer festlegen
				//char response[99999];//Empfangspuffer festlegen. Max. Größe des chars = 999999999999999999
				//char *response;

				//int bytes;
				ssize_t bytes = 0;
				string antwort_ausgabe;
				//vector<string> vektor;
				//int i=0;
				bool ende = true;
				bzero (response, sizeof(response));

				//int finde_ende_von_datensat = -1;
				string response_temp;
				
				write_block_to_db = "";
				
				//bool daten_groesser_1024 = false;

				//response wird weiter unten verarbeitet bei "string anzahl_ketten_peer_string = response;"
				while(ende)
				{
					//ende_datensatz_geunden:
					//memset(response, '\0', sizeof(response));
					//bytes = recv(s3, response, sizeof(response), 0);
					bytes = tls_read(tls2, response, sizeof(response));				//Wird weiter untern bei "string anzahl_ketten_peer_string = response;" bearbeitet
					//bytes = recv(s3, write_block_to_db.c_str(), write_block_to_db.length(), 0);
					//cout<<"bytes#"<<bytes<<endl;
					//cout<<"#############################"<<response<<"#############################";
					//bzero(response, sizeof(response));
					//char *response = new char(); 
					write_block_to_db = "";
					
					if (bytes == 0)
					{	
						close(s3);
						ende = false;
						
					}
					if (bytes == -1)
					{	
						close(s3);
						ende = false;
					}
					if (bytes < 1024)
					{		
					close(s3);
					ende = false;
					//cout<<"Last Block in redis#"<<response<<endl;
					}
				}
				//cout<<"#############################################################################################################"<<endl;
				//cout<<"write_block_to_db#"<<write_block_to_db<<endl;
				//void write_to_db();
				//write_to_db();
				//write_block_to_db = "";
				//void write_to_db();
				//write_to_db();
				//cout<<"write_block_to_db  in read_peer_blocks ####"<<write_block_to_db<<endl;
				//cout<<"Schließe S3"<<endl;
				close(s3);
				tls_close(tls2);
				tls_free(tls2);
				tls_config_free(config2);

//Nach Kettengöße Information von Peer. Alle Ketten einzelnt von Peer laden und einzelnt in den lokalen redis schreiben
				unsigned long long anzahl_ketten_peer ;
				//cout<<"response"<<response<<endl;
				string anzahl_ketten_peer_string = response;
				//anzahl_ketten_peer_string = anzahl_ketten_peer_string.substr(1,anzahl_ketten_peer_string.length());
				try{anzahl_ketten_peer_string = anzahl_ketten_peer_string.substr(1,anzahl_ketten_peer_string.length());}catch( std::out_of_range& exception ){cout<<"Error read_peer_blocks.cpp anzahl_ketten_peer_string std::out_of_range"<<endl;}
				
				//cout<<"anzahl_ketten_peer_string REMOTE"<<anzahl_ketten_peer_string<<endl;
				anzahl_ketten_peer =  stoll(anzahl_ketten_peer_string.c_str());
				//cout<<"anzahl_ketten_peer"<<anzahl_ketten_peer<<endl;
				
				//Netzwerkverbidnung definieren####
				//TLS Initialisierung################################
				//gnuTLS Initilisieren
				int tls_init_status3 = 666;
				tls_init_status3 = tls_init();
				//cout<<"tls_init_status read_peer_lists.cpp#"<<tls_init_status3<<endl;
				//###
				struct tls *tls3 = NULL;
				tls3 = tls_client();
				//cout<<"tls_client read_peer_lists.cpp#"<<tls3<<endl;
				//###
				struct tls_config *config3 = NULL;
				config3 = tls_config_new();
				//cout<<"tls_config_new read_peer_lists.cpp#"<<config3<<endl;
				//###
				tls_config_insecure_noverifycert(config3);
				tls_config_insecure_noverifyname(config3);
				tls_configure(tls3, config3);
				//##################################################
				//bc_peer_port = "8888";
				bc_peer_port = config_file_parameter[1];
				bc_peer = erreichbare_peers[i];
				//struct hostent *host;//Hostname struktuieren
				host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
				//struct sockaddr_in addr;
				addr.sin_addr = *(struct in_addr*)host->h_addr;
				int s4;
				s4 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
				bc_peer_port_int = atoi(bc_peer_port.c_str());
				addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
				addr.sin_family = AF_INET;

				struct timeval timeout_2;
				timeout_2.tv_sec  = 10;
				timeout_2.tv_usec = 0;
				setsockopt (s4, SOL_SOCKET, SO_SNDTIMEO, &timeout_2, sizeof (timeout_2));
				setsockopt (s4, SOL_SOCKET, SO_RCVTIMEO, &timeout_2, sizeof (timeout_2));

				connect_status = 666;
				connect_status = connect(s4,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
				if (connect_status == -1)
				{
					//cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
					continue;
				}
				string block_nummer;
				//char response2 [1024];
				char response2 [999999];
				string peer_single_block_for_local_db ;
				
				tls_connect_socket_status = 666;
				tls_connect_socket_status = tls_connect_socket(tls3, s4, "localhost");
				//cout<<"tls_connect_socket_status in read_peer_lists.cpp#"<<tls_connect_socket_status<<endl;
				//cout<<" tls_error(tls)"<<tls_error(tls)<<endl;

				//hochzählen von 0 bis XXX
				//for (unsigned long long i = 0; i < anzahl_ketten_peer; i++)
				//runterzählen von XX bis 0
				//unsigned long long j = anzahl_ketten_peer;
				//for (unsigned long long j = anzahl_ketten_peer; j > -1; j = j - 1)
				//for (unsigned long long j = anzahl_ketten_peer; j > 0; j = j - 1)
				//cout<<"anzahl_ketten_peer#"<<anzahl_ketten_peer<<endl;
				//for (long long j = anzahl_ketten_peer + 1; j >= 0; j = j - 1)
				for (long long j = anzahl_ketten_peer; j >= 0; j = j - 1)
				{
					//j = j - 1;
					//cout<<"j#"<<j<<endl;
					//cout<<"GET SINGLE BLOCK# "<<j<<" #"<<endl;
						
						stringstream strstream;
						strstream << j;
						strstream >> block_nummer;

					//cout<<"Durchlauf Nr.#"<<j<<endl;
					//bc_command = "download single block " + block_nummer + "\r\n";
					bc_command = "get single block " + block_nummer + "\r\n";
					//cout<<"bc_command in read_peer_blocks.cpp z. 624#"<<bc_command<<endl;
					
					//send(s4, bc_command.c_str(), bc_command.length(),0);//Daten senden
					tls_write_status = 666;
					tls_write_status = tls_write(tls3, bc_command.c_str(), strlen(bc_command.c_str()));
					//cout<<"tls_write_status read_peer_lists.cpp#"<<tls_write_status<<endl;
					//sleep(1);
					//cout<<"ende#"<<ende<<endl;
					bool ende2 = true;
					//ende = false;
					//cout<<"ende2#"<<ende2<<endl;
					//bytes = 0;
					bytes = 0;					
					//while(ende2 == false)
					while(ende2)
					{
						//bytes = recv(s4, response2, sizeof(response2), 0);
						bytes = tls_read(tls3, response2, sizeof(response2));						
						//cout<<"bytes#"<<bytes<<endl;
						//cout<<"response2#"<<response2<<endl;
						//cout<<"ende2#"<<ende2<<endl;
						
						peer_single_block_for_local_db.append(response2);
						
						bzero(response2, sizeof(response2));
						
						if (bytes == 0)
						{	
							close(s4);
							//cout<<"bytes == 0"<<endl;
							//peer_single_block_for_local_db = "";
							ende2 = false;
						}
						
						if (bytes == -1)
						{	
							close(s4);
							//cout<<"bytes == -1"<<endl;
							//peer_single_block_for_local_db = "";
							ende2 = false;
						}
						
						if (bytes == 999999)
						{	
							//close(s4);
							//cout<<"bytes == 999999"<<endl;
							ende2 = true;
						}
						if (bytes < 999999)
						{	
							//close(s4);
							//cout<<"bytes < 999999"<<endl;
							//
							ende2 = false;
						}
						//cout<<"While Neudurchlauf"<<endl;
					}
					
//Block in DB schreiben##############################################################################################					
					//cout<<"peer_single_block_for_local_db#"<<peer_single_block_for_local_db<<"#"<<endl;
					write_block_to_db = peer_single_block_for_local_db;
//################################################################################################################
					void check_block_exists();
					check_block_exists();
					//cout<<"datensatz_existiert STATUS#"<<datensatz_existiert<<"#"<<endl;
					if (datensatz_existiert == true)
					{
						//cout<<"datensatz_existiert STATUS TRUE#"<<datensatz_existiert<<"#"<<endl;
						return;
					}
					else
					{
						//cout<<"datensatz_existiert STATUS FALSE#"<<datensatz_existiert<<"#"<<endl;					
//#################################################################################################					
						//cout<<"write_block_to_db"<<write_block_to_db<<endl;
						void write_to_db();
						write_to_db();
						peer_single_block_for_local_db = "";
						write_block_to_db = "";
					}
//################################################################################################################

				}
				
				//Letzte Lokale redis Eintrag löschen, da dieser nur Murx enthält "\x7f" . redis-cli RPOPLPUSH blockchain_list <NUMMER>
				//bc_command = "RPOPLPUSH \"blockchain_list\" \"" + write_block_to_db + "\"\r\n";
				//string rpoplpush_redis_blocks_from_db;
				//string rpoplpush_redis_redis_command_from_main;
				/*
				string anzahl_ketten_peer_string_2;
					stringstream strstream;
					//anzahl_ketten_peer = anzahl_ketten_peer;
					strstream << anzahl_ketten_peer;
					strstream >> anzahl_ketten_peer_string_2;
				rpoplpush_redis_redis_command_from_main = "RPOPLPUSH blockchain_list " + anzahl_ketten_peer_string_2 + "\r\n";
				void rpoplpush_redis();
				rpoplpush_redis();
				//cout<<"rpoplpush_redis_blocks_from_db#"<<rpoplpush_redis_blocks_from_db<<endl;
				*/				
				close(s4);
				tls_close(tls3);
				tls_free(tls3);
				tls_config_free(config3);
//##############################################################################################				
				//}
//##############################################################################################
//Falls lokal Ketten vorhanden prüfen welche Kette gewinnt

//cout<<"Falls lokal Ketten vorhanden prüfen welche Kette gewinnt"<<endl;
//Die längere Valide Kette gewinnt
//cout<<"anzahl_ketten_db_records_int"<<anzahl_ketten_db_records_int<<endl;
//cout<<"anzahl_lokaler_ketten_long"<<anzahl_lokaler_ketten_long<<endl;

//##############################################################################################
//Schauen in wie weit die Ketten identisch sind in Bezug auf die Transaktions Ketten NICHT der GPG Signatur
			
			}
//###################################################################################
		}
else
{
		//cout<<"Keine Kette auf REMOTE Peer vorhanden"<<endl;
		//Remote Peer Fragen ob er ketten möchte
			
}
}
		//################################################################################################################################

//cout<<"leere write_block_to_db und pure_bc_block in write_block_to_db.cpp"<<endl;
//write_block_to_db = "";
//pure_bc_block = "";


//cout<<"ENDE read_peer_blocks.cpp"<<endl;
//cout<<"\t"<<endl;
//cout<<"##########################################################################################################################"<<endl;
//cout<<"##########################################################################################################################"<<endl;
//cout<<"##########################################################################################################################"<<endl;
//cout<<"getchar();"<<endl;getchar();
}

	
