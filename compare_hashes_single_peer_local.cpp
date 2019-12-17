//clear; rm -frv compare_hashes_single_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_single_peer_local.cpp

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
//Error Handling und Singal
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <csignal>
#include <cassert>
#include "assert.h"

using namespace std;

extern string local_block;
extern string zu_hashende_daten;
extern bool compare_hashes_local;
extern string peer_block;
extern bool compare_hashes_peer;

void compare_hashes_single_peer_local()
	{
		//cout<<"COMPARE HASHES BLOCKS"<<endl;
		cout<<"\e[1m"<<"compare_hashes_single_peer_local.cpp"<<"\e[0m"<<endl;
		//cout<<"local_block#"<<local_block<<endl;
		
//Lokaler Block hash berechnen#######################################################################################################
		
		int find_bc_id = -1;
		int prevoius_hash_bc_id = -1;

		//newline und CR abschneiden####
		int wo_ist_newline = -1;
		int wo_ist_cr = -1;
		wo_ist_newline = local_block.find("\n");
		if(wo_ist_newline != -1)
		{
			char chars[] = "\n";
			for (unsigned int i = 0; i < strlen(chars); ++i)
			{
				local_block.erase(std::remove(local_block.begin(), local_block.end(), chars[i]), local_block.end());
			}	
			char chars2[] = "\r";
			for (unsigned int j = 0; j < strlen(chars2); ++j)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				local_block.erase(std::remove(local_block.begin(), local_block.end(), chars2[j]), local_block.end());
			}
		}	
		//cout<<"local_block#"<<local_block<<endl;
		//########################

		find_bc_id = local_block.find("bc-id:");
		prevoius_hash_bc_id = local_block.find("prevoius_hash_bc-id");
		
		string local_transaction_data;

		if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1))
		{
			//cout<<"find_bc_id#"<<find_bc_id<<endl;
			//cout<<"prevoius_hash_bc_id#"<<prevoius_hash_bc_id<<endl;
			//local_transaction_data =local_block.substr(find_bc_id, prevoius_hash_bc_id - 3	);
			//local_transaction_data =local_block.substr(find_bc_id, prevoius_hash_bc_id - 9 );				//if 5 zeilen vorher
			//local_transaction_data =local_block.substr(find_bc_id, prevoius_hash_bc_id);				//if 5 zeilen vorher
			local_transaction_data =local_block.substr(find_bc_id, prevoius_hash_bc_id - 8);				//if 5 zeilen vorher prüfen ob nicht mit variabler besser ?????
			//cout<<"local_transaction_data#"<<local_transaction_data<<"#"<<endl;
		}
		else
		{
			cout<<"Datensatz Kaputt compare_hashes_single_peer_local.cpp z98"<<endl;
			exit (-1);
		}

		//cout<<"local_transaction_data#"<<local_transaction_data<<"#"<<endl;

		//Transaktiondaten hashen
		zu_hashende_daten = local_transaction_data ;
		void hasher();
		hasher();
		//cout<<"gehashtes zu_hashende_daten#"<<zu_hashende_daten<<"#"<<endl;
		string transaction_data_hash = zu_hashende_daten;

		prevoius_hash_bc_id = -1;
		prevoius_hash_bc_id = local_block.find("prevoius_hash_bc-id");
		string previous_hash ;
		
		if (prevoius_hash_bc_id != -1)
		{
			//cout<<"find_bc_id#"<<find_bc_id<<endl;
			//cout<<"prevoius_hash_bc_id#"<<prevoius_hash_bc_id<<endl;
			previous_hash = local_block.substr(prevoius_hash_bc_id, local_block.length());	//if 4 zeilen vorher
		}
		else
		{
			cout<<"Datesatz Kaputt Datesatz Kaputt compare_hashes_single_peer_local.cpp z99"<<endl;
			exit (-1);
		}
		//cout<<"previous_hash#"<<previous_hash<<"#"<<endl;
		
		if (previous_hash == "")
		{
			cout<<"KEIN PREVIOUS HASH GEFUFEN in compare_hashes_single_peer_local.cpp z106 "<<endl;
			exit (-1);
			//continue;
		}
		
		int wo_ist_hash_block = -1;
		wo_ist_hash_block = previous_hash.find("hash_block");
		if (wo_ist_hash_block != -1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}

		int wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = previous_hash.find(":");
		if (wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}

		int wo_ist_gatter = -1;
		wo_ist_gatter = previous_hash.find("#");
		if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}

		//cout<<"previous_hash####"<<previous_hash<<"###"<<endl;
					
		//Hash des Blocks erstellen
		zu_hashende_daten = "";
		zu_hashende_daten = transaction_data_hash + previous_hash;
		//cout<<transaction_data_hash + " # " + previous_hash;
		//cout<<"zu_hashende_daten transaction_data_hash + previous_hash#"<<zu_hashende_daten<<endl;
		void hasher();
		hasher();
		
		//was nun rauskommt, sollte gleich dem hash des blocks sein.
		//cout<<"gehashtes#"<<zu_hashende_daten<<"#"<<endl;
		string hash_block;
		wo_ist_hash_block = -1;
		wo_ist_hash_block = local_block.find("hash_block");
		if (wo_ist_hash_block != -1){hash_block = local_block.substr(wo_ist_hash_block,local_block.length());}

		int wo_ist_gpg_signature = -1;
		wo_ist_gpg_signature = hash_block.find("gpg_signature");
		if (wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}
		
		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = hash_block.find(":");
		if (wo_ist_doppelpunkt != -1){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}
		//cout<<"hash_block #"<<hash_block<<"#"<<endl;

		if (hash_block != zu_hashende_daten)
		{
			//cout<<"ACHTUNG Ketten Hashwerte sind ungleich !!!"<<endl;
			compare_hashes_local = false;
		}
		if (hash_block == zu_hashende_daten)
		{
			//cout<<"Lokaler Block Hash ist gleich"<<endl;
			compare_hashes_local = true;
		}
		
		//string hash_block_local = hash_block;
		string hash_block_local = zu_hashende_daten;

