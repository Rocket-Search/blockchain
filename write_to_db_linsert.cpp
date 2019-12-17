//clear; rm -frv write_to_db.o; g++-7 -g -fPIC -Wall -c write_to_db.cpp

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

#include <algorithm>
#include <iterator>

using namespace std;

extern string write_block_to_db;
extern vector<string> config_file_parameter;
extern bool datensatz_existiert;
extern string pure_bc_block;
extern string remote_letzter_block;

bool invalidChar_linsert (char c) 
{  
    return !(c>=0 && c <128);   
}

void write_to_db_linsert()
	{
		//cout<<"WRITE TO LOCAL REDIS"<<endl;
		//write_block_to_db = "ZURÜCK" ;
		//cout<<"\e[1m"<<"write_to_db_linsert.cpp"<<"\e[0m"<<endl;

		//####################################################################
		//Debug to File by sap_bcc.cpp
		//ofstream debug_file_1;
		//debug_file_1.open ("/tmp/bc_server.cpp_debug_file.log", ios::app );
		//####################################################################

		//cout<<"write_to_db.cpp z55 write_block_to_db UNGEFILTERT#"<<write_block_to_db<<"#"<<endl;
		
//####################################################################		
		//Newline \n abschneiden für write_block_to_db###
		int wo_ist_newline = -1;
		int wo_ist_cr = -1;
		//wo_ist_newline = write_block_to_db.find_last_not_of("\n");
		//cout<<"wo_ist_newline#"<<wo_ist_newline<<endl;
		//write_block_to_db = write_block_to_db.substr(wo_ist_newline + 1, write_block_to_db.length() );
		try{write_block_to_db = write_block_to_db.substr(wo_ist_newline + 1, write_block_to_db.length() );}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp write_block_to_db std::out_of_range"<<endl;}
		
		wo_ist_newline = write_block_to_db.find("\n");

		if(wo_ist_newline != -1)
		{
			//write_block_to_db = write_block_to_db.erase(write_block_to_db.find_last_not_of("\n"));
			//write_block_to_db = write_block_to_db.erase(write_block_to_db.find_last_not_of("\r\n"));
			
			char chars[] = "\n";
			for (unsigned int i = 0; i < strlen(chars); ++i)
			{
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars[i]), write_block_to_db.end());
			}
			
			wo_ist_cr = write_block_to_db.find("\r");
			//write_block_to_db = write_block_to_db.substr(wo_ist_cr,write_block_to_db.length());
			try{write_block_to_db = write_block_to_db.substr(wo_ist_cr,write_block_to_db.length());}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp write_block_to_db std::out_of_range"<<endl;}
			
			char chars2[] = "\r";
			for (unsigned int j = 0; j < strlen(chars2); ++j)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars2[j]), write_block_to_db.end());
			}

			char chars3[] = "\"";
			for (unsigned int k = 0; k < strlen(chars3); ++k)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars3[k]), write_block_to_db.end());
			}

			/*
			//\x0b\x99\x7f entfernen Obacht beim späteren validieren der Ketten !!!!!!!!!!!!!!!!!!!!!
			char chars4[] = "x0b@";
			for (unsigned int l = 0; l < strlen(chars4); ++l)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars4[l]), write_block_to_db.end());
			}
			char chars5[] = "x99@";
			for (unsigned int m = 0; m < strlen(chars5); ++m)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars5[m]), write_block_to_db.end());
			}
			
			char chars6[] = "x7f@";
			for (unsigned int n = 0; n < strlen(chars6); ++n)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				write_block_to_db.erase(std::remove(write_block_to_db.begin(), write_block_to_db.end(), chars6[n]), write_block_to_db.end());
			}
			*/
		}

		write_block_to_db.erase(remove_if(write_block_to_db.begin(),write_block_to_db.end(), invalidChar_linsert), write_block_to_db.end());  
		//############################
		//Alles bis zu bc-id entfernen
		int wo_ist_bc_id = -1;
		wo_ist_bc_id =  write_block_to_db.find("bc-id:");
		//cout<<"wo_ist_bc_id#"<<wo_ist_bc_id<<"#"<<endl;
		if (wo_ist_bc_id > 0)
		{
			try{write_block_to_db = write_block_to_db.substr(wo_ist_bc_id,write_block_to_db.length());}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp write_block_to_db std::out_of_range"<<endl;}
			//cout<<"SCHREIBE DATENSATZ in DB in write_to_db.cpp z. 132#"<<write_block_to_db<<"#"<<endl;
		}
//cout<<"SCHREIBE DATENSATZ in DB in write_to_db.cpp z. 140#"<<write_block_to_db<<"#"<<endl;
//cout<<"letzter Remote Block der auch lokal existiert#"<<remote_letzter_block<<"#"<<endl;

	
//####################################################################		
//Newline \n und CR abschneiden für remote_letzter_block###
wo_ist_newline = -1;
wo_ist_cr = -1;
try{remote_letzter_block = remote_letzter_block.substr(wo_ist_newline + 1, remote_letzter_block.length() );}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp remote_letzter_block std::out_of_range"<<endl;}
wo_ist_newline = remote_letzter_block.find("\n");

