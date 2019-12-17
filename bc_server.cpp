//Einzelnt
//clear; rm -frv read_all_chains_from_db.o; g++-7 -g -fPIC -Wall -c read_all_chains_from_db.cpp
//clear; rm -frv bc_server.o; g++-7 -g -fPIC -Wall -c bc_server.cpp
//clear; rm -frv read_peer_lists.o; g++-7 -g -fPIC -Wall -c read_peer_lists.cpp
//clear; rm -frv read_peer_blocks.o; g++-7 -g -fPIC -Wall -c  read_peer_blocks.cpp
//clear; rm -frv write_to_db.o; g++-7 -g -fPIC -Wall -c write_to_db.cpp
//clear; rm -frv validate_chains_peer_local.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local.cpp
//clear; rm -frv read_peer_single_block.o; g++-7 -g -fPIC -Wall -c read_peer_single_block.cpp
//clear; rm -frv compare_blocks_peer_local.o; g++-7 -g -fPIC -Wall -c compare_blocks_peer_local.cpp
//clear; rm -frv compare_hashes_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_peer_local.cpp
//clear; rm -frv rpoplpush_redis.o; g++-7 -g -fPIC -Wall -c rpoplpush_redis.cpp
//clear; rm -frv hasher.o; g++-7 -g -fPIC -Wall -c hasher.cpp
//clear; rm -frv send_peer_local_chain_longer_and_send_blocks.o; g++-7 -g -fPIC -Wall -c send_peer_local_chain_longer_and_send_blocks.cpp
//clear; rm -frv validate_chains_peer_local_with_remote_ip_only.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local_with_remote_ip_only.cpp
//clear; rm -frv compare_hashes_single_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_single_peer_local.cpp
//clear; rm -frv filter_pure_bc_block.o; g++-7 -g -fPIC -Wall -c  filter_pure_bc_block.cpp
//clear; rm -frv send_block_to_reachable_peers.o; g++-7 -g -fPIC -Wall -c  send_block_to_reachable_peers.cpp
//clear; rm -frv filter_pure_bc_block_for_peer.o; g++-7 -g -fPIC -Wall -c filter_pure_bc_block_for_peer.cpp
//clear; rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c  read_config_file.cpp
//clear; rm -frv check_block_exists.o; g++-7 -g -fPIC -Wall -c check_block_exists.cpp
//clear; rm -frv write_to_db_linsert.o; g++-7 -g -fPIC -Wall -c write_to_db_linsert.cpp
//clear; rm -frv bc_server; g++-7 -g -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -lpthread -o bc_server bc_server.o read_peer_lists.o read_all_chains_from_db.o read_peer_blocks.o write_to_db.o validate_chains_peer_local.o read_peer_single_block.o compare_blocks_peer_local.o compare_hashes_peer_local.o rpoplpush_redis.o hasher.o send_peer_local_chain_longer_and_send_blocks.o validate_chains_peer_local_with_remote_ip_only.o compare_hashes_single_peer_local.o filter_pure_bc_block.o send_block_to_reachable_peers.o filter_pure_bc_block_for_peer.o read_config_file.o check_block_exists.o write_to_db_linsert.o -static-libstdc++ ;
//###
//Einzeiler###########################
//DEV//clear; rm -frv write_to_db_linsert.o; g++-7 -g -fPIC -Wall -c write_to_db_linsert.cpp; rm -frv check_block_exists.o; g++-7 -g -fPIC -Wall -c check_block_exists.cpp ;rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c  read_config_file.cpp;rm -frv filter_pure_bc_block_for_peer.o; g++-7 -g -fPIC -Wall -c filter_pure_bc_block_for_peer.cpp ;rm -frv send_block_to_reachable_peers.o; g++-7 -g -fPIC -Wall -c send_block_to_reachable_peers.cpp ;rm -frv filter_pure_bc_block.o; g++-7 -g -fPIC -Wall -c  filter_pure_bc_block.cpp ;rm -frv compare_hashes_single_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_single_peer_local.cpp;rm -frv  validate_chains_peer_local_with_remote_ip_only.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local_with_remote_ip_only.cpp ;rm -frv send_peer_local_chain_longer_and_send_blocks.o; g++-7 -g -fPIC -Wall -c send_peer_local_chain_longer_and_send_blocks.cpp  ;rm -frv hasher.o; g++-7 -g -fPIC -Wall -c hasher.cpp ;rm -frv rpoplpush_redis.o; g++-7 -g -fPIC -Wall -c rpoplpush_redis.cpp; rm -frv compare_hashes_peer_local.o; g++-7 -g -fPIC -Wall -c compare_hashes_peer_local.cpp ;rm -frv compare_blocks_peer_local.o; g++-7 -g -fPIC -Wall -c compare_blocks_peer_local.cpp; rm -frv read_peer_single_block.o; g++-7 -g -fPIC -Wall -c read_peer_single_block.cpp ;rm -frv validate_chains_peer_local.o; g++-7 -g -fPIC -Wall -c  validate_chains_peer_local.cpp ;rm -frv write_to_db.o; g++-7 -g -fPIC -Wall -c write_to_db.cpp ;rm -frv read_peer_blocks.o; g++-7 -g -fPIC -Wall -c  read_peer_blocks.cpp ; rm -frv read_peer_lists.o; g++-7 -g -fPIC -Wall -c read_peer_lists.cpp; rm -frv read_all_chains_from_db.o; g++-7 -g -fPIC -Wall -c read_all_chains_from_db.cpp; rm -frv bc_server.o; g++-7 -g -fPIC -Wall -c bc_server.cpp; rm -frv bc_server; g++-7 -g -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -lpthread -o bc_server bc_server.o read_all_chains_from_db.o read_peer_lists.o read_peer_blocks.o write_to_db.o validate_chains_peer_local.o read_peer_single_block.o compare_blocks_peer_local.o compare_hashes_peer_local.o rpoplpush_redis.o hasher.o send_peer_local_chain_longer_and_send_blocks.o validate_chains_peer_local_with_remote_ip_only.o compare_hashes_single_peer_local.o filter_pure_bc_block.o send_block_to_reachable_peers.o filter_pure_bc_block_for_peer.o read_config_file.o check_block_exists.o write_to_db_linsert.o -static-libstdc++ ;date
//PRD//clear; rm -frv write_to_db_linsert.o; g++-7 -O3 -fPIC -Wall -c write_to_db_linsert.cpp; rm -frv check_block_exists.o; g++-7 -O3 -fPIC -Wall -c check_block_exists.cpp ;rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c  read_config_file.cpp;rm -frv filter_pure_bc_block_for_peer.o; g++-7 -O3 -fPIC -Wall -c filter_pure_bc_block_for_peer.cpp ;rm -frv send_block_to_reachable_peers.o; g++-7 -O3 -fPIC -Wall -c send_block_to_reachable_peers.cpp ;rm -frv filter_pure_bc_block.o; g++-7 -O3 -fPIC -Wall -c  filter_pure_bc_block.cpp ;rm -frv compare_hashes_single_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_hashes_single_peer_local.cpp;rm -frv  validate_chains_peer_local_with_remote_ip_only.o; g++-7 -O3 -fPIC -Wall -c  validate_chains_peer_local_with_remote_ip_only.cpp ;rm -frv send_peer_local_chain_longer_and_send_blocks.o; g++-7 -O3 -fPIC -Wall -c send_peer_local_chain_longer_and_send_blocks.cpp  ;rm -frv hasher.o; g++-7 -O3 -fPIC -Wall -c hasher.cpp ;rm -frv rpoplpush_redis.o; g++-7 -O3 -fPIC -Wall -c rpoplpush_redis.cpp; rm -frv compare_hashes_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_hashes_peer_local.cpp ;rm -frv compare_blocks_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_blocks_peer_local.cpp; rm -frv read_peer_single_block.o; g++-7 -O3 -fPIC -Wall -c read_peer_single_block.cpp ;rm -frv validate_chains_peer_local.o; g++-7 -O3 -fPIC -Wall -c  validate_chains_peer_local.cpp ;rm -frv write_to_db.o; g++-7 -O3 -fPIC -Wall -c write_to_db.cpp ;rm -frv read_peer_blocks.o; g++-7 -O3 -fPIC -Wall -c  read_peer_blocks.cpp ; rm -frv read_peer_lists.o; g++-7 -O3 -fPIC -Wall -c read_peer_lists.cpp; rm -frv read_all_chains_from_db.o; g++-7 -O3 -fPIC -Wall -c read_all_chains_from_db.cpp; rm -frv bc_server.o; g++-7 -O3 -fPIC -Wall -c bc_server.cpp; rm -frv bc_server; g++-7 -O3 -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -lpthread -o bc_server bc_server.o read_all_chains_from_db.o read_peer_lists.o read_peer_blocks.o write_to_db.o validate_chains_peer_local.o read_peer_single_block.o compare_blocks_peer_local.o compare_hashes_peer_local.o rpoplpush_redis.o hasher.o send_peer_local_chain_longer_and_send_blocks.o validate_chains_peer_local_with_remote_ip_only.o compare_hashes_single_peer_local.o filter_pure_bc_block.o send_block_to_reachable_peers.o filter_pure_bc_block_for_peer.o read_config_file.o check_block_exists.o write_to_db_linsert.o -static-libstdc++ ;date

