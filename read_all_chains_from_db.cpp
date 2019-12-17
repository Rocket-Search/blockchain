//clear; rm -frv read_all_chains_from_db.o; g++-7 -g -fPIC -Wall -c read_all_chains_from_db.cpp
	
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

extern string blocks_from_db;
extern string redis_command_from_main;
//extern string read_loacal_db_records;
extern vector<string> config_file_parameter;

bool invalidChar_4 (char c) 
{  
    return !(c>=0 && c <128);   
}

void read_all_chains_from_db()
	{
		
		//cout<<"blocks_from_db#"<<blocks_from_db<<"#"<<	endl;
		//cout<<"\e[1m"<<"read_all_chains_from_db.cpp"<<"\e[0m"<<endl;
		//string redis_server = "127.0.0.1";
		string redis_server = config_file_parameter[2];
		//cout<<"redis_server#"<<redis_server<<endl;
		//string redis_port = "6379";
		string redis_port = config_file_parameter[3];;
		
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

		//Redis Command Anzahl der Werte in der Liste
		//string redis_command = "LLEN blockchain_list\r\n";
		string redis_command;
		redis_command = redis_command_from_main;
		//cout<<"redis command read_all_chains_from_db.cpp command von MAIN()#"<<redis_command<<endl;
		
		//char* request = (char*)redis_command.c_str();
		//cout<<"requestread_all_chains_from_db.cpp #"<<request<<endl;

		//send(s, request, strlen(request),0);//Daten senden
		send(s, redis_command.c_str(), redis_command.length(),0);
		
		//Aufpassen redis sendet nach den 1024 noch irgednwelkche Sonder/Stuerzeichen. Diese idetifizieren und ggf. entfernen.
		//char response[1024];//Empfangspuffer festlegen
		char response[999999];//Empfangspuffer festlegen
		//int bytes; 
		ssize_t bytes = 0;
		string antwort_ausgabe;
		vector<string> vektor;
		//int i=0;
		bool ende = true;
		//bzero (response, sizeof(response));
		
		//string last_block_id ;

		//int finde_ende_von_datensat = -1;
		
		blocks_from_db = "";
		
		while(ende)
		{
			bytes = recv(s, response, sizeof(response), 0);
			//cout<<"response UNGEFILTERT#"<<response<<endl;
			//i = i + 1;
			//cout<<"i#"<<i<<endl;
			//cout<<endl<<response;
			//cout<<"bytes in read_all_chains_from_db.cpp#"<<bytes<<"#"<<endl;
			blocks_from_db.append(response);
			//blocks_from_db = response;
			//cout<<"blocks_from_db read_all_chains_from_db.cpp#"<<blocks_from_db<<endl;
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
				//close(s);
				ende = false;
				//cout<<"bytes == 0#"<<response<<endl;
				bzero (response, sizeof(response));
			}

			//if (bytes < 99999)
			//{	
			//	close(s);
			//	ende = false;
			//	//cout<<"bytes < 1024#"<<response<<endl;
			//}
			//if (bytes < 1024)

			if (bytes < 999999)
			{	
				//close(s);
				ende = false;
				//cout<<"bytes < 999999#"<<response<<endl;
				bzero (response, sizeof(response));
			}

			if (bytes == -1)
			{	
				//close(s);
				ende = false;
				//cout<<"bytes == -1#"<<response<<endl;
				bzero (response, sizeof(response));
			}
			//blocks_from_db.append(response);
			bzero (response, sizeof(response));
		}
		//cout<<"blocks_from_db#"<<blocks_from_db<<"#"<<endl;
		/*
		string redis_quit_command = "quit\r\n" ;
		char* request2 = (char*)redis_quit_command.c_str();
		int send_status = 666;
		send_status = send(s, request2, strlen(request2),0);
		//cout<<"send_status QUIT#"<<send_status<<endl;
		bytes = recv(s, response, sizeof(response), 0);
		//cout<<"response QUIT#"<<response<<endl;
		*/
		close(s);
		//cout<<"blocks_from_db#####################"<<blocks_from_db<<"#####################"<<endl;
		//blocks_from_db = "";
		bzero (response, sizeof(response));
		
		//######################################################################################################################
		/*
		//#####Sucher HEX Zeichen "\xAB usw.
		int find_hex = - 1 ;
		find_hex = blocks_from_db.find("\\x");
		cout<<"hex gefunden pos:"<<find_hex<<endl;
		*/
		/*
		int wo_ist_cr = - 1;
		char chars[] = "^A";
		for (unsigned int i = 0; i < strlen(chars); ++i)
		{
			blocks_from_db.erase(std::remove(blocks_from_db.begin(), blocks_from_db.end(), chars[i]), blocks_from_db.end());
		}
		char chars3[] = "^?";
		for (unsigned int k = 0; k < strlen(chars3); ++k)
		{
			// you need include <algorithm> to use general algorithms like std::remove()
			blocks_from_db.erase(std::remove(blocks_from_db.begin(), blocks_from_db.end(), chars3[k]), blocks_from_db.end());
		}

		blocks_from_db.erase(remove_if(blocks_from_db.begin(),blocks_from_db.end(), invalidChar_4), blocks_from_db.end());  
		cout<<"blocks_from_db GFILTERT#"<<blocks_from_db<<"###"<<endl;
		*/
		//######################################################################################################################
		/*
		if ( blocks_from_db == "");
		{
			cout<<"KEINE BLOCKS VON REDIS EMPFANGEN !!!!!"<<endl;
			blocks_from_db = "NIX";
		}
		*/		
		//cout<<"ENDE"<<endl;
		//cout<<"getchar();"<<endl;getchar();
	}
		