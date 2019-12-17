//clear; rm -frv compare_hashes_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_peer_local.cpp

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
extern string peer_block;
extern string block_nummer;
extern bool compare_blocks_peer_local_bool;
extern bool compare_hashes_local;
extern bool compare_hashes_peer;
extern bool compare_hashes_cross_peer_local;
extern bool compare_hashes_previous_blocks;
extern string blocks_from_db;
extern string redis_command_from_main;
extern string erreichbare_peers_fuer_read_peer_single_block;
extern unsigned long long block_nummer_fuer_read_peer_single_block;
extern unsigned long long zufall_pruef_nummer; 
extern bool start_compare_20_blocks_hashes;
extern vector<string> config_file_parameter;

string zu_hashende_daten;


void compare_hashes_peer_local()
	{
		//cout<<"\e[1m"<<"compare_hashes_peer_local.cpp"<<"\e[0m"<<endl;
		
		//cout<<"COMPARE HASHES BLOCKS"<<endl;
		//cout<<endl;
		//cout<<"LOCAL BLOCK#"<<local_block<<endl;
		//cout<<endl;
		//cout<<"PEER BLOCK #"<<peer_block<<endl;
		
		//Bsp. Block. Mechanik
		/*		
		LOCAL BLOCK#$903bc-id: 3 # timestamp: 20.10.2018 16:36:04.623207399 # Transaktion 3 data: # 2 20181020-16:36:04 # prevoius_hash_bc-id 2: baf3be237c24588ca9749d31d9d76ce0cd5ce97a1d7a933235c2ae417353a43d6ecb64058fbefeed5b5d51d3a774e5e908c5bb344b5a72d2f1159f541fccc5e8 #
		hash_block 3: da32f4f9d171344929f89d6a20cd46825f97ac02f8f64e415dd2b1ca3b68dab0d84ca0c31a31d95b2550a8e8e6dfca313e8e87f4521b6eb7a7e1296f9f0b224f # gpg_signature: -----BEGIN PGP SIGNED MESSAGE-----@Hash: SHA256@@da32f4f9d171344929f89d6a20cd46825f97ac02f8f64e415dd2b1ca3
		b68dab0d84ca0c31a31d95b2550a8e8e6dfca313e8e87f4521b6eb7a7e1296f9f0b224f@-----BEGIN PGP SIGNATURE-----@@iLMEAQEIAB0WIQRDkhUryzl5r0a8nTXognSsR0t/AwUCW8s9VAAKCRDognSsR0t/@A3yUA/0YKtfkwRwEg8P5UmhMqzL3tOs827r3Sqx/llqc/LkqQuTSR15dnsMHcf/H@ke8JB6F7AX6zX0C62U8KEYK3eJzbxLc/N8
		miDAeh9JaKIaaXR3S/UqzOZ6M1kuGa@vouRiaLUgCVitngAwtShnk/t6TFbSxo667DaGdWM9o0mWbgK1w==@=r9n+@-----END PGP SIGNATURE-----@

		PEER BLOCK #$903bc-id: 3 # timestamp: 20.10.2018 16:36:04.623207399 # Transaktion 3 data: # 2 20181020-16:36:04 # prevoius_hash_bc-id 2: baf3be237c24588ca9749d31d9d76ce0cd5ce97a1d7a933235c2ae417353a43d6ecb64058fbefeed5b5d51d3a774e5e908c5bb344b5a72d2f1159f541fccc5e8 #
		hash_block 3: da32f4f9d171344929f89d6a20cd46825f97ac02f8f64e415dd2b1ca3b68dab0d84ca0c31a31d95b2550a8e8e6dfca313e8e87f4521b6eb7a7e1296f9f0b224f # gpg_signature: -----BEGIN PGP SIGNED MESSAGE-----@Hash: SHA256@@da32f4f9d171344929f89d6a20cd46825f97ac02f8f64e415dd2b1ca3
		b68dab0d84ca0c31a31d95b2550a8e8e6dfca313e8e87f4521b6eb7a7e1296f9f0b224f@-----BEGIN PGP SIGNATURE-----@@iLMEAQEIAB0WIQRDkhUryzl5r0a8nTXognSsR0t/AwUCW8s9VAAKCRDognSsR0t/@A3yUA/0YKtfkwRwEg8P5UmhMqzL3tOs827r3Sqx/llqc/LkqQuTSR15dnsMHcf/H@ke8JB6F7AX6zX0C62U8KEYK3eJzbxLc/N8
		miDAeh9JaKIaaXR3S/UqzOZ6M1kuGa@vouRiaLUgCVitngAwtShnk/t6TFbSxo667DaGdWM9o0mWbgK1w==@=r9n+@-----END PGP SIGNATURE-----@
		*/
		/*
		//Validierungsvorgehensweise:
		1. echo -n "bc-id: 3 # timestamp: 20.10.2018 16:36:04.623207399 # Transaktion 3 data: # 2 20181020-16:36:04" | openssl sha512
			20f304cfa5d5962dc2ab64cd0bcd27852477235ae9a1962382290e7b0a52cd094ece16943137fed45c855e5b1d8077ea5ebf41d79dbe86637b424b14bc6803e9
		2. Hash aus 1. plus Previous hash, direkt dran"
		echo -n "20f304cfa5d5962dc2ab64cd0bcd27852477235ae9a1962382290e7b0a52cd094ece16943137fed45c855e5b1d8077ea5ebf41d79dbe86637b424b14bc6803e9baf3be237c24588ca9749d31d9d76ce0cd5ce97a1d7a933235c2ae417353a43d6ecb64058fbefeed5b5d51d3a774e5e908c5bb344b5a72d2f1159f541fccc5e8" | openssl sha512
			da32f4f9d171344929f89d6a20cd46825f97ac02f8f64e415dd2b1ca3b68dab0d84ca0c31a31d95b2550a8e8e6dfca313e8e87f4521b6eb7a7e1296f9f0b224f
		*/	
		
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
		/*
		if (peer_block == "")
		{
			cout<<"KEIN REMOTE BLOCK ERHALTEN in compare_blocks_peer_local.cpp"<<endl;
			//continue;
			return;
		}
		*/
		//cout<<"local_block#"<<local_block<<endl;
		//cout<<"peer_block #"<<peer_block<<endl;
		//cout<<endl;
		//####################################


//Lokaler Block hash berechnen#######################################################################################################
		int find_bc_id = -1;
		int prevoius_hash_bc_id = -1;
		
		find_bc_id = local_block.find("bc-id:");
		prevoius_hash_bc_id = local_block.find("prevoius_hash_bc-id");
		
		string local_transaction_data;

		if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1))
		{
			//cout<<"find_bc_id#"<<find_bc_id<<endl;
			//cout<<"prevoius_hash_bc_id#"<<prevoius_hash_bc_id<<endl;
			local_transaction_data =local_block.substr(find_bc_id, prevoius_hash_bc_id - 3	);			//substr out of range wird 4 zeilen vorher abgefangen
		}
		else
		{
			cout<<"Datesatz Kaputt"<<endl;
			//exit(-1);
		}

		//cout<<"local_transaction_data####"<<local_transaction_data<<"###"<<endl;
		
		//Transaktiondaten hashen
		zu_hashende_daten = local_transaction_data ;
		void hasher();
		hasher();
		//cout<<"Transaktionsdaten gehasht#"<<zu_hashende_daten<<"#"<<endl;
		string transaction_data_hash = zu_hashende_daten;
		
		prevoius_hash_bc_id = -1;
		prevoius_hash_bc_id = local_block.find("prevoius_hash_bc-id");
		string previous_hash ;
		
		if (prevoius_hash_bc_id != -1)
		{
			//cout<<"find_bc_id#"<<find_bc_id<<endl;
			//cout<<"prevoius_hash_bc_id#"<<prevoius_hash_bc_id<<endl;
			previous_hash = local_block.substr(prevoius_hash_bc_id, local_block.length());		//if 3 zeilen vorher
		}
		else
		{
			cout<<"Datesatz Kaputt"<<endl;
			//exit(-1);
		}

		int wo_ist_hash_block = -1;
		wo_ist_hash_block = previous_hash.find("hash_block");
		//cout<<"previous_hash SUBSTR()"<<endl;
		//previous_hash = previous_hash.substr(0 , wo_ist_hash_block);
		//if (wo_ist_hash_block != -1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block); }else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if (wo_ist_hash_block != -1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block); }else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}		

		int wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = previous_hash.find(":");
		//previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());
		//if (wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if (wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}			
		
		int wo_ist_gatter = -1;
		wo_ist_gatter = previous_hash.find("#");
		//previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);
		//if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit (-1);}
		if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}
		//cout<<"previous_hash####"<<previous_hash<<"###"<<endl;
		//cout<<"TR DATA + PREV HASH#"<<transaction_data_hash + " + "+ previous_hash<<endl;				
	
		//Hash des Blocks erstellen
		zu_hashende_daten = "";
		zu_hashende_daten = transaction_data_hash + previous_hash;
		//cout<<"TR DATA + PREV HASH#"<<transaction_data_hash + "            " + previous_hash;
		//cout<<"zu_hashende_daten transaction_data_hash + previous_hash#"<<zu_hashende_daten<<endl;
		void hasher();
		hasher();
		
		//was nun rauskommt, sollte gleich dem hash des blocks sein.
		//cout<<"Ergebnis TR+Prev Hash: gehashtes####"<<zu_hashende_daten<<endl;
		string hash_block;
		wo_ist_hash_block = -1;
		wo_ist_hash_block = local_block.find("hash_block");
		//hash_block = local_block.substr(wo_ist_hash_block,local_block.length());
		//if (wo_ist_hash_block != -1){hash_block = local_block.substr(wo_ist_hash_block,local_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit (-1);}
		if (wo_ist_hash_block != -1){hash_block = local_block.substr(wo_ist_hash_block,local_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}
	
		int wo_ist_gpg_signature = -1;
		wo_ist_gpg_signature = hash_block.find("gpg_signature");
		//hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);
		//if(wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit (-1);}
		if(wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}
		
		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = hash_block.find(":");
		//hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());
		//if (wo_ist_doppelpunkt != 0){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit (-1);}
		if (wo_ist_doppelpunkt != 0){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}
		//cout<<"hash_block ###"<<hash_block<<"####"<<endl;

		//cout<<endl;		
		//cout<<"hash_block in compare_hashes_peer_local.cpp z. 222       #"<<hash_block<<"#"<<endl;
		//cout<<"zu_hashende_daten in compare_hashes_peer_local.cpp z. 222#"<<zu_hashende_daten<<"#"<<endl;
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
		find_bc_id = -1;
		prevoius_hash_bc_id = -1;
		
		find_bc_id = peer_block.find("bc-id:");
		prevoius_hash_bc_id = peer_block.find("prevoius_hash_bc-id");
		string peer_transaction_data;
		//peer_transaction_data = peer_block.substr(find_bc_id, prevoius_hash_bc_id - 3	);
		//if (prevoius_hash_bc_id != -1){peer_transaction_data = peer_block.substr(find_bc_id, prevoius_hash_bc_id - 3);}else{cout<<"out of range peer_transaction_data in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if (prevoius_hash_bc_id != -1){peer_transaction_data = peer_block.substr(find_bc_id, prevoius_hash_bc_id - 3);}else{cout<<"out of range peer_transaction_data in compare_hashes_peer_local.cpp"<<endl;}
		//cout<<"peer_transaction_data####"<<peer_transaction_data<<"###"<<endl;
	
		//Transaktiondaten hashen
		zu_hashende_daten = peer_transaction_data ;
		void hasher();
		hasher();
		//cout<<"gehashtes zu_hashende_daten#"<<zu_hashende_daten<<"#"<<endl;
		transaction_data_hash = zu_hashende_daten;
		
		prevoius_hash_bc_id = -1;
		prevoius_hash_bc_id = peer_block.find("prevoius_hash_bc-id");
		previous_hash = "";
		//previous_hash = peer_block.substr(prevoius_hash_bc_id, peer_block.length());
		//if (prevoius_hash_bc_id != -1){previous_hash = peer_block.substr(prevoius_hash_bc_id, peer_block.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if (prevoius_hash_bc_id != -1){previous_hash = peer_block.substr(prevoius_hash_bc_id, peer_block.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}
		
		wo_ist_hash_block = -1;
		wo_ist_hash_block = previous_hash.find("hash_block");
		//previous_hash = previous_hash.substr(0 , wo_ist_hash_block);
		//if (wo_ist_hash_block !=1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if (wo_ist_hash_block != -1){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}		
		
		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = previous_hash.find(":");
		//previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());
		//if(wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if(wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}
		
		wo_ist_gatter = -1;
		wo_ist_gatter = previous_hash.find("#");
		//previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);
		//if(wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if(wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}
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
		//hash_block = peer_block.substr(wo_ist_hash_block,peer_block.length());
		//if(wo_ist_hash_block != -1){hash_block = peer_block.substr(wo_ist_hash_block,peer_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if(wo_ist_hash_block != -1){hash_block = peer_block.substr(wo_ist_hash_block,peer_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}

		wo_ist_gpg_signature = -1;
		wo_ist_gpg_signature = hash_block.find("gpg_signature");
		//hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);
		//if(wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if(wo_ist_gpg_signature != -1){hash_block = hash_block.substr(0, wo_ist_gpg_signature - 3);}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}

		wo_ist_doppelpunkt = -1;
		wo_ist_doppelpunkt = hash_block.find(":");
		//hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());
		//if(wo_ist_doppelpunkt != -1){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if(wo_ist_doppelpunkt != -1){hash_block = hash_block.substr(wo_ist_doppelpunkt + 2,hash_block.length());}else{cout<<"out of range hash_block in compare_hashes_peer_local.cpp"<<endl;}
		//cout<<"hash_block ###"<<hash_block<<"####"<<endl;

		//cout<<"hash_block in compare_hashes_peer_local.cpp z. 314       #"<<hash_block<<"#"<<endl;
		//cout<<"zu_hashende_daten in compare_hashes_peer_local.cpp z. 315#"<<zu_hashende_daten<<"#"<<endl;
	
		if (hash_block != zu_hashende_daten)
		{
			//cout<<"ACHTUNG Ketten Hashwerte sind ungleich !!!"<<endl;
			compare_hashes_peer = false;
		}
		if (hash_block == zu_hashende_daten)
		{
			//cout<<"PEER Block Hash ist gleich"<<endl;
			compare_hashes_peer = true;
		}
		
		//string hash_block_peer = hash_block;
		string hash_block_peer = zu_hashende_daten;
//##############################################################################################################
//Hash kreuz check. Block local gegen block peer !!!
		//cout<<"hash_block_peer  #"<<hash_block_peer<<"##"<<endl;
		//cout<<"hash_block_local #"<<hash_block_local<<"##"<<endl;
		if (hash_block_peer != hash_block_local)
		{
			//cout<<"CROSS CHECK FAIL!!!"<<endl;
			compare_hashes_cross_peer_local = false;
		}
		if (hash_block_peer == hash_block_local)
		{
			//cout<<"Cross Check Peer <-> Lokal Block Hash ist gleich"<<endl;
			compare_hashes_cross_peer_local = true;
		}
//##############################################################################################################		
//20 Blöcke (oder Zufallsanzahl) davor hash kreuz checken.
		//cout<<"20 Block vorher block_nummer"<<endl;
	
		//Länger der Kette feststellen 
		redis_command_from_main = "LLEN blockchain_list\r\n";
		void read_all_chains_from_db();
		read_all_chains_from_db();
		//cout<<"LLEN blockchain_list #"<<blocks_from_db<<endl;
		//cout<<"block_nummer# "<<block_nummer<<endl;
		
		//Redis Blocknummer nach long konvertieren
		unsigned long long redis_block_nummer_long_long = 0;
		redis_block_nummer_long_long = stoll(block_nummer);
		//cout<<"redis_block_nummer_long_long#"<<redis_block_nummer_long_long<<"#"<<endl;
		
//##########################################################################################################
//Aktuell geladen Block als Basis Block festhalten und von diesem aus 20 Blöcke herunterechnen.####
		find_bc_id = -1;
		int find_timestamp = -1;
		
		//bc-id Nummer filtern
		string bc_id_nummer;
		find_bc_id = local_block.find("bc-id:");
		find_timestamp = local_block.find("timestamp:");
		//bc_id_nummer = local_block.substr(find_bc_id + 7, find_timestamp - 10);
		//if ( find_timestamp != -1){bc_id_nummer = local_block.substr(find_bc_id + 7, find_timestamp - 10);}else{cout<<"out of range bc_id_nummer in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
		if ( find_timestamp != -1){bc_id_nummer = local_block.substr(find_bc_id + 7, find_timestamp - 10);}else{cout<<"out of range bc_id_nummer in compare_hashes_peer_local.cpp"<<endl;}

		//cout<<"bc_id_nummer###"<<bc_id_nummer<<"###"<<endl;
		unsigned long long bc_id_block_nummer_long_long = 0;
		bc_id_block_nummer_long_long = stoll(bc_id_nummer);
		//cout<<"bc_id_block_nummer_long_long###"<<bc_id_block_nummer_long_long<<"###"<<endl;
		
		//Hier einen Zufalls Port wählen und diesen analysieren # bc-id minus 20 Blöcke sofern aktuelle Position schon über 20 liegt
		//if (bc_id_block_nummer_long_long > 20)
		//cout<<"PEER###"<<peer_block<<"###"<<endl;
		//cout<<"LOCAL###"<<local_block<<"###"<<endl;

		//Zufallszahl wird in "read_peer_blocks.cpp" erzeugt		
		//unsigned long long zufall_pruef_nummer = 91;
		//unsigned long long zufall_pruef_nummer = 21; 
		//zufall_pruef_nummer = rand() % 100 + 50; 
		//cout<<"zufall_pruef_nummer###"<<zufall_pruef_nummer<<"###"<<endl;

		unsigned long long zufall_pruef_nummer_temp;
		
		if (bc_id_block_nummer_long_long == zufall_pruef_nummer)
		{
			start_compare_20_blocks_hashes = true;
			
			//cout<<"aktuelle Position ist ÜBER 20"<<endl;
			//cout<<"bc_id_block_nummer_long_long#"<<bc_id_block_nummer_long_long<<endl;
			unsigned long long minus_20_bloecke = 0;
			
			//for (unsigned long long i = 0; i < 20; i++)
			for (int i = 0; i < 20; i++)
			{
//Lokalen Block nummer XYZ herausholen#############################################################################
				//Anzahl Max Ketten minus aktuelle redis Block gleich bc-id real block
				zufall_pruef_nummer_temp = zufall_pruef_nummer - i ;
					string i_string;
					stringstream strstream;
					strstream << zufall_pruef_nummer_temp;
					strstream >> i_string;
				redis_command_from_main = "LINDEX blockchain_list " + i_string + "\r\n";
				//cout<<"redis_command_from_main in compare_hashes_peer_local#"<<redis_command_from_main<<endl;
				//cout<<local_block<<endl;
				blocks_from_db = "";
				void read_all_chains_from_db();
				read_all_chains_from_db();
				//cout<<"LOKAL BLOCK####"<<blocks_from_db<<"###"<<endl;
				string local_cross_check_block = blocks_from_db;
				
//Peer nach 20 Blöcken fragen####################################################################################
				//cout<<"PEER###"<<peer_block<<"###"<<endl;
				//cout<<"erreichbare_peers_fuer_read_peer_single_block###"<<erreichbare_peers_fuer_read_peer_single_block<<endl;
				//cout<<"block_nummer_fuer_read_peer_single_block###"<<block_nummer_fuer_read_peer_single_block<<endl;
				block_nummer_fuer_read_peer_single_block = stoll(i_string);
				blocks_from_db = "";
				void read_peer_single_block();
				read_peer_single_block();
				//cout<<"PEER BLOCK###"<<blocks_from_db<<endl;;
				string peer_cross_check_block = blocks_from_db;
				
				
//Bei beiden Blocken die Werte Filtern und Hashes Kreuz Checken#################################################
				//gefiltertes in arraay schreiben und in einem rutsch kreuz checken
//Lokal#####################################
				//cout<<endl<<"Lokaler Block         ###"<<local_cross_check_block<<endl;
				find_bc_id = -1;
				prevoius_hash_bc_id = -1;
				find_bc_id = local_cross_check_block.find("bc-id:");
				prevoius_hash_bc_id = local_cross_check_block.find("prevoius_hash_bc-id");
				local_transaction_data = "";
				if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1)){	local_transaction_data =local_cross_check_block.substr(find_bc_id, prevoius_hash_bc_id - 9);}else{cout<<"Datesatz Kaputt"<<endl;}
				//cout<<"local_transaction_data####"<<local_transaction_data<<"###"<<endl;
				//Transaktiondaten hashen
				zu_hashende_daten = local_transaction_data ;
				void hasher();
				hasher();
				//cout<<"gehashtes zu_hashende_daten#"<<zu_hashende_daten<<"#"<<endl;
				transaction_data_hash = "";
				transaction_data_hash = zu_hashende_daten;

				//Prevois Block kompletten Block hash filtern
				prevoius_hash_bc_id = -1;
				prevoius_hash_bc_id = local_cross_check_block.find("prevoius_hash_bc-id");
				previous_hash = "";
				//if (prevoius_hash_bc_id != -1){previous_hash = local_cross_check_block.substr(prevoius_hash_bc_id, local_block.length());}else{cout<<"prevoius_hash_bc_id Datesatz Kaputt"<<endl;exit(-1);}
				if (prevoius_hash_bc_id != -1){previous_hash = local_cross_check_block.substr(prevoius_hash_bc_id, local_block.length());}else{cout<<"prevoius_hash_bc_id Datesatz Kaputt"<<endl;}
				//cout<<"Kreuz check previous_hash#"<<previous_hash<<endl;
				
				wo_ist_hash_block = -1;
				wo_ist_hash_block = previous_hash.find("hash_block");
				//previous_hash = previous_hash.substr(0 , wo_ist_hash_block);
				//if(wo_ist_hash_block != -1 ){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
				if(wo_ist_hash_block != -1 ){previous_hash = previous_hash.substr(0 , wo_ist_hash_block);}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}
		
				wo_ist_doppelpunkt = -1;
				wo_ist_doppelpunkt = previous_hash.find(":");
				//previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());
				//if(wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;exit(-1);}
				if(wo_ist_doppelpunkt != -1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt, previous_hash.length());}else{cout<<"out of range previous_hash in compare_hashes_peer_local.cpp"<<endl;}				
		
				//cout<<"previous_hash#"<<previous_hash<<endl;
				wo_ist_gatter = -1;
				wo_ist_gatter = previous_hash.find("#");
				//cout<<"wo_ist_gatter"<<wo_ist_gatter<<endl;
				//if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"previous_hash Datesatz Kaputt"<<endl; exit(-1);}
				if (wo_ist_gatter != -1){previous_hash = previous_hash.substr(0 + 2 , wo_ist_gatter - 3);}else{cout<<"previous_hash Datesatz Kaputt"<<endl;}				
				//cout<<"previous_hash####"<<previous_hash<<"###"<<endl;
				
				//Hash des Blocks erstellen
				zu_hashende_daten = "";
				zu_hashende_daten = transaction_data_hash + previous_hash;
				//cout<<transaction_data_hash + " # " + previous_hash<<endl;
				//cout<<"zu_hashende_daten transaction_data_hash + previous_hash#"<<zu_hashende_daten<<endl;
				void hasher();
				hasher();
				//cout<<"Aktuelle Block LOKAL Hash Wert####"<<zu_hashende_daten<<"###"<<endl;		
				string lokaler_hash_block;
				lokaler_hash_block = zu_hashende_daten;

	//Peer##################################
				//Aktueller Lokaler Block Hashwert muss mit dem Previos Haswert vom Peer übereinstimmern
				//cout<<"Aktuelle Block LOKAL Hash Wert####"<<zu_hashende_daten<<"###"<<endl;
				//Peer filttern
				//get peer block number XY
				//cout<<endl<<"peer_cross_check_block#"<<peer_cross_check_block<<endl;
				find_bc_id = -1;
				prevoius_hash_bc_id = -1;
				find_bc_id = peer_cross_check_block.find("bc-id:");
				prevoius_hash_bc_id = peer_cross_check_block.find("prevoius_hash_bc-id");
				//cout<<"PEER prevoius_hash_bc_id##"<<prevoius_hash_bc_id<<endl;
				peer_transaction_data = "";
				//if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1)){peer_transaction_data =peer_cross_check_block.substr(find_bc_id, prevoius_hash_bc_id - 9);}else{cout<<"Datesatz Kaputt"<<endl; exit(-1);}
				if ((find_bc_id != -1) && (prevoius_hash_bc_id != -1)){peer_transaction_data =peer_cross_check_block.substr(find_bc_id, prevoius_hash_bc_id - 9);}else{cout<<"Datesatz Kaputt"<<endl;}
				//cout<<"PEER transaction data####"<<peer_transaction_data<<"###"<<endl;
				
				//Transaktiondaten hashen
				zu_hashende_daten = peer_transaction_data ;
				void hasher();
				hasher();
				//cout<<"gehashtes zu_hashende_daten#"<<zu_hashende_daten<<"#"<<endl;
				transaction_data_hash = "";
				transaction_data_hash = zu_hashende_daten;
				//cout<<"Aktuelle Block PEER Hash Wert####"<<zu_hashende_daten<<"###"<<endl;		

				//Hash von Previous Block mit filtern und mitverhashen.
				//cout<<"peer_cross_check_block##"<<peer_cross_check_block<<endl;
				wo_ist_hash_block = -1;
				previous_hash = "";
				wo_ist_hash_block = peer_cross_check_block.find("hash_block");
				//cout<<"PEER wo_ist_hash_block##"<<wo_ist_hash_block<<endl;
				if (wo_ist_hash_block != -1){previous_hash = peer_cross_check_block.substr(0 , wo_ist_hash_block);}else{cout<<"PEER previous_hash Datesatz Kaputt"<<endl; (exit -1); }
				//cout<<"PEER previous_hash##"<<previous_hash<<endl;
				
				wo_ist_doppelpunkt = -1;
				wo_ist_doppelpunkt = previous_hash.rfind(":");
				//if (wo_ist_doppelpunkt !=1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt + 2 , previous_hash.length());}else{cout<<"Peer previous_hash Datesatz Kaputt"<<endl;exit(-1);}
				if (wo_ist_doppelpunkt !=1){previous_hash = previous_hash.substr(wo_ist_doppelpunkt + 2 , previous_hash.length());}else{cout<<"Peer previous_hash Datesatz Kaputt"<<endl;}				
				
				//previous_hash = previous_hash.substr(0,128);		//SHA512 feste Länge von 128 Zeichen
				
				//SHA512 feste Länge von 128 Zeichen				
				try{ previous_hash = previous_hash.substr(0,128);}catch( std::out_of_range& exception ){cout<<"Error compare_hashes_peer_local.cpp z. 474 previous_hash std::out_of_range"<<endl;}
				
				//cout<<"PEER previous_hash###"<<previous_hash<<"###"<<endl;
				string peer_previous_hash;
				peer_previous_hash = previous_hash;

				zu_hashende_daten = "";
				zu_hashende_daten = transaction_data_hash + previous_hash;
				//cout<<transaction_data_hash + " # " + previous_hash<<endl;
				//cout<<"zu_hashende_daten transaction_data_hash + previous_hash#"<<zu_hashende_daten<<endl;
				void hasher();
				hasher();
				//cout<<"Aktuelle Block PEER Hash Wert####"<<zu_hashende_daten<<"###"<<endl;	
				string peer_hash_block;
				peer_hash_block = zu_hashende_daten;
				
	//Lokaler Trasnaction Hash mit Peer Prevoius Hash vergleichen
				//cout<<"local_transaction_data##"<<local_transaction_data<<endl;
				zu_hashende_daten = "";
				zu_hashende_daten = local_transaction_data;
				void hasher();
				hasher();
				string local_transaction_data_gehasht;
				local_transaction_data_gehasht = zu_hashende_daten;
				//cout<<"local_transaction_data_gehasht##"<<local_transaction_data_gehasht<<endl;
				//cout<<"peer_previous_hash##"<<peer_previous_hash<<endl;
				
				zu_hashende_daten = "";
				zu_hashende_daten = local_transaction_data_gehasht + peer_previous_hash;
				void hasher();
				hasher();
				string cross_check_hash_block;
				cross_check_hash_block = zu_hashende_daten;
				
				//cout<<"zu_hashende_daten             ####"<<cross_check_hash_block<<"###"<<endl;
				//cout<<"Aktuelle Block PEER Hash Wert ####"<<peer_hash_block<<"###"<<endl;
				//cout<<"Aktuelle Block LOKAL Hash Wert####"<<lokaler_hash_block<<"###"<<endl;		
	
	//Peer Hash mit Lokaler Prevoius Hash vergleichen
				//compare_hashes_previous_blocks = false;
				if ((cross_check_hash_block == peer_hash_block) && (cross_check_hash_block ==lokaler_hash_block))
				{
					//cout<<"CROSS CHECK OK"<<endl;
					//cout<<"cross_check_hash_block        ####"<<cross_check_hash_block<<"###"<<endl;
					//cout<<"Aktuelle Block PEER Hash Wert ####"<<peer_hash_block<<"###"<<endl;
					//cout<<"Aktuelle Block LOKAL Hash Wert####"<<lokaler_hash_block<<"###"<<endl;		
					compare_hashes_previous_blocks = true;
				}
				else
				{
					//cout<<"CROSS CHECK FALSE"<<endl;
					//cout<<"cross_check_hash_block        ####"<<cross_check_hash_block<<"###"<<endl;
					//cout<<"Aktuelle Block PEER Hash Wert ####"<<peer_hash_block<<"###"<<endl;
					//cout<<"Aktuelle Block LOKAL Hash Wert####"<<lokaler_hash_block<<"###"<<endl;		
					compare_hashes_previous_blocks = false;
				}
				//compare_hashes_previous_blocks = false
			}
		}
		//##########################################################################################################
		
//##############################################################################################################				
//Alle Blöcke Hashtechninsch bis "bc-id 0" herunterechnen
//cout<<"ENDE"<<endl;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	