//Test mit Dummydaten
//timeout 60 cat /dev/random | xxd -ps | awk '{print " # "b++ strftime(" %Y%m%d-%H:%M:%S", systime()) }' | xargs -I % ./blockchain "%"
//clear; time seq 1000 | xargs -n 1 ./blockchain ASDF 

//(echo -ne "get chain size\r\n" ; cat ) | openssl s_client -connect 172.17.190.84:8888 = API TLS Test Client
//Performancetest: "while true ; do timeout 0.1 ./tls_check.sh; done;"

//C_C++ Header
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string>
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
//File Time Modification####
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstdlib>
//Error Handling und Singal
//perror
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <csignal>
#include <iterator>
//Network
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
//Posix Threads
#include <fcntl.h> // for open
#include<pthread.h>
#include <thread>
//TLS
#include <tls.h>
//Assertation
#include <assert.h>
//Local Address inf
#include <sys/ioctl.h>
#include <net/if.h>
#include <ifaddrs.h>
//#####################
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <resolv.h>
//#include <regex>

using namespace std;

//Public Variablen für Object Files
string blocks_from_db;
string redis_command_from_main;
vector<string> peer_lists;
vector<string> peer_lists_temp;
string remote_ip;
string pure_bc_block;
vector<string> config_file_parameter;
bool exit_validate_chains_peer_local_with_remote_ip_only_cpp = false;
bool datensatz_existiert = false;
string lokal_ip_adresse;
bool block_fuer_set_block_to_peer = false;
bool local_chain_longer_than_remote = false;

unsigned long long local_kette_laenge;
int remote_kettten_laenge;

//extern Variablen
extern string write_block_to_db;
extern vector<string> erreichbare_peers;

struct tls *tls2 = NULL;
struct tls_config *config = NULL;
struct tls *tls = NULL;

string config_file_pfad;

void signalHandler( int signum)
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	cout<<"PROBLEM Blockchain daemon"<<endl;
	
//close(socket_desc);
	
	exit (666);
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
	//char *message , client_message[2000];
//char client_message[2000];
//wchar_t client_message[2000];
char client_message[999999];

	//Send some messages to the client
    //message = "Block Chain Server Helo\n";
//write(sock , message , strlen(message));
//send(sock, message, strlen(message), 0);
	
	//message = "Start Communication\n";
//write(sock , message , strlen(message));
//send(sock, message, strlen(message), 0);

//TLS einmal manuell
//int bytes;
//bytes = tls_read(tls2, client_message, 1000);
//cout<<"bytes#"<<bytes<<endl;
//cout<<"client_message#"<<client_message<<endl;

	//Receive a message from client
//Aus Konfig lesen ob TLS gewünscht wird oder nicht
    //while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
