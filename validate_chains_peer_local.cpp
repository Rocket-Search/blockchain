//clear; rm -frv  validate_chains_peer_local.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local.cpp

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
extern vector<string> erreichbare_peers;
extern unsigned long long anzahl_ketten_db_records_int ;
string erreichbare_peers_fuer_read_peer_single_block;
unsigned long long block_nummer_fuer_read_peer_single_block ;
string local_block;
string peer_block;
string block_nummer;
bool compare_blocks_peer_local_bool;
bool compare_hashes_local;
bool compare_hashes_peer;
bool compare_hashes_cross_peer_local;
bool compare_hashes_previous_blocks;
bool start_compare_20_blocks_hashes;
extern vector<string> config_file_parameter;

void validate_chains_peer_local()
{
	//cout<<"Validate Chains"<<endl;
	//cout<<"\e[1m"<<"validate_chains_peer_local.cpp"<<"\e[0m"<<endl;
	
	//Lokale DB Einträge und Peer DB einträge einzelnt prüfen inkl. GPG Key. Public GPG Key zuvor implementieren
	//Public Key exportieren:	"gpg --armor --export 4392152BCB3979AF46BC9D35E88274AC474B7F03 > bc-peer-1@bit-devil.ddns.net_public_key.asc"
	//Public Key importieren:	"gpg --import bc-peer-1@bit-devil.ddns.net_public_key.asc"

	//Lokale DB prüfen
	//###########
	//redis_command_from_main = "LINDEX blockchain_list 2\r\n";
	//string block_nummer;
	//string local_block;
	//string peer_block;
	
	//cout<<"vector<string> erreichbare_peers.size()#"<<erreichbare_peers.size()<<endl;;
	//cout<<"vector<string> erreichbare_peers#"<<erreichbare_peers[0]<<endl;;
	//erreichbare_peers_fuer_read_peer_single_block = erreichbare_peers[0] ;
		
	//cout<<"local_block#"<<local_block<<endl;
	//cout<<"peer_block#"<<peer_block<<endl;

	for(unsigned int i = 0 ; i < erreichbare_peers.size(); i++)
	{
		erreichbare_peers_fuer_read_peer_single_block = erreichbare_peers[i] ;
		//cout<<"erreichbare_peers_fuer_read_peer_single_block#"<<erreichbare_peers_fuer_read_peer_single_block<<endl;
		
		for (unsigned long long j = 0; j < anzahl_ketten_db_records_int; j++)
		{
			//Lokale Datensätze aus redis holen#####
			stringstream strstream;
			strstream << j;
			strstream >> block_nummer;
			redis_command_from_main = "LINDEX blockchain_list " + block_nummer + " \r\n";
			//cout<<"redis_command_from_main#"<<redis_command_from_main<<endl;
			void read_all_chains_from_db();
			read_all_chains_from_db();
			blocks_from_db = blocks_from_db.erase(blocks_from_db.find_last_not_of("\n"));
			//cout<<"blocks_from_db VALIDATE LOCAL#"<<blocks_from_db<<endl;
			local_block = blocks_from_db;
			//cout<<"lokales lesen fertig# "<<block_nummer<<endl;
			//cout<<"Lokaler Block#"<<local_block<<"#"<<endl;
			//#################################################################
			
			//Im gleichen Zyklus die Peer Datenbank ansprechen und den Datenstaz Nummer "XY" rausholen###
			//Block ID (LINDEX) übergeben
			block_nummer_fuer_read_peer_single_block = j;
			//cout<<"block_nummer in VALIDATE#"<<block_nummer_fuer_read_peer_single_block<<endl;
			blocks_from_db = "";		//variable leeren
			void read_peer_single_block();
			read_peer_single_block();
			//blocks_from_db = blocks_from_db.erase(blocks_from_db.find_last_not_of("\n"));
			
			peer_block = blocks_from_db;
			//cout<<"blocks_from_db in VALIDATE PEER#"<<peer_block<<endl;
			//cout<<"Remote Block#"<<peer_block<<"#"<<endl;
			//#################################################################

			//Datensaätze von lokal und peer auf gleich chars überprüfen###
			compare_blocks_peer_local_bool = false;
			void compare_blocks_peer_local();
			compare_blocks_peer_local();
			
			if(compare_blocks_peer_local_bool == false)
			{
				if (peer_block == "")
				{
					//cout<<"KEIN REMOTE BLOCK ERHALTEN in validate_chains_peer_local.cpp"<<endl;
					continue;
				}
				else
				{
					cout<<"ACHTUNG Kette CHARS ist unterschiedlich !!!!!!!!"<<endl;
	//				cout<<"Manuelle Tätigkeit notwendig"<<endl;
					cout<<"LOCAL BLOCK#"<<local_block<<endl;
					cout<<endl;
					cout<<"PEER BLOCK #"<<peer_block<<endl;
					cout<<"block_nummer#"<<block_nummer<<endl;
					cout<<"EXIT"<<endl;exit(-1);
				}
			}
			if(compare_blocks_peer_local_bool == true)
			{
				//cout<<"Kette (Zeichenketten sind gelich)"<<endl;
				//cout<<"LOCAL BLOCK#"<<local_block<<endl;
				//cout<<"PEER BLOCK #"<<peer_block<<endl;
				//cout<<"block_nummer#"<<block_nummer<<endl;
			}
			//#################################################################
			
			//#################################################################
			//bis zum bc-id abschneiden. Das ist die redis Zeichenkettenanzahlnummer
			int wo_ist_crlf = -1;
			//wo_ist_crlf = local_block.find("\r\n");
			//cout<<"LOCAL BLOCK#"<<local_block<<endl;
			wo_ist_crlf = local_block.find("bc-id");
			//cout<<"wo_ist_crlf in validate_chains_peer_local#"<<wo_ist_crlf<<endl;
			if (wo_ist_crlf != -1)
			{
				local_block = local_block.substr(wo_ist_crlf, local_block.length());			//substr mit if 2 zeilen voher abgesichert
				//cout<<"local_block validate_chains_peer_local#"<<local_block<<endl;
			}
			//#
			wo_ist_crlf = -1;
			//wo_ist_crlf = peer_block.find("\r\n");
			wo_ist_crlf = peer_block.find("bc-id");
			//cout<<"wo_ist_crlf in validate_chains_peer_local#"<<wo_ist_crlf<<endl;
			if (wo_ist_crlf != -1)
			{
				peer_block = peer_block.substr(wo_ist_crlf, peer_block.length());		//substr mit if 2 zeilen voher abgesichert
				//cout<<"peer_block validate_chains_peer_local#"<<peer_block<<endl;
			}
			//#################################################################
		
			//unsigned long long zufall_pruef_nummer = 91;
			//unsigned long long zufall_pruef_nummer = 21; 
			//zufall_pruef_nummer = rand() % 100 + 50; 

			//compare hashes###
			void compare_hashes_peer_local();
			compare_hashes_peer_local();
			
			if (compare_hashes_local == false)
			{
				if (peer_block == "")
				{
					//cout<<"KEIN REMOTE BLOCK ERHALTEN"<<endl;
					continue;
				}
				else
				{
					cout<<"ACHTUNG Block Hashwetre LOKAL ist unterschiedlich !!!!!!!!"<<endl;
	//				cout<<"Manuelle Tätigkeit notwendig"<<endl;
					cout<<"PEER BLOCK #"<<peer_block<<endl;
					cout<<"LOCAL BLOCK#"<<local_block<<endl;
					cout<<"block_nummer#"<<block_nummer<<endl;
					cout<<"EXIT"<<endl;exit(-1);
				}
			}
			
			if (compare_hashes_peer == false)
			{
				if (peer_block == "")
				{
					//cout<<"KEIN REMOTE BLOCK ERHALTEN"<<endl;
					continue;
				}
				else
				{
					cout<<"ACHTUNG Block Hashwetre PEER ist unterschiedlich !!!!!!!!"<<endl;
	//				cout<<"Manuelle Tätigkeit notwendig"<<endl;
					cout<<"PEER BLOCK#"<<peer_block<<endl;
					cout<<"LOCAL BLOCK#"<<local_block<<endl;
					cout<<"block_nummer#"<<block_nummer<<endl;
					cout<<"EXIT"<<endl;exit(-1);
				}
			}
			
			if (compare_hashes_cross_peer_local == false)
			{
				if (peer_block == "")
				{
					//cout<<"KEIN REMOTE BLOCK ERHALTEN"<<endl;
					continue;
				}
				else
				{

					cout<<"ACHTUNG Cross Check Lokal <-> Peer ist unterschiedlich !!!!!!!!"<<endl;
	//				cout<<"Manuelle Tätigkeit notwendig"<<endl;
					cout<<"LOCAL BLOCK#"<<local_block<<endl;
					cout<<"PEER BLOCK#"<<peer_block<<endl;
					cout<<"block_nummer#"<<block_nummer<<endl;
					cout<<"EXIT"<<endl;exit(-1);
				}
			}
			
		//start compare_hashes_previous_blocks###################
		//erst starten wenn blöcke über Numer 20 erreicht
		if (start_compare_20_blocks_hashes == true)
		{
			if(compare_hashes_previous_blocks == false)
			{
				cout<<"CROSS CHECK 20 Blöcke Transaktion Data und Prevois Peer und Lokal nicht korret !!!!"<<endl;
				//cout<<"Manuelle Tätigkeit notwendig"<<endl;
				cout<<"LOCAL BLOCK#"<<local_block<<endl;
				cout<<"PEER BLOCK#"<<peer_block<<endl;
				cout<<"block_nummer#"<<block_nummer<<endl;
			}
		}	
//validate GPG Signature####

//Datums Check inkl. Zeit

//Nummerierung prüfen
			
		}
	}
	//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db#"<<blocks_from_db<<endl;
	//blocks_from_db = blocks_from_db.substr(1,blocks_from_db.length());
	//cout<<"blocks_from_db VALIDATE CHAIN#"<<blocks_from_db<<endl;
	//unsigned long long anzahl_lokaler_ketten_long = stoll(blocks_from_db);
	//cout<<"Lokal Ketten Anzahl LLEN blocks_from_db VALIDATE CHAIN long#"<<anzahl_lokaler_ketten_long<<endl;
	//###########
	
	//cout<<"vector<string> erreichbare_peers.size()#"<<erreichbare_peers.size()<<endl;;
	//cout<<"vector<string> erreichbare_peers#"<<erreichbare_peers[0]<<endl;;
	//cout<<"anzahl_ketten_db_records_int vlaidate#"<<anzahl_ketten_db_records_int<<endl;
	
//cout<<"ENDE validate_chains_peer_local.cpp"<<endl;
}