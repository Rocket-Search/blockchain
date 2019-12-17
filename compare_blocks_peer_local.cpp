//clear; rm -frv compare_blocks_peer_local.o; g++-7 -g -fPIC -Wall -c compare_blocks_peer_local.cpp
//Test manipulationskommando für Redis

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

extern string local_block;
extern string peer_block;
extern string block_nummer;
extern bool compare_blocks_peer_local_bool;

void compare_blocks_peer_local()
	{
		//cout<<"compare_blocks_peer_local()"<<endl;
		//cout<<"\e[1m"<<"compare_blocks_peer_local.cpp"<<"\e[0m"<<endl;
		
		char chars[] = "\n";
		for (unsigned int i = 0; i < strlen(chars); ++i)
		{
			local_block.erase(std::remove(local_block.begin(), local_block.end(), chars[i]), local_block.end());
			peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars[i]), peer_block.end());
		}
		/*
		for (unsigned int i = 0; i < strlen(chars); ++i)
		{
			local_block.erase(std::remove(local_block.begin(), local_block.end(), chars[i]), local_block.end());
			peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars[i]), peer_block.end());
		}
		local_block = local_block.erase(local_block.find_last_not_of("\n"));
		peer_block = peer_block.erase(peer_block.find_last_not_of("\n"));
		*/
		char chars2[] = "\r";
		for (unsigned int j = 0; j < strlen(chars2); ++j)
		{
			local_block.erase(std::remove(local_block.begin(), local_block.end(), chars2[j]), local_block.end());
			peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars2[j]), peer_block.end());
		}
		/*
		char chars3[] = "\"";
		for (unsigned int k = 0; k < strlen(chars3); ++k)
		{
			local_block.erase(std::remove(local_block.begin(), local_block.end(), chars3[k]), local_block.end());
			peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars3[k]), peer_block.end());
		}
		*/
		//cout<<"local_block#"<<local_block<<endl;
		//cout<<"peer_block#"<<peer_block<<endl;
		//####################################
		//Alles bis bc-id abschneiden
		//LOKAL
		int wo_ist_bc_id = -1;
		wo_ist_bc_id =  local_block.find("bc-id:");
		//cout<<"wo_ist_bc_id#"<<wo_ist_bc_id<<"#"<<endl;
		if (wo_ist_bc_id > 0)
		{
		try{local_block = local_block.substr(wo_ist_bc_id,local_block.length());}catch( std::out_of_range& exception ){cout<<"Error compare_blocks_peer_local.cpp local_block std::out_of_range"<<endl;}
		}
		//REMOTE/PEER
		wo_ist_bc_id = -1;
		wo_ist_bc_id =  peer_block.find("bc-id:");
		//cout<<"wo_ist_bc_id#"<<wo_ist_bc_id<<"#"<<endl;
		if (wo_ist_bc_id > 0)
		{
		try{peer_block = peer_block.substr(wo_ist_bc_id,peer_block.length());}catch( std::out_of_range& exception ){cout<<"Error compare_blocks_peer_local.cpp peer_block std::out_of_range"<<endl;}
		}
		//cout<<"local_block#"<<local_block<<endl;
		//cout<<"peer_block #"<<peer_block<<endl;
		
//cout<<"Lokaler BLOCK #"<<local_block<<"#"<<endl;
//cout<<endl;
//cout<<"Remote BLOCK  #"<<peer_block<<"#"<<endl;

		if (peer_block == "")
		{
			//cout<<"KEIN REMOTE BLOCK ERHALTEN in compare_blocks_peer_local.cpp"<<endl;
			//continue;
			return;
		}
		//####################################
		/*
		cout<<"COMPARE BLOCKS"<<endl;	cout<<endl;
		cout<<"LOCAL BLOCK#"<<local_block<<endl;
		cout<<endl;
		cout<<"PEER BLOCK #"<<peer_block<<endl;
		*/
		//Validierunsg Kriterien
			//alle chars müssen gleich sein
			//GPG Signature muss valide sein
			//Transaczion Hases prüfen
			//Transaczion Hases prüfen Hashes mit GPG signature
		//Manuelle User Masnahmen
			//Peer Kette nach lokal laden
			//Lokale Kette nach Peer laden
		
		//Reine Zeichen vergleichen

		//cout<<"Lokaler BLOCK #"<<local_block<<"#"<<endl;
		//cout<<endl;
		//cout<<"Remote BLOCK  #"<<peer_block<<"#"<<endl;

		//int result = strcmp(lokal_ip_adresse.c_str(), bc_server.c_str());		
		//cout<<"strcmp result#"<<result<<endl;
		//if (result == 0)
		//string test_cin_2; cout<<"CIN"<<endl; cin>>test_cin_2;
		//strcmp ?????

		if (local_block != peer_block)
		{
			
			//cout<<"ACHTUNG Kette ist unterschiedlich !!!!!!!!"<<endl;
			/*
			cout<<"Manuelle Tätigkeit notwendig"<<endl;
			cout<<"LOCAL BLOCK#"<<local_block<<endl;
			cout<<"PEER BLOCK#"<<peer_block<<endl;
			cout<<"block_nummer#"<<block_nummer<<endl;
			*/
			compare_blocks_peer_local_bool = false;
		}
		else
		{
			//cout<<"Ketten sind gleich"<<endl;
			compare_blocks_peer_local_bool = true;
		}
		
		//cout<<"ENDE compare_blocks_peer_local.cpp"<<endl;		
//cout<<"ENDE"<<endl;
	}