//          bytes = tls_read(tls2, bufs, 1000);
//read_size = tls_read(tls2, client_message, 1000);
//Was ist wenn die Nachricht mehr als 20000 Chars enthält
//while( (read_size = tls_read(tls2, client_message, 2000)) > 0 )
while( (read_size = tls_read(tls2, client_message, 999999)) > 0 )
    {
        //end of string marker
		//client_message[read_size] = '\0';
		//cout<<"client_message RAW##"<<client_message<<"##"<<endl;
		
		//#################################################################
		//Bit-Devil Block Chain Protokoll
		string bc_protokoll_client_messages = client_message;
		//cout<<"bc_protokoll_client_messages 1#"<<bc_protokoll_client_messages<<"#"<<endl;
		//void bc_protokoll();
		//bc_protokoll();

		bc_protokoll_client_messages = bc_protokoll_client_messages.erase(bc_protokoll_client_messages.find_last_not_of("\n"));
		//bc_protokoll_client_messages = bc_protokoll_client_messages.erase(bc_protokoll_client_messages.find_last_of("\n"));
		//bc_protokoll_client_messages.pop_back();
		//bc_protokoll_client_messages = bc_protokoll_client_messages.erase(bc_protokoll_client_messages.find_first_of("\n"));
		//bc_protokoll_client_messages = bc_protokoll_client_messages.replace(bc_protokoll_client_messages.begin(),bc_protokoll_client_messages.end(),"\n"); 
		//cout<<"bc_protokoll_client_messages 2#"<<bc_protokoll_client_messages<<"#"<<endl;

//#######################################################################################################################################################################
//#######################################################################################################################################################################
//PROTOKOLL##############################################################################################################################################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		
		//################################################################
		//GET CHAIN#############################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		if (bc_protokoll_client_messages == "get chain")
		{
			//cout<<"\e[1m"<<"bc_server # get chain"<<"\e[0m"<<endl;
			//cout<<"Sende komplette Chain an Client"<<endl;
			//bc_protokoll_client_messages = bc_protokoll_client_messages.erase(bc_protokoll_client_messages.find_last_not_of("\n"));
			bc_protokoll_client_messages = "Sende CHAIN";
			//Ketten größe ermitteln "LLEN" ############
			redis_command_from_main = "LLEN blockchain_list\r\n";
			void read_all_chains_from_db();
			read_all_chains_from_db();
			//cout<<"blocks_from_db LLEN #"<<blocks_from_db<<endl;
			//#########################
			
			//Blöcke laden und an client senden#####
			//64 (this is a non-standard GNU extension) Range:	-9223372036854775808 to 9223372036854775807(signed) or 0-18446744073709551616(unsigned)
			unsigned long long block_chain_groesse,block_chain_groesse_temp;
			unsigned long long counter;

			blocks_from_db = blocks_from_db.erase(blocks_from_db.find_last_not_of("\n"));
			
			//blocks_from_db = blocks_from_db.substr(1,999999);
			try{blocks_from_db = blocks_from_db.substr(1,999999);}catch( std::out_of_range& exception ){cout<<"Error bc_server.cpp blocks_from_db std::out_of_range"<<endl;}

			//cout<<"blocks_from_db#"<<blocks_from_db<<"#"<<endl;
			block_chain_groesse = stoll(blocks_from_db);
			block_chain_groesse_temp = block_chain_groesse;
			//cout<<"block_chain_groesse_temp#"<<block_chain_groesse_temp<<endl;

			for ( counter = 0; counter <  block_chain_groesse; counter++)
			//for ( counter = 0; counter <  3; counter++)
			{
				//cout<<"counter#"<<counter<<endl;
				//redis_command_from_main = "LINDEX blockchain_list 0\r\n";
				block_chain_groesse_temp = block_chain_groesse_temp - 1;
				//cout<<"block_chain_groesse#"<<block_chain_groesse<<endl;
					//block_chain_groesse in string wandeln
					string block_chain_groesse_string;
					stringstream strstream;
					strstream << block_chain_groesse_temp;
					strstream >> block_chain_groesse_string;
				redis_command_from_main = "LINDEX blockchain_list " + block_chain_groesse_string + "\r\n";

				//cout<<"redis_command_from_main#"<<redis_command_from_main<<endl;
				void read_all_chains_from_db();
				read_all_chains_from_db();
				//cout<<"blocks_from_db in bc_server####"<<blocks_from_db<<endl;
				//cout<<"blocks_from_db in bc_server LÄNGE####"<<blocks_from_db.length()<<endl;
				//#########################
				
				//Sende die Bloecke an den Client
				//cout<<"Sende Block an Clinet:"<<endl;
				//blocks_from_db = blocks_from_db + "ENDE#DATENSATZ";
				//Sonderzeichen nach dem "-----END PGP SIGNATURE-----" entfernet
				//send(sock, blocks_from_db.c_str(), blocks_from_db.length(), 0);
				tls_write(tls2, blocks_from_db.c_str(), blocks_from_db.length() );
				blocks_from_db = "";
			}
			//cout<<"schließe Client get chain socket"<<endl;
			//cout<<"Schließe socket"<<endl;
			//close(sock);
			//cout<<"ENDE bc_server # get chain"<<endl;
		}
		//################################################################
		//GET PEER LIST#############################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		if (bc_protokoll_client_messages == "get peer list")
		{
			//cout<<"\e[1m"<<"bc_server # get peer list"<<"\e[0m"<<endl;
			//Sende die Bloecke an den Client
			//cout<<"peer_lists aus PROTOKOLL#"<<peer_lists[0]<<endl;
			int anzahl_peers_aus_datei = 0;
			anzahl_peers_aus_datei = peer_lists.size();
			//cout<<"anzahl_peers_aus_datei#"<<anzahl_peers_aus_datei<<endl;
			string peers_aus_array;
			
			if (anzahl_peers_aus_datei == 0)
			{
				string keine_peers_vorhanden = "##NO PEERS##";
				int tls_write_status = 666;
				tls_write_status = tls_write(tls2, keine_peers_vorhanden.c_str(), keine_peers_vorhanden.length() );
				//cout<<"tls_write_status NO PEERS bc_server get peer list.cpp#"<<tls_write_status<<endl;
			}
		
			
			for (int i = 0; i < anzahl_peers_aus_datei; i++)
			{			
				peers_aus_array = peer_lists[i] + "@";
				//peers_aus_array = peer_lists[i] + "#";
				//peers_aus_array = peer_lists[i] + "ENDEPEERLIST";
				//peers_aus_array = peer_lists[i] + "\nENDEPEERLIST";
				//peers_aus_array = peer_lists[i] + "\0";
				//peers_aus_array = peer_lists[i] + "\r\n";
				//cout<<"SENDE peer_lists aus PROTOKOLL#"<<peers_aus_array<<endl;
				//send(sock, peers_aus_array.c_str(), peers_aus_array.length(), 0);
				int tls_write_status = 666;
				tls_write_status = tls_write(tls2, peers_aus_array.c_str(), peers_aus_array.length() );
				//cout<<"tls_write_status bc_server get peer list.cpp#"<<tls_write_status<<endl;

			}
			//cout<<"schließe Client get peer list"<<endl;
			//close(sock);
			//cout<<"ENDE bc_server # get peer list"<<endl;
		}
		//################################################################
		//GET CHAIN SIZE#############################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		if (bc_protokoll_client_messages == "get chain size")
		{
			//cout<<"\e[1m"<<"bc_server # get chain size"<<"\e[0m"<<endl;
			//string redis_llen;
			
			//redis_llen = "Sende Chain Size";
			//send(sock, redis_llen.c_str(), redis_llen.length(), 0);
			
			redis_command_from_main = "LLEN blockchain_list\r\n";
			//cout<<"redis_command_from_main#"<<redis_command_from_main<<"#"<<endl;
			
			void read_all_chains_from_db();
			read_all_chains_from_db();
			
			//cout<<"Blockanzahl von redis"<<endl;	
			//cout<<"Sende Ketten Länge an client blocks_from_db#"<<blocks_from_db<<"#"<<endl;
			//send(sock, blocks_from_db.c_str(), blocks_from_db.length(), 0);
			tls_write(tls2, blocks_from_db.c_str(), blocks_from_db.length() );

			//cout<<"schließe Client get chain size"<<endl;
			//close(sock);
			//cout<<"ENDE bc_server # get chain size"<<endl;
		}
		//################################################################
		//GET SINGLE BLOCK#############################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		unsigned int wo_ist_get_single_block_bc_protokoll_client_messages = -1;
		//Im Auge behalten ob nicht besser lösbar !!!
		if (wo_ist_get_single_block_bc_protokoll_client_messages > bc_protokoll_client_messages.find("get single block"))
		{
			//cout<<"Sende Single Block"<<endl;
			//cout<<"\e[1m"<<"bc_server # get single block"<<"\e[0m"<<endl;
			//cout<<"wo_ist_get_single_block_bc_protokoll_client_messages#"<<wo_ist_get_single_block_bc_protokoll_client_messages<<endl;
			//cout<<"client_message#"<<bc_protokoll_client_messages<<"#"<<endl;
			
			string block_nummer;
			//block_nummer = bc_protokoll_client_messages.substr(17,bc_protokoll_client_messages.length());
			try{block_nummer = bc_protokoll_client_messages.substr(17,bc_protokoll_client_messages.length());}catch( std::out_of_range& exception ){cout<<"Error bc_server.cpp bc_protokoll_client_messages std::out_of_range"<<endl;}

			//cout<<"block_nummer#"<<block_nummer<<endl;
			
			string redis_lindex;
					
			redis_command_from_main = "LINDEX blockchain_list "+ block_nummer +"\r\n";
			//cout<<"redis_command_from_main#"<<redis_command_from_main<<"#"<<endl;
			
			void read_all_chains_from_db();
			read_all_chains_from_db();
			
			//cout<<"Blockanzahl von redis"<<endl;	
			//cout<<"Block Nummer in bc_server.cpp bevor an Client gesendet"<<block_nummer<<"#"<<blocks_from_db<<"#"<<endl;
			//send(sock, blocks_from_db.c_str(), blocks_from_db.length(), 0);
			//tls_write(tls2, blocks_from_db.c_str(), blocks_from_db.length() );
			int tls_write_status = 666;
			tls_write_status = tls_write(tls2, blocks_from_db.c_str(), blocks_from_db.length() );
			//cout<<"tls_write_status#"<<tls_write_status<<endl;
			//sleep(1000);
			if (tls_write_status == -1){cout<<"TLS Schreib Problem in bc_server.cpp # get single block # z358#"<<tls_error(tls2)<<"#"<<endl; exit(-1);}
	
			//cout<<"schließe Client get single block"<<endl;
			//close(sock);
			//cout<<"ENDE bc_server # get single block"<<endl;
		}
		//################################################################
		//local chain longer send get chain command#############################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		if (bc_protokoll_client_messages == "local chain longer send get chain command")
		{	
	
//BSP. Kette auf 172.17.190.84 ist länger als auch 172.17.190.78

			//An Peer Senden das unsere ketten KLEINER sind 
			
	
cout<<"\e[1m"<<"bc_server # local chain longer send get chain command"<<"\e[0m"<<endl;
cout<<"Lokale Kette kleiner, hole fehlende Blöcke von Peer"<<endl;
cout<<"vorher beide ketten validieren"<<endl;
//cout<<"PROTOKOLL#"<<bc_protokoll_client_messages<<"#"<<endl;	
//cout<<"remote_ip# "<<remote_ip<<endl;
			//cout<<"blocks_from_db#"<<blocks_from_db<<"#"<<endl;
			//send(sock, blocks_from_db.c_str(), blocks_from_db.length(), 0);
			//cout<<"schließe Client get chain size"<<endl;
			//cout<<"empfange chains von peer bzw. zugreifer#"<<endl;
			//Vom Zugreifer die Kette empfangen
			
//Validierung beider ketten bis zur stelle an der die remote kette länger ist als die lokale
			//cout<<"Remote IP##"<<remote_ip<<"##"<<endl;
			//cout<<"Validiere Ketten von Remote bis Kette Remote länger"<<endl;
			//ggf. validate change anpassen für remote_ip;
void validate_chains_peer_local_with_remote_ip_only();
validate_chains_peer_local_with_remote_ip_only();
			//cout<<"\e[1m"<<"bc_server # local chain longer send get chain command"<<"\e[0m"<<endl;
//Nach validerung die Fehlenden ketten von remote laden
//Sende get singe block an remote mit nummer


	
//close(sock);
cout<<"ENDE bc_server # local chain longer send get chain command"<<endl;
		}
		//################################################################
		//set block to bc_server### ################################################################
		//set block. Block in lokalen redis/DB schreiben und den Block auf mind. 5 weitere Nodes verteilen
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		//if (bc_protokoll_client_messages == "set block")
		int wo_ist_set_block_bc_protokoll_client_messages = -1;
		if (wo_ist_set_block_bc_protokoll_client_messages > bc_protokoll_client_messages.find("set block to bc_server###"))
		{
			//cout<<"set block to bc_server###"<<endl;
			//cout<<"\e[1m"<<"bc_server # set block to bc_server###"<<"\e[0m"<<endl;
			//cout<<"bc_protokoll_client_messages@"<<bc_protokoll_client_messages<<"@"<<endl;
			
			//reine Block aus Protokoll Kommunikation Filtern################################
			pure_bc_block = bc_protokoll_client_messages;
			//cout<<"pure_bc_block in bc_server.cpp"<<pure_bc_block<<endl;
			//cout<<"Empfangener Block von Client bc_server.cpp"<<pure_bc_block<<endl;
			//Filter pure BC Block
			void filter_pure_bc_block();
			filter_pure_bc_block();
			//cout<<"bc_server.cpp z393 pure_bc_block#"<<pure_bc_block<<endl;
			//cout<<"Gefilterter Block von Client#"<<pure_bc_block<<endl;
			//cout<<"\e[1m"<<"bc_server # set block to bc_server###"<<"\e[0m"<<endl;
	
			//##########################################################################	
			//Prüfen ob der empfangene Block nicht schon vorhanden ist ??
			void check_block_exists();
			check_block_exists();
			//if block existe write block to db überspringen
			if (datensatz_existiert == false)
			{
						//cout<<"Block Existiert NICHT bc_server.cpp  # set block to bc_server # z. 413"<<endl;
						//Block in lokale redis/DB schreiben##################################
						//cout<<"write_block_to_db in bc_server set block to server"<<write_block_to_db<<endl;
						write_block_to_db = pure_bc_block;
						void write_to_db();
						write_to_db();
						
			}
			datensatz_existiert = false;
			//Block in lokale redis/DB schreiben##################################
			//write_block_to_db = pure_bc_block;
			//void write_to_db();
			//write_to_db();
			//##########################################################################

			//cout<<"\e[1m"<<"bc_server # set block to bc_server###"<<"\e[0m"<<endl;
			
			//Den Block verteilen auf alle ereichbare peers################################
			//wenn anzahl_erreichbarer_peers gleich null, an blockchain zurücksenden der Block nicht geschrieben wird weil zu wenig Peers vorhanden sind.
			//cout<<"peer_lists_temp#"<<peer_lists_temp.size()<<endl;
			//cout<<"erreichbare_peers#"<<erreichbare_peers.size()<<endl;
			//cout<<"erreichbare_peers#"<<erreichbare_peers[0]<<endl;
			string blockchain_daemon_return_message;
			int anzahl_erreichbarer_peers = -1;
			anzahl_erreichbarer_peers = erreichbare_peers.size();

			//Wenn Peer Zahl kleiner 5, Error Zurücksenden##
			
			//cout<<"Schließe socket und TLS"<<endl;
			//close(sock);
			//tls_close(tls);
			//tls_free(tls);
			//tls_config_free(config);

			if (anzahl_erreichbarer_peers != -1)
			{
//if IP gleich eigene continue

				void send_block_to_reachable_peers();
				send_block_to_reachable_peers();
				//cout<<"\e[1m"<<"bc_server # set block to bc_server###"<<"\e[0m"<<endl;
				blockchain_daemon_return_message = "BLOCK ERFOLGREICH IM PEER NETZ VERTEILT GESCHRIEBEN";
				//cout<<blockchain_daemon_return_message<<endl;
				//send(sock, blockchain_daemon_return_message.c_str(), blockchain_daemon_return_message.length(), 0);
				tls_write(tls2, blockchain_daemon_return_message.c_str(), blockchain_daemon_return_message.length() );
				//cout<<"pure_bc_block#"<<pure_bc_block<<endl;
				//cout<<"Schließe socket und TLS"<<endl;
				//close(sock);
				//tls_close(tls);
				//tls_free(tls);
				//tls_config_free(config);
			}
			else
			{
				//cout<<"BLOCK KANN NICHT GESETZT WERDEN DA ZU WENIG PEERS VORHANDEN !!"<<endl;
				blockchain_daemon_return_message = "BLOCK KANN NICHT GESETZT WERDEN DA ZU WENIG PEERS VORHANDEN !!";
				cout<<blockchain_daemon_return_message<<endl;
				//send(sock, blockchain_daemon_return_message.c_str(), blockchain_daemon_return_message.length(), 0);
				tls_write(tls2, blockchain_daemon_return_message.c_str(), blockchain_daemon_return_message.length() );
			}
			
			//cout<<"ENDE bc_server # set block to bc_server"<<endl;
		}
		//################################################################
		//set block to peer ### ################################################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		int wo_ist_set_block__to_peer_bc_protokoll_client_messages = -1;
		if (wo_ist_set_block__to_peer_bc_protokoll_client_messages > bc_protokoll_client_messages.find("set block to peer ###"))
		{
			//cout<<"SET BLOCK TO PEER"<<endl;
			//cout<<"bc_protokoll_client_messages"<<bc_protokoll_client_messages<<endl;
			//cout<<"\e[1m"<<"bc_server # set block to peer ###"<<"\e[0m"<<endl;
			
			//Filter pure BC Block
			pure_bc_block = bc_protokoll_client_messages;
			void filter_pure_bc_block_for_peer();
			filter_pure_bc_block_for_peer();
			//cout<<"pure_bc_block in bc_server set block to peer z. 489#"<<pure_bc_block<<"#"<<endl;
			//cout<<"\e[1m"<<"bc_server # set block to peer ###"<<"\e[0m"<<endl;

			block_fuer_set_block_to_peer = true;

			//Prüfen ob der empfangene Block nicht schon vorhanden ist ??
			void check_block_exists();
			check_block_exists();
			//if block existe write block to db überspringen
			if (datensatz_existiert == false)
			{
						//Block in lokale redis/DB schreiben##################################
						//cout<<"Block Existiert NICHT bc_server.cpp  # set block to peer # z. 499"<<endl;
						write_block_to_db = pure_bc_block;
						void write_to_db();
						write_to_db();
						
			}
			datensatz_existiert = false;

			//cout<<"\e[1m"<<"bc_server # set block to peer ###"<<"\e[0m"<<endl;
			
			//cout<<"Setzte Block auf Peer"<<pure_bc_block<<endl;
			//cout<<"ENDE bc_server # set block to peer"<<endl;
			block_fuer_set_block_to_peer = false;
			
			//cout<<"Schließe socket und TLS"<<endl;			
			//close(sock);
			//tls_close(tls);
			//tls_free(tls);
			//tls_config_free(config);

			
		}
		//################################################################
		//exit_validate_chains_peer_local_with_remote_ip_only_cpp################################################################
		//cout<<"bc_protokoll_client_messages##"<<bc_protokoll_client_messages<<"##"<<endl;
		int wo_exit_validate_chains_peer_local_with_remote_ip_only_cpp = -1;
		if (wo_exit_validate_chains_peer_local_with_remote_ip_only_cpp > bc_protokoll_client_messages.find("exit_validate_chains_peer_local_with_remote_ip_only_cpp"))
		{
			//cout<<"bc_protokoll_client_messages"<<bc_protokoll_client_messages<<endl;
			//cout<<"\e[1m"<<"BC Protokoll exit_validate_chains_peer_local_with_remote_ip_only_cpp"<<"\e[0m"<<endl;
			exit_validate_chains_peer_local_with_remote_ip_only_cpp = true;
		}
//########################################################################################################################################################		
//########################################################################################################################################################		
//########################################################################################################################################################		

		//Send the message back to client
        //write(sock , client_message , strlen(client_message));
		//send(sock, client_message, strlen(client_message), 0);
		
		//clear the message buffer
		memset(client_message, 0, 2000);
//memset(client_message, 0, 999999);
		
	}

	if(read_size == 0)
    {
        //puts("Client disconnected");
		//cout<<"Client disconnected"<<endl;
		//close(sock);
		//tls_close(tls);
		//tls_free(tls);
		//tls_config_free(config);
		
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        //perror("recv failed");
		//cout<<"recv failed"<<endl;
		fflush(stdout);
		//close(sock);
		//tls_close(tls);
		//tls_free(tls);
		//tls_config_free(config);

	}
	
	close(sock);
	tls_close(tls);
	//tls_free(tls);
	tls_config_free(config);
	//#
	tls_close(tls2);
	//tls_free(tls2);
		//return("nix");
	bzero (client_message, sizeof(client_message));
		
	//cout<<"ENDE PROTOKOLL !!!"<<endl;
	
	return(0);
}
int main(int argc, char *argv[]) 
{
	
	//cout<<"Block Chain Server"<<endl;
	
	//Wenn ARGV Initial angegebn wird. Den ersten Block Chain Wert schreiben und warnen das ggf. alle vorherigen Daten gelöscht werden.


//####################################################################
	//Error Signals
//ZUR FEHLERSUCH CORE DUMPS SCHREIBEN UND NICHT ABFANGEN. IN PRD WIEDER AKTIVIEREN.
/*
	signal(SIGSEGV, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGINT, signalHandler);
	//sleep(300);
*/
//####################################################################
//Resource limit vergroessern (ulimit). Wird an Child Prozesse vererbt. Siehe sap_bcc.cpp

//Linux Thread Werte. Per ofstream in /Proc Datei schreiben
//echo 100000000 > /proc/sys/kernel/threads-max
//echo 100000000 > /proc/sys/vm/max_map_count
//echo 1000000 > /proc/sys/kernel/pid_max

//####################################################################

	//Config aus Datei lesen
	cout<<"lese Config ein"<<endl;
	config_file_pfad = "/etc/blockchain/bc_server.cfg";
	void read_config_file();
	read_config_file();
	//cout<<"config_file_parameter#"<<config_file_parameter[0]<<endl;

//###################################################################	

//####################################################################
	//Environement Einstellen
	string XTERM_LOCALE = "XTERM_LOCALE=en_US.UTF-8";
	char *XTERM_LOCALE_char;
	XTERM_LOCALE_char = (char *) XTERM_LOCALE.c_str();
	//putenv("XTERM_LOCALE=en_US.UTF-8");
	putenv(XTERM_LOCALE_char);
	//#
	string CTYPE = "XTERM_LOCALE=en_US.UTF-8";
	char *CTYPE_char;
	CTYPE_char = (char *) CTYPE.c_str();
	//putenv("XTERM_LOCALE=en_US.UTF-8");
	putenv(CTYPE_char);
	//putenv("LC_CTYPE=en_US.UTF-8");
//####################################################################

//Lokale IP in IF ermittel um die lokalen zugriffe zu unterbinden####################################################################
	struct ifaddrs * ifAddrStruct=NULL;
	struct ifaddrs * ifa=NULL;
	void * tmpAddrPtr=NULL;      
	string ip;

	getifaddrs(&ifAddrStruct);

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
			// is a valid IP4 Address
			tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			//printf("'%s': %s\n", ifa->ifa_name, addressBuffer); 
			ip = ifa->ifa_name;
			//cout<<"IF#"<<ip<<"#"<<endl;
			//cout<<"IP#"<<addressBuffer<<"#"<<endl;
			lokal_ip_adresse = addressBuffer;
			if (lokal_ip_adresse == "127.0.0.1")
			{
				continue;
			}
			//cout<<"IF#"<<ip<<"#"<<endl;
			//cout<<"IP#"<<addressBuffer<<"#"<<endl;
		} 
	}
	if (ifAddrStruct!=NULL)
	{
		//cout<<"freeifaddrs"<<endl;
		freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct
	}
