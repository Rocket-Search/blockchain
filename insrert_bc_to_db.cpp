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

extern string block_formated_redis;
extern vector<string> config_file_parameter;

void insert_in_db()
	{
		
		//cout<<"\e[1m"<<"insert_bc_to_db.cpp"<<"\e[0m"<<endl;
		//cout<<"Insert to redis"<<endl;
		//string redis_server = "127.0.0.1";
		string redis_server = config_file_parameter[2];
		//string redis_port = "6379";
		string redis_port = config_file_parameter[3];
		
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(redis_server.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		int s10; 
		
		s10 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
		int redis_port_int = atoi(redis_port.c_str());
		addr.sin_port = htons(redis_port_int);//Connection Portnummer des Servers festlegen
		
		addr.sin_family = AF_INET; 
		connect(s10,(struct sockaddr*)&addr, sizeof(addr));

		string redis_command = block_formated_redis + "\r\n";
		//cout<<"redis_command#"<<redis_command<<endl;
				 
		char* request = (char*)redis_command.c_str();
		//cout<<"request: "<<request<<endl;

		send(s10, request, strlen(request),0);//Daten senden

		string redis_quit_command = "quit\r\n" ;
		char* request2 = (char*)redis_quit_command.c_str();
		int send_status = 666;
		send_status = send(s10, request2, strlen(request2),0);
		//cout<<"send_status QUIT#"<<send_status<<endl;
		ssize_t bytes_1 = 0;
		char response[1024];
		bytes_1 = recv(s10, response, sizeof(response), 0);
		//cout<<"response QUIT#"<<response<<endl;
		bzero (response, sizeof(response));
		
		close(s10);

	//cout<<"ENDE"<<endl;	
//ENDE##########################		
	}
		