//clear; rm -frv check_block_exists.o; g++-7 -g -fPIC -Wall -c check_block_exists.cpp

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

extern string pure_bc_block;
extern vector<string> config_file_parameter;
extern bool datensatz_existiert;
extern string write_block_to_db;
extern bool block_fuer_set_block_to_peer;
extern bool komme_von_read_peer_blocks_remote_kette_laenger;
//extern unsigned long long ubergabe_block_nummer;
extern string remote_ip;

void check_block_exists()
{

//cout<<"\e[1m"<<"check_block_exists.cpp"<<"\e[0m"<<endl;
	
	//cout<<"pure_bc_block in check_block_exists.cpp#"<<pure_bc_block<<endl;
	//cout<<"write_block_to_db in check_block_exists.cpp z 51#"<<write_block_to_db<<"###"<<endl;
	//cout<<"REMOTE erhaltener Block#"<<write_block_to_db<<"#"<<endl;
	//cout<<"pure_bc_block.size()#"<<pure_bc_block.size()<<endl;
	//cout<<"REMOTE write_block_to_db.size()#"<<write_block_to_db.size()<<endl;
	//cout<<"block_fuer_set_block_to_peer#"<<block_fuer_set_block_to_peer<<"#"<<endl;
/*
if (block_fuer_set_block_to_peer == true)
{
	cout<<"Block kommt von set_block_to_peer"<<endl;
	//write_block_to_db = pure_bc_block;
}
if (block_fuer_set_block_to_peer == false)
{
	cout<<"Block kommt NICHT von set_block_to_peer"<<endl;
}
*/
//####################################
	//$-1 Datensatz (leer)
	int datensatz_groesse = - 1 ;
	datensatz_groesse = write_block_to_db.size();
	if (datensatz_groesse == 5)
	{
		//cout<<"Datensatz LEER"<<endl;
		//cout<<"RETURN"<<endl;
		datensatz_existiert = false;
		return;
	}

//####################################

	if (block_fuer_set_block_to_peer == true)
	{
		//cout<<"Block kommt von set_block_to_peer"<<endl;
		write_block_to_db = pure_bc_block;
		//cout<<"SET BLOCK TO PEER in check_block_exists.cpp z 83#"<<write_block_to_db<<"#"<<endl;
		
	}

//####################################
	int wo_ist_newline = -1;
	wo_ist_newline = write_block_to_db.find("\n");
	int wo_ist_bc_id_2 = -1;

	if(wo_ist_newline != -1)
	{
		char chars[] = "\n";
		for (unsigned int i = 0; i < strlen(chars); ++i)
		{
			write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars[i]), write_block_to_db.end());
			pure_bc_block = write_block_to_db;
		}
		/*
		//bis bc-id alles wegmachen
		if (wo_ist_bc_id_2 != 0)
		{
			cout<<"bis bc-id filtern pos #"<<wo_ist_bc_id_2<<"#"<<endl;
			try{pure_bc_block = pure_bc_block.substr(wo_ist_bc_id_2, pure_bc_block.length());}catch( std::out_of_range& exception ){cout<<"Error check_block_exists.cpp pure_bc_block std::out_of_range z.106"<<endl;}
			cout<<"Bis bc-id abgeschnitten pure_bc_block#"<<pure_bc_block<<"#"<<endl;
			//string test3;
			//cin>>test3;
		}
		*/
	}
	//####
	int wo_ist_cr = -1;
	wo_ist_cr = write_block_to_db.find("\r");
	if(wo_ist_cr != -1)
	{
		char chars2[] = "\r";
		for (unsigned int j = 0; j < strlen(chars2); ++j)
		{
			write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars2[j]), write_block_to_db.end());
			pure_bc_block = write_block_to_db;
		}
		
	}
	//#####
	wo_ist_bc_id_2 = write_block_to_db.find("bc-id:");
	//cout<<"bis bc-id filtern pos #"<<wo_ist_bc_id_2<<"#"<<endl;
	if (wo_ist_bc_id_2 != 0)
	{
		//cout<<"bis bc-id filtern pos #"<<wo_ist_bc_id_2<<"#"<<endl;
		try{pure_bc_block = pure_bc_block.substr(wo_ist_bc_id_2, pure_bc_block.length());}catch( std::out_of_range& exception )
		{
			//cout<<"Error check_block_exists.cpp pure_bc_block std::out_of_range z.106 pure_bc_block#"<<pure_bc_block<<"#"<<endl;
			//cout<<"Empfangener Datensatz von #"<<remote_ip<<" Defekt. Stoppen Das Laden der Blöcke"<<endl;
			//cout<<"Empfangener Datensatz defekt. Stoppen Das Laden der Blöcke"<<endl;
			//cout<<"Inhalt des Defekten Blocks: "<<pure_bc_block<<endl;
		}
		//cout<<"Bis bc-id abgeschnitten pure_bc_block#"<<pure_bc_block<<"#"<<endl;
		//string test3;
		//cin>>test3;
	}
	//cout<<"write_block_to_db in check_block_exists.cpp NACH erase \n#"<<write_block_to_db<<endl;
	//cout<<"SET BLOCK TO PEER in check_block_exists.cpp NACH erase z. 100#"<<write_block_to_db<<"#"<<endl;