//####################################################################

//Bein starten prüfen ob Ketten vorhanden sind
	cout<<"Prüfe auf vorhandene Ketten"<<endl;
	cout<<"\t"<<"1. Prüfe Peers"<<endl;
	redis_command_from_main = "LLEN blockchain_list\r\n";
	//cout<<"redis_command_from_main#"<<redis_command_from_main<<endl;
	void read_all_chains_from_db();
	read_all_chains_from_db();
	//cout<<"blocks_from_db#"<<blocks_from_db<<endl;

//####################################################################################
//Peerliste abfragen und erhalten

	cout<<"Auf Peers weitere bc_server erfragen"<<endl;

	void read_peer_lists();
	read_peer_lists();
	//cout<<"\e[1m"<<"bc_server"<<"\e[0m"<<endl;
	
	//cout<<"peer_lists#"<<peer_lists[0]<<endl;
	int anzahl_peers_aus_datei = 0;
	anzahl_peers_aus_datei = peer_lists.size();
	//cout<<"anzahl_peers_aus_datei#"<<anzahl_peers_aus_datei<<endl;
	string peers_aus_array;
	
	int wo_ist_newline;
	//bool ende = true;
	int i = 0;
	string str;	
	
	//int start_c = 0 ;
	string peers_aus_array_temp;
	//vector<string> peer_lists_temp;
	
	for (int i = 0; i < anzahl_peers_aus_datei; i++)
	{			
		//peers_aus_array = peer_lists[i] + "\n";
		//cout<<"Peer LISTE#"<<peers_aus_array<<"#"<<endl;
		//cout<<"Anzahl Peers#"<<i<<"#"<<endl;
		
		//Über Netz erhaltene Daten IP technisch filter###
		peers_aus_array = peer_lists[i];
		//cout<<"peer aus datei in_bc_server.cpp#"<<peers_aus_array<<"#"<<endl;
		peer_lists_temp.push_back(peers_aus_array);
		//wo_ist_newline = peers_aus_array.find("ENDEPEERLIST");
		//cout<<"#wo_ist_newline in WHILE#"<<wo_ist_newline<<endl;
		//peers_aus_array = peers_aus_array.substr(wo_ist_newline,peers_aus_array.length());
		//peers_aus_array = peers_aus_array.substr(0,wo_ist_newline);
		//cout<<"peers_aus_array#"<<peers_aus_array<<"#"<<endl;
		wo_ist_newline = peers_aus_array.find("@");
		//cout<<"#wo_ist_newline#"<<wo_ist_newline<<endl;
			
		string str_temp;
		string str_temp_2;
		
		if (wo_ist_newline > -1)
		{
			string str = peers_aus_array;
			peer_lists_temp.pop_back();
			
			for(std::string::size_type j = 0; j < str.size(); ++j) 
			{
				//do_things_with(str[i]);
				//cout<<"str[j]#"<<str[j]<<endl;
				//cout<<"CHAR#"<<str[j]<<endl;
				//cout<<"CHAR_2#"<<str<<endl;
				str_temp = str[j];
				//cout<<"CHAR_3#"<<str_temp<<endl;
				//cout<<"CHAR_3#"<<str_temp;
				//cout<<str_temp;
				str_temp_2 = str_temp_2.append(str_temp);
				if (str_temp == "@")
				{
					//str_temp_2 = str_temp_2.substr(0, str_temp_2.length() - 1);
					try{str_temp_2 = str_temp_2.substr(0, str_temp_2.length() - 1);}catch( std::out_of_range& exception ){cout<<"Error bc_server.cpp str_temp_2 std::out_of_range"<<endl;}

					//str_temp_2 = str_temp_2 + "\n";
					//cout<<"str_temp_2#"<<str_temp_2<<endl;
					//peer_lists.push_back(str_temp_2);
					peer_lists_temp.push_back(str_temp_2);
					str_temp_2 = "";
					//cout<<"TRENNZEICHEN #"<<endl;
					//cout<<"CHAR#"<<str_temp<<endl;
					//cout<<endl<<endl;
				}
			}
		}
	}
	
	//anzahl_peers_aus_datei = peer_lists_temp.size();
	//cout<<"anzahl_peers_aus_datei#"<<anzahl_peers_aus_datei<<endl;
	//Peer dopplete Einträge aus Array entfernen###########
	sort( peer_lists_temp.begin(), peer_lists_temp.end() );
	peer_lists_temp.erase( unique( peer_lists_temp.begin(), peer_lists_temp.end() ), peer_lists_temp.end() );
	anzahl_peers_aus_datei = peer_lists_temp.size();
	//#############################################
	for (i = 0; i < anzahl_peers_aus_datei; i++)
	{	
		//cout<<"i#"<<i<<endl;
		//cout<<"peer_lists_temp in bc_server.cpp#"<<peer_lists_temp[i]<<endl;
	}
	
	//##########################################
	//Block Infos von Peers erhalten
	cout<<"\t"<<"2. Prüfe auf Blöcke bei entfernten Peers"<<endl;
	void read_peer_blocks();
	read_peer_blocks();
		
	//Wenn keine Blöcke vorhanden, Perrs aus Peerliste fragen und in redis schrieben
	//Wenn Blöcke vorhanden, mit Peers aus Peerliste abgleichen.
	

