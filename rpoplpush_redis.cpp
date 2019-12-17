//clear; rm -frv rpoplpush_redis.o; clear; g++-7 -g -fPIC -Wall -c rpoplpush_redis.cpp

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

extern string rpoplpush_redis_blocks_from_db;
extern string rpoplpush_redis_redis_command_from_main;
extern vector<string> config_file_parameter;

void rpoplpush_redis()
	{
		
		//cout<<"rpoplpush_redis"<<endl;
		
		
		//cout<<"rpoplpush_redis_redis_command_from_main#"<<rpoplpush_redis_redis_command_from_main<<endl;
		
		
		
		//string redis_server = "127.0.0.1";
		string redis_server = config_file_parameter[2];
		//string redis_port = "6379";
		string redis_port = config_file_parameter[3];
		
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(redis_server.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		int s_rpoplpush; 
		
		s_rpoplpush = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int redis_port_int = atoi(redis_port.c_str());
		addr.sin_port = htons(redis_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET; 
		connect(s_rpoplpush,(struct sockaddr*)&addr, sizeof(addr));

		//Redis Command Anzahl der Werte in der Liste
		//string redis_command = "LLEN blockchain_list\r\n";
		string redis_command;
		redis_command = rpoplpush_redis_redis_command_from_main;
		//cout<<"RPOPLPUSH blockchain_list#"<<redis_command<<endl;
		
		char* request = (char*)redis_command.c_str();
		//cout<<"request: "<<request<<endl;

		send(s_rpoplpush, request, strlen(request),0);//Daten senden
		
		//char response[1024];//Empfangspuffer festlegen
		char response[99999];//Empfangspuffer festlegen
		int bytes; 
		string antwort_ausgabe;
		vector<string> vektor;
		//int i=0;
		bool ende = true;
		bzero (response, sizeof(response));
		
		//string last_block_id ;

		//int finde_ende_von_datensat = -1;
		
		rpoplpush_redis_blocks_from_db = "";
		
		while(ende)
		{
			bytes = recv(s_rpoplpush, response, sizeof(response), 0);
			//i = i + 1;
			//cout<<"i#"<<i<<endl;
			//cout<<endl<<response;
			rpoplpush_redis_blocks_from_db.append(response);
			//blocks_from_db = response;
						//cout<<"#####################"<<blocks_from_db<<endl;
			/*
			blocks_from_db.append(response);
			//blocks_from_db = response ;
			//finde_ende_von_datensat = blocks_from_db.find("\r\n");
			//cout<<"blocks_from_db in_read_all_chains_from_db#"<<blocks_from_db<<endl;
			if (finde_ende_von_datensat != -1)
				{
					//close(s);
					//ende = false;
					cout<<"Ende des Datensatzes != \r\n#"<<blocks_from_db<<endl;
					//cout<<"write_block_to_db#"<<write_block_to_db<<endl;
					blocks_from_db = "";
					finde_ende_von_datensat = -1;
				}			
			*/
			bzero (response, sizeof(response));
			if (bytes == 0)
			{	
				close(s_rpoplpush);
				ende = false;
				//cout<<"bytes == 0#"<<response<<endl;
			}

			if (bytes < 99999)
			{	
				close(s_rpoplpush);
				ende = false;
				//cout<<"bytes < 1024#"<<response<<endl;
			}

			if (bytes == -1)
			{	
				close(s_rpoplpush);
				ende = false;
				//cout<<"bytes == -1#"<<response<<endl;
			}
			//bzero (response, sizeof(response));
		}
		close(s_rpoplpush);
		//cout<<"rpoplpush_redis#####################"<<rpoplpush_redis_blocks_from_db<<"#####################"<<endl;
		//blocks_from_db = "";
						}
		