//####################################
/*
int finde_dollar_minus_1 = - 1 ;
finde_dollar_minus_1 = write_block_to_db.find("$-1");
if (finde_dollar_minus_1 != -1)
{
cout<<"write_block_to_db gleich DOLLAR MINUS EINS"<<endl;
cout<<"ENDE RETURN"<<endl;
return;
}
*/
	/*
	pure_bc_block = write_block_to_db;
	cout<<"pure_bc_block in check_block_exists.cpp#"<<pure_bc_block<<endl;

	if (pure_bc_block == "")
	{
		cout<<"Kein Block zum prüfen in check_block_exists.cpp z. 49 continue"<<endl;
		cout<<"ENDE"<<endl;
		//return("nix");
		//return (0);
		//return 1;
		return;
		//continue;
	}
	cout<<"durführe check_block_exists.cpp"<<endl;
	*/
	

	//Empfangenen Remote Block analyieren####################################
	//cout<<"pure_bc_block in check_block_exists.cpp z170 ###"<<pure_bc_block<<"###"<<endl;
	//Empfangenen Remote Block analyieren####################################



//Empfangenen Remote Block analyieren####################################
	//Filter ID, Zeit, Prevois Hash, hash_block und dann in DB suchen bzw. über ID direkt LINDEX ansprechen.
	//cout<<"REMOTE pure_bc_block#"<<pure_bc_block<<"#"<<endl;
	//bc-id
	int wo_ist_bc_id = -1;
	string bc_id;
	bc_id = pure_bc_block;
	wo_ist_bc_id = pure_bc_block.find("bc-id:");
	//cout<<"wo_ist_bc_id in check_block_exists.cpp z.97#"<<wo_ist_bc_id<<"#"<<endl;
	//if (wo_ist_bc_id != -1){bc_id = bc_id.substr(wo_ist_bc_id + 7, pure_bc_block.length());}else{cout<<"check_block_exists.cpp Datensatz bc_id defekt"<<endl;exit(-1);}
	if (wo_ist_bc_id != -1){bc_id = bc_id.substr(wo_ist_bc_id + 7, pure_bc_block.length());}else{cout<<"bc-id defekt"<<endl;exit(-1);}
	int wo_ist_hash = -1;
	wo_ist_hash = bc_id.find("#");
	if(wo_ist_hash != -1){bc_id = bc_id.substr(0,wo_ist_hash - 1);}else{cout<<"check_block_exists.cpp Datensatz bc_id defekt"<<endl;exit(-1);}
	//cout<<"bc_id#"<<bc_id<<"#"<<endl;
	
	//timestamp
	int wo_ist_timestamp = -1;
	string timestamp = pure_bc_block;
	wo_ist_timestamp = timestamp.find("timestamp:");
	if(wo_ist_timestamp != -1){timestamp = timestamp.substr(wo_ist_timestamp + 11 , timestamp.length());}else{cout<<"check_block_exists.cpp Datensatz timestamp defekt"<<endl;exit(-1);}
	wo_ist_hash = -1;
	wo_ist_hash = timestamp.find("#");
	if(wo_ist_hash != -1){timestamp = timestamp.substr(0, wo_ist_hash -1);}else{cout<<"check_block_exists.cpp Datensatz timestamp defekt"<<endl;exit(-1);}
	//cout<<"timestamp#"<<timestamp<<"#"<<endl;
	
	//prevoius_hash
	int wo_ist_prevoius_hash_bc_id = -1;
	string prevoius_hash = pure_bc_block;
	wo_ist_prevoius_hash_bc_id = prevoius_hash.find("prevoius_hash_bc-id");
	if(wo_ist_prevoius_hash_bc_id != -1){prevoius_hash = prevoius_hash.substr(wo_ist_prevoius_hash_bc_id, prevoius_hash.length());}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash defekt"<<endl;exit(-1);}
	int wo_ist_doppelpunkt = -1;
	wo_ist_doppelpunkt = prevoius_hash.find(":");
	if (wo_ist_doppelpunkt != -1){prevoius_hash = prevoius_hash.substr(wo_ist_doppelpunkt + 2, prevoius_hash.length());}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash defekt"<<endl;exit(-1);}
	wo_ist_hash = -1;
	wo_ist_hash = prevoius_hash.find("#");
	if(wo_ist_hash != -1){prevoius_hash = prevoius_hash.substr(0, 128);}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash defekt"<<endl;exit(-1);}		//128 Zeichen, ist die Länge des SHA512 Hashes
	//cout<<"prevoius_hash#"<<prevoius_hash<<"#"<<endl;
	
	//hash des blocks
	int wo_ist_hash_block = -1;
	string hash_block = pure_bc_block;
	wo_ist_hash_block = hash_block.find("hash_block");
	if(wo_ist_hash_block != -1){hash_block = hash_block.substr(wo_ist_hash_block , hash_block.length());}else{cout<<"check_block_exists.cpp Datensatz hash_block defekt"<<endl;exit(-1);}
	wo_ist_doppelpunkt = -1;
	wo_ist_doppelpunkt = hash_block.find(":");
	if (wo_ist_doppelpunkt != -1){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2, hash_block.length());}else{cout<<"check_block_exists.cpp Datensatz hash_block defekt"<<endl;exit(-1);}
	wo_ist_hash = -1;
	wo_ist_hash = hash_block.find("#");
	if(wo_ist_hash != -1){hash_block = hash_block.substr(0, 128);}else{cout<<"check_block_exists.cpp Datensatz hash_block defekt"<<endl;exit(-1);}		//128 Zeichen, ist die Länge des SHA512 Hashes
	//cout<<"hash_block#"<<hash_block<<"#"<<endl;	
	