//####################################################################
//###################################################################
//Alle lokalen Ketten vom Ende zum Initial Block runterechnen bzw. validieren.
//danach diese funktiuon in pthread startenund alle 5 minuten laufen lassen.
//####################################################################
//####################################################################



cout<<"Prüfung beendet, starte BC_SERVER"<<endl;	
//####################################################################
	//https://gist.github.com/oleksiiBobko/43d33b3c25c03bcc9b2b
	
	int socket_desc , client_sock , c;
	struct sockaddr_in server , client;

	//TLS Initialiserung######################################################
	//struct tls *tls2 = NULL;
	//#
	int tls_init_status = 666;
	tls_init_status = tls_init();
	//cout<<"tls_init_status#"<<tls_init_status<<endl;
	//#
	//Global definiert
	//struct tls_config *config = NULL;
	config = tls_config_new();
	//cout<<"config#"<<config<<endl;
	//#
	//Global definiert
	//struct tls *tls = NULL;
	tls = tls_server();
	//cout<<"tls_server()#"<<tls<<endl;
	//#
	int tls_config_parse_protocols_status = 666;
	unsigned int protocols = 0;
	//cout<<"protocols#"<<protocols<<endl;
	tls_config_parse_protocols_status = tls_config_parse_protocols(&protocols, "secure") ;
	//cout<<"tls_config_parse_protocols_status#"<<tls_config_parse_protocols_status<<endl;
	//#
	int tls_config_set_protocols_status = 666;
	tls_config_set_protocols_status = tls_config_set_protocols(config, TLS_PROTOCOL_TLSv1_2);
	//cout<<"tls_config_set_protocols_status#"<<tls_config_set_protocols_status<<endl;
	//#
	string cipher_suite = "ECDHE-RSA-AES256-GCM-SHA384";
	char *ciphers = (char *) cipher_suite.c_str();		//Aktuell höchster Versclüsselungsgrad (01/2019  v3.6)
	int tls_config_set_ciphers_status = 666;
	tls_config_set_ciphers_status = tls_config_set_ciphers(config, ciphers);
	//cout<<"#tls_config_set_ciphers_status#"<<tls_config_set_ciphers_status<<endl;
	//#
	//Key/Cert Files laden
	//openssl req -x509 -newkey rsa:4096 -subj "/C=DE/ST=B-W/L=ROT/O=Bit-Devil Inc./OU=Org/CN=blockchain.more.corp" -keyout key.pem -out cert.pem -days 365
	//openssl rsa -in key.pem -out key2.pem 		#Passwort entfernen
	int tls_config_set_key_file_status = 666;
	tls_config_set_key_file_status = tls_config_set_key_file(config, "/etc/blockchain/key2.pem");
	//tls_config_set_key_file_status = tls_config_set_key_file(config, "key2.pem");
	//cout<<"tls_config_set_key_file_status#"<<tls_config_set_key_file_status<<endl;
	//#
	int tls_config_set_cert_file_status = 666;
	tls_config_set_cert_file_status = tls_config_set_cert_file(config, "/etc/blockchain/cert.pem");
	//tls_config_set_cert_file_status = tls_config_set_cert_file(config, "cert.pem");
	//cout<<"tls_config_set_cert_file_status#"<<tls_config_set_cert_file_status<<endl;
	//#
	int tls_configure_status = 666;
	tls_configure_status = tls_configure(tls, config);
	//cout<<"tls_configure_status#"<<tls_configure_status<<endl;
	//########################################################################

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);

	if (socket_desc == -1)
	{
		cout<<"Could not create socket"<<endl;
	}
	//cout<<"Socket created"<<endl;
	 
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	//server.sin_port = htons(8888);
	int bc_server_listen_port = atoi(config_file_parameter[1].c_str());
	server.sin_port = htons(bc_server_listen_port);

	//Bind
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        cout<<"bind failed. Error"<<endl;
		cout<<"socket_desc#"<<socket_desc<<endl;
		exit(-1);
        //return 1;
    }
	//cout<<"bind done"<<endl	;
	
	//Listen . "man 2 listen"
	//listen(socket_desc , 3);
	listen(socket_desc , 128);
     
    //Accept and incoming connection
    //cout<<"Waiting for incoming connections..."<<endl;
    c = sizeof(struct sockaddr_in);
	//cout<<"c#"<<endl;
          
	////Accept and incoming connection
	cout<<"\e[1m"<<"!!! ### bc_server # Ready for Client Connections ### !!!"<<"\e[0m"<<endl;

