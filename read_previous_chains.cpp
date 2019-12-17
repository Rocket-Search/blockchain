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

using namespace std;

extern string vorhandene_ketten;
extern string last_block_chain_id;
extern string previous_hash_block;
extern vector<string> config_file_parameter;

void read_previous_chains()
	{
		
		//string redis_server = "127.0.0.1";
		string redis_server = config_file_parameter[2];
		//string redis_port = "6379";
		string redis_port = config_file_parameter[3];
		
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(redis_server.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		int s; 
		
		s = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int redis_port_int = atoi(redis_port.c_str());
		addr.sin_port = htons(redis_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET;
		
		struct timeval timeout;
		timeout.tv_sec  = 10;
		timeout.tv_usec = 0;
		setsockopt (s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));

		connect(s,(struct sockaddr*)&addr, sizeof(addr));
		//string suchmuster = argv[1];
		
		//scan 0 MATCH * COUNT 1
		//string redis_command = "KEYS \"*\"\r\n";
		//string redis_command = "scan 0 MATCH * COUNT 1\r\n";
		//string redis_command = "scan 0\r\n";
		//string redis_command = "dbsize\r\n";
		//string redis_command = "LINDEX liste 0\r\n";
		string redis_command = "LINDEX blockchain_list 0\r\n";
		 
		char* request = (char*)redis_command.c_str();
		//cout<<"request: "<<request<<endl;

		send(s, request, strlen(request),0);//Daten senden
		
		char response[99999];//Empfangspuffer festlegen
		int bytes; 
		string antwort_ausgabe;
		vector<string> vektor;
		int i=0;
		bool ende = true;
		bzero (response, sizeof(response));
		
		/*
		bytes = recv(s, response, sizeof(response), 0);
		//cout<<endl<<response;
		string dbsize ;
		dbsize = response;
		cout<<dbsize<<endl;
		*/		
		
		
//###############################################################
//Daten des letzeten Block laden
		string last_block_id ;
		
		while(ende)
		{
//IF Experimental
if ( bytes = recv(s, response, sizeof(response), 0) != NULL);
{
			i = i + 1;
			//cout<<"i#"<<i<<endl;
			//cout<<endl<<response;
			
			last_block_id.append(response);
			//cout<<"last_block_id#"<<last_block_id<<endl;
			//cout<<"bytes#"<<bytes<<endl;
			//cout<<"ende#"<<ende<<endl;
			
			bzero (response, sizeof(response));
			if (bytes == 0)
			{	
				close(s);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			if (bytes < 1024)
			{	
				close(s);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			if (bytes == -1)
			{	
				close(s);
				ende = false;
				//cout<<"Last Block in redis#"<<response<<endl;
			}
			//bzero (response, sizeof(response));
}
		}
		
		//datei_inhalt.append(datei_inhalt_2);
		//cout<<"Last Block in redis#"<<response<<endl;
		//cout<<endl<<response;
	
	//cout<<"last_block_id#"<<last_block_id<<endl;
	vorhandene_ketten = last_block_id;
	string hash_block = last_block_id;
	
	//Filter ID und hash######################
	
	//Filter last ID
	string block_chain_id, hash;
	int finde_gatter;
	
	//bc-id: 555 # timestamp: 16.09.2018 16:30:30.307151371 # data: Transaktion 4 , 50€ an Alex # prevoius_hash_bc-id 3: 2ee034b218c32646dfa1020d93cc2c2155237c8ab0b779889825dce44fdca61ad0ac1d5c9a368ffeb1a42cc5133066db0681145f7f633bc15dc94f4e029ef2ef # hash_block_4: abb81850d8dd577b
	finde_gatter = last_block_id.find("#");
	
	//cout<<"finde_gatter#"<<finde_gatter<<endl;

	//last_block_id = last_block_id.substr(0, finde_gatter);
	try {last_block_id = last_block_id.substr(0, finde_gatter);}catch( std::out_of_range& exception ){cout<<"Error read_previous_chains.cpp z. 162 last_block_id std::out_of_range"<<endl;}
	
	int finde_string_bc_id;
	finde_string_bc_id = last_block_id.find("bc-id:");
	
	//last_block_id = last_block_id.substr(finde_string_bc_id + 7, 999);
	try{last_block_id = last_block_id.substr(finde_string_bc_id + 7, 999);}catch( std::out_of_range& exception ){cout<<"Error read_previous_chains.cpp z. 168 last_block_id std::out_of_range"<<endl;}
	
	last_block_id = last_block_id.erase(last_block_id.find_last_not_of(" ")+1);
	//cout<<"last_block_id#"<<last_block_id<<endl;
	last_block_chain_id = last_block_id;
	
	
	//Filter Hash
	int finde_string_hash_block_id;
	
	//hash_block_<Block-ID-Nummer>
	string suchstrig = "hash_block " + last_block_id + ":";
	//cout<<"suchstrig#"<<suchstrig<<"#"<<endl;
	
	finde_string_hash_block_id = hash_block.find(suchstrig);
	//cout<<"finde_string_hash_block_id#"<<finde_string_hash_block_id<<endl;
	
	//hash_block = hash_block.substr(finde_string_hash_block_id + suchstrig.length() + 1, 128);
	try{hash_block = hash_block.substr(finde_string_hash_block_id + suchstrig.length() + 1, 128);}catch( std::out_of_range& exception ){cout<<"Error read_previous_chains.cpp z. 187 hash_block std::out_of_range"<<endl;}

	//cout<<"hash_block#"<<hash_block<<endl;
	previous_hash_block = hash_block;
	
//ENDE##########################		
	}
		