//####################################
	//in redis nach der ID bzw. Blocknummer suchen und schauen ob diese vorhanden ist
	int s13 = 666;
	//string bc_peer = "127.0.0.1";
	string bc_peer = config_file_parameter[2];
	//string bc_peer_port = "6379";
	string bc_peer_port = config_file_parameter[3];
	struct hostent *host;//Hostname struktuieren
	host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr;
	addr.sin_addr = *(struct in_addr*)host->h_addr;
	//int s; 
	s13 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int = atoi(bc_peer_port.c_str());
	addr.sin_port = htons(bc_peer_port_int);//Connection Portnummer des Servers festlegen
	addr.sin_family = AF_INET;
	int connect_status = 666;
	if (connect_status == -1)
	{
		cout<<"Socket error auf der Gegenseite# "<<connect_status<<endl;
		//continue;
		exit(666);
	}
	//connect() timeout setzen 					//http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap11-015.htm#RxxKap11015040003941F043100			//https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
	struct timeval timeout;
	timeout.tv_sec  = 10;
	timeout.tv_usec = 0;
	setsockopt (s13, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
	setsockopt (s13, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
	connect_status = connect(s13,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
	//Listen Länge Anfrage senden
	string bc_command;
	bc_command = "LLEN blockchain_list \r\n";
	send(s13, bc_command.c_str(), bc_command.length(),0);//Daten senden
	//Listen Länge Empfangen
	char response[1024];
	ssize_t bytes = 0;
	string antwort_ausgabe;
	vector<string> vektor;
	bool ende = true;
	string lokal_ketten_laenge;
	bzero (response, sizeof(response));
	while(ende)
	{
		bytes = recv(s13, response, sizeof(response), 0);
		//cout<<"response LLEN blockchain_list in check_block_exists.cpp"<<response<<"#"<<endl;;
		lokal_ketten_laenge.append(response);
		bzero (response, sizeof(response));
		if (bytes == 0)
		{	
			close(s13);
			ende = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		if (bytes < 1024)
		{	
			close(s13);
			ende = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		if (bytes == -1)
		{	
			close(s13);
			ende = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		//bzero (response, sizeof(response));
	}
	//Aus redis abmelden
	string redis_quit_command = "quit\r\n" ;
	char* request2 = (char*)redis_quit_command.c_str();
	int send_status = 666;
	send_status = send(s13, request2, strlen(request2),0);
	//cout<<"send_status QUIT#"<<send_status<<endl;
	ssize_t bytes_1 = 0;
	char response_2[1024];
	bytes_1 = recv(s13, response_2, sizeof(response_2), 0);
	//cout<<"response QUIT#"<<response_2<<endl;
	bzero (response_2, sizeof(response_2));
	
	close(s13);
//####################################
	
//####################################
	//prüfen ob Block ID in redis liegt
	//cout<<"bc_id#"<<bc_id<<"#"<<endl;
	//cout<<"timestamp#"<<timestamp<<"#"<<endl;
	//cout<<"prevoius_hash#"<<prevoius_hash<<"#"<<endl;
	//cout<<"hash_block#"<<hash_block<<"#"<<endl;	
	//####################################
	//in redis nach der ID bzw. Blocknummer suchen und schauen ob diese vorhanden ist
	//string bc_peer = "127.0.0.1";
	string bc_peer_2 = config_file_parameter[2];
	//string bc_peer_port = "6379";
	string bc_peer_port_2 = config_file_parameter[3];
	struct hostent *host_2;//Hostname struktuieren
	host_2 = gethostbyname(bc_peer_2.c_str()); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr_2;
	addr_2.sin_addr = *(struct in_addr*)host_2->h_addr;
	int s14; 
	s14 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	int bc_peer_port_int_2 = atoi(bc_peer_port_2.c_str());
	addr_2.sin_port = htons(bc_peer_port_int_2);//Connection Portnummer des Servers festlegen
	addr_2.sin_family = AF_INET;
	//connect() timeout setzen 					//http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap11-015.htm#RxxKap11015040003941F043100			//https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
	struct timeval timeout_2;
	timeout_2.tv_sec  = 10;
	timeout_2.tv_usec = 0;
	setsockopt (s14, SOL_SOCKET, SO_SNDTIMEO, &timeout_2, sizeof (timeout_2));
	setsockopt (s14, SOL_SOCKET, SO_RCVTIMEO, &timeout_2, sizeof (timeout_2));
	int connect_status_2;
	connect_status_2 = 666;
	connect_status_2 = connect(s14,(struct sockaddr*)&addr_2, sizeof(addr_2));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
	if (connect_status_2 == -1)
	{
		cout<<"Socket error auf der Gegenseite 2#"<<connect_status_2<<endl;
		exit(-1);
	}
	
	//Listen Länge Anfrage senden
	string bc_command_2;
	//Eventuell im Index Nr. 0 rausholen ???
	
//#############################################################################	
	//#############################################################################
	//OFFSET auf Basis bc-id berechnen und korrekten Datensatz aus redis holen
	//cout<<"Loakle redis Datensatz#"<<lokal_ketten_laenge<<"#"<<endl;
	//Filter Zahl aus Datenstrom
	//Lokal Ketten Länge
	int wo_ist_lokal_doppelpunkt = -1;
	string lokal_ketten_laenge_string;
	lokal_ketten_laenge_string = lokal_ketten_laenge;
	wo_ist_lokal_doppelpunkt = lokal_ketten_laenge_string.find(":");
	//cout<<"wo_ist_lokal_doppelpunkt in check_block_exists.cpp z.288#"<<wo_ist_lokal_doppelpunkt<<"#"<<endl;
	if (wo_ist_lokal_doppelpunkt != -1){lokal_ketten_laenge_string = lokal_ketten_laenge_string.substr(wo_ist_lokal_doppelpunkt + 1, lokal_ketten_laenge_string.length());}else{cout<<"check_block_exists.cpp Datensatz lokal_ketten_laenge_string defekt z. 289"<<endl;exit(-1);}
	int wo_ist_remote_backslash_n = -1;
	wo_ist_remote_backslash_n = lokal_ketten_laenge_string.find("\n");
	if (wo_ist_remote_backslash_n != -1){lokal_ketten_laenge_string = lokal_ketten_laenge_string.substr(0,wo_ist_remote_backslash_n);}else{cout<<"check_block_exists.cpp Datensatz lokal_ketten_laenge_string defekt z. 292"<<endl;exit(-1);}
	unsigned long long lokal_ketten_laenge_long = -1;
	try {lokal_ketten_laenge_long = stoll(lokal_ketten_laenge_string); }catch(std::invalid_argument& exception){cout<<"Error check_block_exists.cpp ketten_laenge_long stol  invaild argument z. 299"<<endl;}
	//cout<<"#LOKAL ketten laenge LONG#"<<lokal_ketten_laenge_long<<"#"<<endl;
	//###
	//Lokal bc-id
	string lokal_bc_id = write_block_to_db;
	int wo_ist_lokal_bc_id = -1;
	wo_ist_lokal_bc_id = lokal_bc_id.find("bc-id:");
	//cout<<"wo_ist_lokal_bc_id in check_block_exists.cpp z.304#"<<wo_ist_lokal_bc_id<<"#"<<endl;
	//if (wo_ist_lokal_bc_id != -1){lokal_bc_id = lokal_bc_id.substr(wo_ist_lokal_bc_id + 7, lokal_bc_id.length());}else{cout<<"check_block_exists.cpp Datensatz lokal_bc_id defekt z. 302"<<endl;exit(-1);}
	if (wo_ist_lokal_bc_id != -1){lokal_bc_id = lokal_bc_id.substr(wo_ist_lokal_bc_id + 7, lokal_bc_id.length());}else
	{
		//cout<<"check_block_exists.cpp Datensatz lokal_bc_id defekt z. 303 oder enhalt KEINE DATEN"<<endl;
		return;
	}
	//cout<<"lokal_bc_id#"<<lokal_bc_id<<"#"<<endl;
	int wo_ist_remote_hash = -1;
	wo_ist_remote_hash = lokal_bc_id.find("#");
	if(wo_ist_remote_hash != -1){lokal_bc_id = lokal_bc_id.substr(0,wo_ist_remote_hash - 1);}else{cout<<"check_block_exists.cpp Datensatz bc_id defekt z. 306"<<endl;exit(-1);}
	//cout<<"#lokal_bc_id#"<<lokal_bc_id<<"##"<<endl;
	unsigned long long lokal_bc_id_long = -1;
	try {lokal_bc_id_long = stoll(lokal_bc_id);}catch(std::invalid_argument& exception){cout<<"Error check_block_exists.cpp ketten_laenge_long stol  invaild argument z. 309"<<endl;}
	//cout<<"#LOKAL ketten ID#"<<lokal_bc_id_long<<"#"<<endl;
	//Nun das OFFSET Berechnen und über LINDEX korrekten block aus redis laden
	unsigned long long offset_fuer_redis_block = 0;

	//offset_fuer_redis_block = lokal_ketten_laenge_long - lokal_bc_id_long;
	//offset_fuer_redis_block = lokal_ketten_laenge_long - lokal_bc_id_long - 1;
	offset_fuer_redis_block = lokal_ketten_laenge_long - 1 ;

	//cout<<"offset_fuer_redis_block#"<<offset_fuer_redis_block<<endl;
	string offset_fuer_redis_block_string ;
		stringstream strstream;
		strstream << offset_fuer_redis_block;
		strstream >> offset_fuer_redis_block_string;

	//#########################################################################
	
	//bc_command_2 = "LINDEX blockchain_list " + bc_id + "\r\n";
	//bc_command_2 = "LINDEX blockchain_list 0\r\n";													//LOKALE REDIS DATENBANK ANFRAGE
	//bc_command_2 = "LINDEX blockchain_list " + lokal_bc_id + "\r\n";									//LOKALE REDIS DATENBANK ANFRAGE
	if (komme_von_read_peer_blocks_remote_kette_laenger == true)
	{
		//cout<<"bc_id#"<<bc_id<<"#"<<endl;
		//offset_fuer_redis_block_string = "0";
		//offset_fuer_redis_block_string = bc_id;
		//cout<<"offset_fuer_redis_block_string für komme_von_read_peer_blocks_remote_kette_laenger "<<offset_fuer_redis_block_string<<endl;

		//offset minux bc-id
		string offset_fuer_redis_block_string_2;
		int offset_fuer_redis_block_int_2 = -1;
		int bc_id_int_2 = -1;
		offset_fuer_redis_block_int_2 = atoi(offset_fuer_redis_block_string.c_str()) - atoi(bc_id.c_str());
		//cout<<"offset_fuer_redis_block_int_2"<<offset_fuer_redis_block_int_2<<endl;
				stringstream strstream;
				strstream << offset_fuer_redis_block_int_2;
				strstream >> offset_fuer_redis_block_string;
		//bc_command_2 = "LINDEX blockchain_list " + offset_fuer_redis_block_string + "\r\n";					//LOKALE REDIS DATENBANK ANFRAGE
		//bc_command_2 = "LINDEX blockchain_list " + offset_fuer_redis_block_string + "\r\n";					//LOKALE REDIS DATENBANK ANFRAGE
		bc_command_2 = "LINDEX blockchain_list " + offset_fuer_redis_block_string + "\r\n";					//LOKALE REDIS DATENBANK ANFRAGE
		komme_von_read_peer_blocks_remote_kette_laenger = false;
		offset_fuer_redis_block_string = "";
		//string test_3; cout<<"CIN"<<endl; cin>>test_3;
	}
	else
	{
		bc_command_2 = "LINDEX blockchain_list " + offset_fuer_redis_block_string + "\r\n";					//LOKALE REDIS DATENBANK ANFRAGE
	}
	//cout<<"bc_command in check_block_exists.cpp #"<<bc_command_2<<endl;
	send(s14, bc_command_2.c_str(), bc_command_2.length(),0);//Daten senden
	
	//Block Empfangen
	//char response_4[1024];
	char response_4[999999];
	ssize_t bytes_4 = 0;
	string antwort_ausgabe_4;
	vector<string> vektor_4;
	bool ende_4 = true;
	string response_temp_4;
	bzero (response_4, sizeof(response_4));
	while(ende_4)
	{
		bytes_4 = recv(s14, response_4, sizeof(response_4), 0);
		//cout<<"response_4 BLOCK check_block_exists.cpp z. 340##"<<response_4<<"##"<<endl;;
		//bzero (response_4, sizeof(response_4));
		response_temp_4.append(response_4);
		
		if (bytes_4 == 0)
		{	
			close(s14);
			ende_4 = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		//if (bytes_4 < 1024)
			if (bytes_4 < 999999)
		{	
			close(s14);
			ende_4 = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		if (bytes_4 == -1)
		{	
			close(s14);
			ende_4 = false;
			//cout<<"Last Block in redis#"<<response<<endl;
		}
		//bzero (response_4, sizeof(response_4));
		//response_temp_4.append(response_4);
		bzero (response_4, sizeof(response_4));
	}
	
	//Aus redis abmelden
	string redis_quit_command_2 = "quit\r\n" ;
	char* request3 = (char*)redis_quit_command_2.c_str();
	int send_status_2 = 666;
	send_status_2 = send(s14, request3, strlen(request3),0);
	//cout<<"send_status QUIT#"<<send_status<<endl;
	ssize_t bytes_2 = 0;
	char response_3[1024];
	bytes_2 = recv(s14, response_3, sizeof(response_3), 0);
	//cout<<"response QUIT#"<<response_3<<"#ENDE QUIT response_3#"<<endl;
	bzero (response_3, sizeof(response_3));
	
	close(s14);
	//###########################################
	//ID, timestamp, previous_hash, hash_block vom geladen lokalen redis block filtern und mit gesendetem peer block vergleichen.
	//cout<<"response_4 BLOCK check_block_exists.cpp"<<response_temp_4<<"#"<<endl;;
	//cout<<"bc_id REMOTE#"<<bc_id<<"#"<<endl;
	//cout<<"timestamp REMOTE#"<<timestamp<<"#"<<endl;
	//cout<<"prevoius_hash REMOTE#"<<prevoius_hash<<"#"<<endl;
	//cout<<"hash_block REMOTE#"<<hash_block<<"#"<<endl;
	
//#############################################################################

	int finde_dollar_minus_1 = - 1 ;
	finde_dollar_minus_1 = response_temp_4.find("$-1");
	if (finde_dollar_minus_1 != -1)
	{
		//cout<<"KEIN Datensatz in Datenbank gefunden"<<endl;
		//cout<<"Schreibe Datensatz in DB "<<endl;
		//cout<<"response_temp_4 gleich DOLLAR MINUS EINS"<<endl;
		//cout<<"ENDE RETURN"<<endl;
		//write_block_to_db = "";
		//pure_bc_block = "";
		return;
	}

//#############################################################################
	//cout<<"Lokaler Redis block#"<<response_temp_4<<"#"<<endl;

//Lokalen Redis Datensatz analysieren#############################################################################
	//bc-id
	int wo_ist_bc_id_lokal = -1;
	string bc_id_lokal;
	bc_id_lokal = response_temp_4;
	wo_ist_bc_id_lokal = bc_id_lokal.find("bc-id:");
	if (wo_ist_bc_id_lokal != -1){bc_id_lokal = bc_id_lokal.substr(wo_ist_bc_id_lokal + 7, bc_id_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz bc_id_lokal defekt"<<endl;exit(-1);}
	int wo_ist_hash_lokal = -1;
	wo_ist_hash_lokal = bc_id_lokal.find("#");
	if(wo_ist_hash_lokal != -1){bc_id_lokal = bc_id_lokal.substr(0,wo_ist_hash_lokal - 1);}else{cout<<"check_block_exists.cpp Datensatz bc_id_lokal defekt"<<endl;exit(-1);}
	//cout<<"bc_id LOKAL#"<<bc_id_lokal<<"#"<<endl;
	
	//timestamp
	int wo_ist_timestamp_lokal = -1;
	string timestamp_lokal = response_temp_4;
	wo_ist_timestamp_lokal = timestamp_lokal.find("timestamp:");
	if(wo_ist_timestamp_lokal != -1){timestamp_lokal = timestamp_lokal.substr(wo_ist_timestamp_lokal + 11 , timestamp_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz timestamp__lokal defekt"<<endl;exit(-1);}
	wo_ist_hash_lokal = -1;
	wo_ist_hash_lokal = timestamp_lokal.find("#");
	if(wo_ist_hash_lokal != -1){timestamp_lokal = timestamp_lokal.substr(0, wo_ist_hash_lokal -1);}else{cout<<"check_block_exists.cpp Datensatz timestamp_lokal defekt"<<endl;exit(-1);}
	//cout<<"timestamp LOKAL#"<<timestamp_lokal<<"#"<<endl;
		
	//prevoius_hash
	int wo_ist_prevoius_hash_bc_id_lokal = -1;
	string prevoius_hash_lokal = response_temp_4;
	wo_ist_prevoius_hash_bc_id_lokal = prevoius_hash_lokal.find("prevoius_hash_bc-id");
	if(wo_ist_prevoius_hash_bc_id_lokal != -1){prevoius_hash_lokal = prevoius_hash_lokal.substr(wo_ist_prevoius_hash_bc_id_lokal, prevoius_hash_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash_lokal defekt"<<endl;exit(-1);}
	int wo_ist_doppelpunkt_lokal = -1;
	wo_ist_doppelpunkt_lokal = prevoius_hash_lokal.find(":");
	if (wo_ist_doppelpunkt_lokal != -1){prevoius_hash_lokal = prevoius_hash_lokal.substr(wo_ist_doppelpunkt_lokal + 2, prevoius_hash_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash_lokal defekt"<<endl;exit(-1);}
	wo_ist_hash_lokal = -1;
	wo_ist_hash_lokal = prevoius_hash_lokal.find("#");
	if(wo_ist_hash_lokal != -1){prevoius_hash_lokal = prevoius_hash_lokal.substr(0, 128);}else{cout<<"check_block_exists.cpp Datensatz prevoius_hash_lokal defekt"<<endl;exit(-1);}		//128 Zeichen, ist die Länge des SHA512 Hashes
	//cout<<"prevoius_hash LOKAL#"<<prevoius_hash_lokal<<"#"<<endl;
	
	//hash des blocks
	int wo_ist_hash_block_lokal = -1;
	string hash_block_lokal = response_temp_4;
	wo_ist_hash_block_lokal = hash_block_lokal.find("hash_block");
	if(wo_ist_hash_block_lokal != -1){hash_block_lokal = hash_block_lokal.substr(wo_ist_hash_block_lokal , hash_block_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz hash_block_lokal defekt"<<endl;exit(-1);}
	wo_ist_doppelpunkt_lokal = -1;
	wo_ist_doppelpunkt_lokal = hash_block_lokal.find(":");
	if (wo_ist_doppelpunkt_lokal != -1){hash_block_lokal = hash_block_lokal.substr(wo_ist_doppelpunkt_lokal + 2, hash_block_lokal.length());}else{cout<<"check_block_exists.cpp Datensatz hash_block_lokal defekt"<<endl;exit(-1);}
	wo_ist_hash_lokal = -1;
	wo_ist_hash_lokal = hash_block_lokal.find("#");
	if(wo_ist_hash_lokal != -1){hash_block_lokal = hash_block_lokal.substr(0, 128);}else{cout<<"check_block_exists.cpp Datensatz hash_block_lokal defekt"<<endl;exit(-1);}		//128 Zeichen, ist die Länge des SHA512 Hashes
	//cout<<"hash_block LOKAL#"<<hash_block_lokal<<"#"<<endl;	
	
	//##############
	//cout<<"REMOTE bc_id#"<<bc_id<<"#"<<endl;
	//cout<<"LOKAL bc_id_lokal#"<<bc_id_lokal<<"#"<<endl;
	if ( (timestamp == timestamp_lokal) && (bc_id == bc_id_lokal) && (prevoius_hash == prevoius_hash_lokal) && ( hash_block == hash_block_lokal) )
	{
		//cout<<"Datensatz ist gleich überspringen##########"<<endl;
		datensatz_existiert = true;
	}
	else
	{
		//cout<<"Block NICHT in DB vorhanden, schreibe Block in DB"<<endl;
		//cout<<"Schreibe Datensatz in DB #"<<response_temp_4<<"#"<<endl;
		datensatz_existiert = false;
	}
	//###########################################
	
//####################################
	
//cout<<"ENDE check_block_exists.cpp"<<endl;
}