//#####################################################################
if (local_chain_longer_than_remote == true)
{
//string asd ; cout<<"CIN bc_server is listen LOCAL_CHAIN_LONGER_THAN_REMOTE"<<endl; cin>>asd;

	cout<<"bc_server is listen and LOCAL_CHAIN_LONGER_THAN_REMOTE"<<endl; 
	//cout<<"local_chain_longer_than_remote"<<local_chain_longer_than_remote<<endl;
	//cout<<"remote_ip#"<<remote_ip<<endl;

//Sende Blöcke an Remote Peer	
void send_peer_local_chain_longer_and_send_blocks();
send_peer_local_chain_longer_and_send_blocks();
	
	local_chain_longer_than_remote = false;
}
//#####################################################################

	//cout<<"Ready for Client Connections"<<endl;
	//c = sizeof(struct sockaddr_in);
	
	pthread_t thread_id;

	int tls_accept_socket_status = 666;
	char client_message[2000];	
	int bytes;

	//sc = accept(sock, (struct sockaddr *) &client, &client_size);
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	//while( (client_sock = accept(sock, (struct sockaddr *) &client, &client_size)) )
	{

		//sleep(1);
		tls_accept_socket(tls, &tls2, client_sock);
		//cout<<"tls_accept_socket_status#"<<tls_accept_socket_status<<endl;



		//bytes = tls_read(tls2, client_message, 1000);
		//cout<<"bytes#"<<bytes<<endl;
		//cout<<"client_message#"<<client_message<<endl;

		
		//cout<<"Connection accepted"<<endl;
		//printf("ip is: %s\n", inet_ntoa(client.sin_addr));
		//cout<<"Client IP: "<<inet_ntoa(client.sin_addr)<<endl;
		remote_ip = inet_ntoa(client.sin_addr);
		//cout<<"remote_ip#"<<remote_ip<<endl;
		//###########################
		/*
		char ip_address[15];
		int fd;
		struct ifreq ifr;
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		ifr.ifr_addr.sa_family = AF_INET;  
		memcpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
		//memcpy(ifr.ifr_name, "*", IFNAMSIZ-1);
		ioctl(fd, SIOCGIFADDR, &ifr);
		close(fd);
		//strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		cout<<"LOCAL#"<<inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr)<<"#"<<endl;
		//printf("System IP Address is: %s\n",ip_address);
		cout<<"Local Address:"<<ip_address<<endl;
		*/
/*
struct ifaddrs * ifAddrStruct=NULL;
struct ifaddrs * ifa=NULL;
void * tmpAddrPtr=NULL;      
string ip;

getifaddrs(&ifAddrStruct);

for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
{
	if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
		// is a valid IP4 Address
		tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
		char addressBuffer[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
		//printf("'%s': %s\n", ifa->ifa_name, addressBuffer); 
		ip = ifa->ifa_name;
		//cout<<"IF#"<<ip<<"#"<<endl;
		//cout<<"IP#"<<addressBuffer<<"#"<<endl;
		lokal_ip_adresse = addressBuffer;
		if (lokal_ip_adresse == "127.0.0.1")
		{
			continue;
		}
		cout<<"IF#"<<ip<<"#"<<endl;
		cout<<"IP#"<<addressBuffer<<"#"<<endl;
	} 
}
if (ifAddrStruct!=NULL)
{
	cout<<"freeifaddrs"<<endl;
	freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct
}
*/
//###################################

//posix Thread für Socket############################################################################################################################################
		int pth_rc = -1 ;
		//	pthread_create(&threads[1] , NULL , dbsize_eintraege     ,(void *)&thread_nummer_1);
		pth_rc = pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock);
		//cout<<"Posix Thread Retrun Code#"<<pth_rc<<"#"<<endl;
		if( pth_rc != 0 )
		{
			//printf("Konnte Thread nicht erzeugen\n");
			cout<<"Posix Thread Return Code#"<<pth_rc<<"#"<<endl;
			return EXIT_FAILURE;
		}
/*
if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
{
	cout<<"could not create thread"<<endl;;
	return 1;
}
*/
		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( thread_id , NULL);
		//cout<<"Handler assigned"<<endl;



//############################################################################################################################################
	
	}

	if (client_sock < 0)
    {
        cout<<"accept failed"<<endl;
        return 1;
    }

	close(socket_desc);
	//close(c);
	
	
	
//####################################################################

}