//Peer Block hash berechnen#######################################################################################################
		//cout<<"peer_block#"<<peer_block<<"#"<<endl;
		
		//newline und CR abschneiden####
		int wo_ist_newline2 = -1;
		int wo_ist_cr2 = -1;
		wo_ist_newline2 = peer_block.find("\n");
		if(wo_ist_newline2 != -1)
		{
			char chars3[] = "\n";
			for (unsigned int i = 0; i < strlen(chars3); ++i)
			{
				peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars3[i]), peer_block.end());
			}	
			char chars4[] = "\r";
			for (unsigned int j = 0; j < strlen(chars4); ++j)
			{
				// you need include <algorithm> to use general algorithms like std::remove()
				peer_block.erase(std::remove(peer_block.begin(), peer_block.end(), chars4[j]), peer_block.end());
			}
		}	
		//cout<<"peer_block#"<<peer_block<<"#"<<endl;
		//########################
		
		find_bc_id = -1;
		prevoius_hash_bc_id = -1;
		
		find_bc_id = peer_block.find("bc-id:");
		prevoius_hash_bc_id = peer_block.find("prevoius_hash_bc-id");
		
		string peer_transaction_data;
		
		//if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1)){peer_transaction_data = peer_block.substr(find_bc_id, prevoius_hash_bc_id - 9 );}
		if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1)){peer_transaction_data = peer_block.substr(find_bc_id, prevoius_hash_bc_id - 8 );}

		//cout<<"peer_transaction_data#"<<peer_transaction_data<<"#"<<endl;

		//Transaktiondaten hashen
		zu_hashende_daten = peer_transaction_data ;
		void hasher();
		hasher();
		//cout<<"gehashtes zu_hashende_daten#"<<zu_hashende_daten<<"#"<<endl;
		transaction_data_hash = zu_hashende_daten;

		prevoius_hash_bc_id = -1;
		prevoius_hash_bc_id = peer_block.find("prevoius_hash_bc-id");
		previous_hash = "";
		if (prevoius_hash_bc_id != -1){previous_hash = peer_block.substr(prevoius_hash_bc_id, peer_block.length());}

		wo_ist_hash_block = -1;
		wo_ist_hash_block = previous_hash.find("hash_block");
		if (wo_ist_hash_block != -1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}

		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = previous_hash.find(":");
		if (wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}

		wo_ist_gatter = -1;
		wo_ist_gatter = previous_hash.find("#");
		if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}
		//cout<<"previous_hash####"<<previous_hash<<"###"<<endl;
	
		//Hash des Blocks erstellen
		zu_hashende_daten = "";
		zu_hashende_daten = transaction_data_hash + previous_hash;
		//cout<<transaction_data_hash + " # " + previous_hash;
		//cout<<"zu_hashende_daten transaction_data_hash + previous_hash#"<<zu_hashende_daten<<endl;
		void hasher();
		hasher();
		
		//was nun rauskommt, sollte gleich dem hash des blocks sein.
		//cout<<"gehashtes####"<<zu_hashende_daten<<endl;

		hash_block = "";
		wo_ist_hash_block = -1;
		wo_ist_hash_block = peer_block.find("hash_block");
		if (wo_ist_hash_block != -1){hash_block = peer_block.substr(wo_ist_hash_block,peer_block.length());}

		wo_ist_gpg_signature = -1;
		wo_ist_gpg_signature = hash_block.find("gpg_signature");
		if (wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}

		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = hash_block.find(":");
		if (wo_ist_doppelpunkt != -1){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}

		//cout<<"hash_block ###"<<hash_block<<"####"<<endl;
		
		if (hash_block != zu_hashende_daten)
		{
			//cout<<"ACHTUNG PEER Ketten Hashwerte sind ungleich !!!"<<endl;
			compare_hashes_peer = false;
		}
		if (hash_block == zu_hashende_daten)
		{
			//cout<<"PEER Block Hash ist gleich"<<endl;
			compare_hashes_peer = true;
		}
		
		//string hash_block_peer = hash_block;
		string hash_block_peer = zu_hashende_daten;
	
		cout<<"ENDE"<<endl;
	}
	