if(wo_ist_newline != -1)
		{
			char chars4[] = "\n";
			for (unsigned int l = 0; l < strlen(chars4); ++l)
			{
				remote_letzter_block.erase(std::remove(remote_letzter_block.begin(), remote_letzter_block.end(), chars4[l]), remote_letzter_block.end());
			}

			wo_ist_cr = remote_letzter_block.find("\r");
			//write_block_to_db = write_block_to_db.substr(wo_ist_cr,write_block_to_db.length());
			try{remote_letzter_block = remote_letzter_block.substr(wo_ist_cr,remote_letzter_block.length());}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp remote_letzter_block std::out_of_range"<<endl;}
			
			char chars5[] = "\r";
			for (unsigned int m = 0; m < strlen(chars5); ++m)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				remote_letzter_block.erase(std::remove(remote_letzter_block.begin(), remote_letzter_block.end(), chars5[m]), remote_letzter_block.end());
			}

			char chars6[] = "\"";
			for (unsigned int l = 0; l < strlen(chars6); ++l)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				remote_letzter_block.erase(std::remove(remote_letzter_block.begin(), remote_letzter_block.end(), chars6[l]), remote_letzter_block.end());
			}
		}
remote_letzter_block.erase(remove_if(remote_letzter_block.begin(),remote_letzter_block.end(), invalidChar_linsert), remote_letzter_block.end());  


//############################
//Alles bis zu bc-id entfernen
wo_ist_bc_id = -1;
wo_ist_bc_id =  remote_letzter_block.find("bc-id:");
//cout<<"wo_ist_bc_id#"<<wo_ist_bc_id<<"#"<<endl;
if (wo_ist_bc_id > 0)
{
	try{remote_letzter_block = remote_letzter_block.substr(wo_ist_bc_id,remote_letzter_block.length());}catch( std::out_of_range& exception ){cout<<"Error write_to_db.cpp remote_letzter_block std::out_of_range"<<endl;}
	//cout<<"SCHREIBE DATENSATZ in DB in write_to_db.cpp z. 132#"<<write_block_to_db<<"#"<<endl;
}
//cout<<"letzter Remote Block der auch lokal existiert#"<<remote_letzter_block<<"#"<<endl;/*
//###########################################################################################
		
//cout<<"write_to_db.cpp z122 write_block_to_db GEFILTERT#"<<write_block_to_db<<"#"<<endl;
//cout<<"SCHREIBE DATENSATZ in DB in write_to_db.cpp z. 140#"<<write_block_to_db<<"#"<<endl;
//cout<<"letzter Remote Block der auch lokal existiert#"<<remote_letzter_block<<"#"<<endl;
//cout<<"SCHREIBE DATENSATZ in DB#"<<endl;
//getchar();



		
		int s4 = 666;
		//string bc_peer = "127.0.0.1";
		string bc_peer = config_file_parameter[2];
		
		//string bc_peer_port = "6379";
		string bc_peer_port = config_file_parameter[3];
		
		//bc_peer = erreichbare_peers[i];
		//bc_peer = "172.17.190.80";
		//cout<<"bc_peer#"<<bc_peer<<endl;
		//cout<<"Lese vorhandene Block Ketten ein"<<endl;
		
	
		struct hostent *host;//Hostname struktuieren
		host = gethostbyname(bc_peer.c_str()); //eventuell die IP in DNS Namen umwandeln
		
		struct sockaddr_in addr;
		addr.sin_addr = *(struct in_addr*)host->h_addr;
		//int s; 
		
		s4 = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
		
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
		setsockopt (s4, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout));
		setsockopt (s4, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
		connect_status = connect(s4,(struct sockaddr*)&addr, sizeof(addr));		//http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html
		
		//Redis Command Anzahl der Werte in der Liste
		
		//string bc_command = "LLEN blockchain_list\r\n";
		string bc_command;
		
		//bc_command = "flushall\r\n";
		//cout<<"bc_command#"<<bc_command<<"#"<<endl;
		//send(s4, bc_command.c_str(), bc_command.length(),0);//Daten senden
				
		//bc_command = "LPUSH 'blockchain_list' '" + write_block_to_db + "'\r\n";
		bc_command = "LINSERT \"blockchain_list\" BEFORE \"" + remote_letzter_block + "\" \"" + write_block_to_db + "\"\r\n";
		//cout<<"bc_command in write_to_db_linset.cpp z249#"<<bc_command<<"#"<<endl;
		//cout<<"bc_command in write_to_db.cpp z250 ###"<<write_block_to_db<<"###"<<endl;

		send(s4, bc_command.c_str(), bc_command.length(),0);//Daten senden
		//cout<<"bc_command z. 207#"<<bc_command<<endl;

		//bc_command = "RPOPLPUSH \"blockchain_list\" \"" + write_block_to_db + "\"\r\n";
		//redis-cli RPOPLPUSH blockchain_list

		string redis_quit_command = "quit\r\n" ;
		char* request2 = (char*)redis_quit_command.c_str();
		int send_status = 666;
		send_status = send(s4, request2, strlen(request2),0);
		//cout<<"send_status QUIT#"<<send_status<<endl;
		ssize_t bytes_1 = 0;
		char response[1024];
		bytes_1 = recv(s4, response, sizeof(response), 0);
		//cout<<"response QUIT#"<<response<<endl;
		bzero (response, sizeof(response));

		//cout<<"leere write_block_to_db und pure_bc_block in write_block_to_db.cpp"<<endl;
		//write_block_to_db = "";
		//pure_bc_block = "";

		//cout<<"ENDE write_to_db_linsert.cpp"<<endl;
		//cout<<"\t"<<endl;
		//cout<<"##########################################################################################################################"<<endl;
		close(s4);
		
//debug_file_1<<"write_to_db.cpp z216 bc_command#"<<bc_command<<"#"<<endl;

//###################################################
//Debug file schliesen.
//debug_file_1.close();
//###################################################



}



