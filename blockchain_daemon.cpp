//PRD debug: rm -frv blockchain_daemon; clear; g++-7 -g -fPIC -Wall blockchain_daemon.cpp -o blockchain_daemon -static-libstdc++
//PRD compile: rm -frv blockchain; clear; g++-7 -O3 -fPIC -Wall blockchain.cpp -o blockchain -static-libstdc++

//rm -frv blockchain_daemon.o; g++-7 -Wall -g -c blockchain_daemon.cpp
//rm -frv hasher.o; clear; g++-7 -g -fPIC -Wall -c hasher.cpp
//rm -frv timestamp.o; clear; g++-7 -g -fPIC -Wall -c timestamp.cpp
//rm -frv read_previous_chains.o; clear; g++-7 -g -fPIC -Wall -c read_previous_chains.cpp
//rm -frv create_gpg_signature.o; clear; g++-7 -g -fPIC -Wall -c create_gpg_signature.cpp
//rm -frv insrert_bc_to_db.o; clear; g++-7 -g -fPIC -Wall -c insrert_bc_to_db.cpp
//rm -frv send_block_to_server.o; g++-7 -g -fPIC -Wall -c  send_block_to_server.cpp
//rm -frv get_last_block.o; g++-7 -g -fPIC -Wall -c get_last_block.cpp
//rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c  read_config_file.cpp
//rm -frv create_gpg_encryption.o; g++-7 -g -fPIC -Wall -c create_gpg_encryption.cpp
//rm -frv blockchain; g++-7 -g -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -o blockchain blockchain_daemon.o hasher.o send_block_to_server.o get_last_block.o read_config_file.o -static-libstdc++
//#######################################################################################################
//Einzeiler DEV# clear; rm -frv create_gpg_encryption.o; g++-7 -g -fPIC -Wall -c create_gpg_encryption.cpp;rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c  read_config_file.cpp;rm -frv get_last_block.o; g++-7 -g -fPIC -Wall -c get_last_block.cpp ;rm -frv send_block_to_server.o; g++-7 -g -fPIC -Wall -c send_block_to_server.cpp ; rm -frv insrert_bc_to_db.o; g++-7 -g -fPIC -Wall -c insrert_bc_to_db.cpp; rm -frv create_gpg_signature.o; g++-7 -g -fPIC -Wall -c create_gpg_signature.cpp ;rm -frv read_previous_chains.o; g++-7 -g -fPIC -Wall -c read_previous_chains.cpp ;rm -frv timestamp.o; g++-7 -g -fPIC -Wall -c timestamp.cpp ;rm -frv blockchain_daemon.o; g++-7 -Wall -g -c blockchain_daemon.cpp; rm -frv hasher.o; g++-7 -g -fPIC -Wall -c hasher.cpp; rm -frv blockchain; g++-7 -g -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -o blockchain blockchain_daemon.o hasher.o timestamp.o read_previous_chains.o create_gpg_signature.o insrert_bc_to_db.o send_block_to_server.o get_last_block.o read_config_file.o create_gpg_encryption.o -static-libstdc++ ;date;
//Einzeiler PRD# clear; rm -frv create_gpg_encryption.o; g++-7 -O3 -fPIC -Wall -c create_gpg_encryption.cpp;rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c  read_config_file.cpp;rm -frv get_last_block.o; g++-7 -O3 -fPIC -Wall -c get_last_block.cpp ;rm -frv send_block_to_server.o; g++-7 -O3 -fPIC -Wall -c send_block_to_server.cpp ; rm -frv insrert_bc_to_db.o; g++-7 -O3 -fPIC -Wall -c insrert_bc_to_db.cpp; rm -frv create_gpg_signature.o; g++-7 -O3 -fPIC -Wall -c create_gpg_signature.cpp ;rm -frv read_previous_chains.o; g++-7 -O3 -fPIC -Wall -c read_previous_chains.cpp ;rm -frv timestamp.o; g++-7 -O3 -fPIC -Wall -c timestamp.cpp ;rm -frv blockchain_daemon.o; g++-7 -Wall -O3 -c blockchain_daemon.cpp; rm -frv hasher.o; g++-7 -O3 -fPIC -Wall -c hasher.cpp; rm -frv blockchain; g++-7 -O3 -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -o blockchain blockchain_daemon.o hasher.o timestamp.o read_previous_chains.o create_gpg_signature.o insrert_bc_to_db.o send_block_to_server.o get_last_block.o read_config_file.o create_gpg_encryption.o -static-libstdc++ ;date;

//Test mit Dummydaten
//timeout 60 cat /dev/random | xxd -ps | awk '{print " # "b++ strftime(" %Y%m%d-%H:%M:%S", systime()) }' | xargs -I % ./blockchain "%"
//while true ; do timeout 0.5 ./blockchain ASDF; done;
//clear; time seq 1000 | xargs -n 1 ./blockchain ASDF 			= 1000 Durchläufe
//Normaler Aufruf
// ./blockchain "<TRANSAKTION DATEN>"

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
#include <pthread.h>
//Header für setrlimit (ulimits setzen)
#include <sys/resource.h>

using namespace std;

//Public Variablen für Object Files
//hasher.cpp
string zu_hashende_daten;
//timestamp.cpp
string aktuelle_zeit;
//read_prevoious_hash.cpp
string vorhandene_ketten;
string last_block_chain_id;
string previous_hash_block;
//create_gpg_signature.cpp
string gpg_signature;
//insrert_bc_to_db.cpp
string block_formated_redis;
string block_formated;
string gpg_encryption;
string config_file_pfad;

vector<string> config_file_parameter;

bool invalidChar (char c) 
{  
    return !(c>=0 && c <128);   
} 

void signalHandler( int signum) 
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	cout<<"PROBLEM Blockchain daemon"<<endl;
	
	exit (666);
}

int main(int argc, char *argv[]) 
{

	//cout<<"Blockchain start"<<endl;

//Wenn ARGV Initial angegebn wird. Den ersten Block Chain Wert schreiben und warnen das ggf. alle vorherigen Daten gelöscht werden.

//####################################################################
	//Error Signals
//ZUR FEHLERSUCH CORE DUMPS SCHREIBEN UND NICHT ABFANGEN. IN PRD WIEDER AKTIVIEREN.

	signal(SIGSEGV, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGINT, signalHandler);
	//sleep(300);

//####################################################################

//####################################################################
//Debug to File by sap_bcc.cpp
//ofstream debug_file;
//debug_file.open ("/tmp/blockchain_daemon.cpp_debug_file.log", ios::app );
//####################################################################

//###################################################################################################################
	//Resource limit vergroessern (ulimit). Wird an Child Prozesse vererbt
	struct rlimit rl;
	//getrlimit (RLIMIT_CPU, &rl);
	rl.rlim_cur = RLIM_INFINITY;		//#RLIM_INFINITY = unlimited
	rl.rlim_max = RLIM_INFINITY;		//#RLIM_INFINITY = unlimited
	
	//#http://man7.org/linux/man-pages/man2/getrlimit.2.html		#cat /proc/<PID>/limits
	setrlimit(RLIMIT_AS, &rl);
	setrlimit(RLIMIT_CORE,&rl);
	setrlimit(RLIMIT_CPU,&rl);
	setrlimit(RLIMIT_DATA,&rl);
	setrlimit(RLIMIT_FSIZE,&rl);
	setrlimit(RLIMIT_LOCKS,&rl);
	setrlimit(RLIMIT_MEMLOCK,&rl);
	setrlimit(RLIMIT_MSGQUEUE,&rl);
	setrlimit(RLIMIT_NPROC,&rl);
	setrlimit(RLIMIT_RSS,&rl);
	setrlimit(RLIMIT_RTPRIO,&rl);
	setrlimit(RLIMIT_RTTIME,&rl);
	setrlimit(RLIMIT_SIGPENDING,&rl);
	setrlimit(RLIMIT_STACK,&rl);
	
	//#########
	//Number of open file. Nimmt INFINITY nicht an
	struct rlimit rl_open_files;
	rl_open_files.rlim_cur = 1024;
	rl_open_files.rlim_max = 999999;
	setrlimit(RLIMIT_NOFILE,&rl_open_files);
	//#############
	
	//echo "999999999" > /proc/sys/fs/pipe-max-size

//###################################################################################################################


	//Config aus Datei lesen
	config_file_pfad = "/etc/blockchain/bc.cfg";
	void read_config_file();
	read_config_file();
	//cout<<"config_file_parameter#"<<config_file_parameter[0]<<endl;
	
//###################################################################	
	/*
	string buchung;
	cout<<"Daten der ersten Buchung eingeben"<<endl;
	cin>>buchung;
	cout<<"buchung"<<buchung<<endl;
	cout<<" Transaktion gespeichert"<<endl;
	cout<<"index";
	cout<<"timestamp";
	cout<<"hash";
	cout<<"Prevoius hash";
	*/
	
	//Buchungsdaten hashen
	//zu_hashende_daten = "Hash in main";
	//cout<<"zu_hashende_daten#"<<zu_hashende_daten<<endl;
	
//ARGV darf nicht mehr als 999999 Zeichen haben, da sonst die socket recv() funktionenen nicht korrekt funktioniert. Daher noch eine Prüfung einbauen !!!!
	string transaktions_rohdaten;
	transaktions_rohdaten = argv[1];
	//cout<<"transaktions_rohdaten#"<<transaktions_rohdaten<<endl;
	
	//SONDERZEICHEN MASKIEREN, RAUSSCHMEISEN, UTF8 konvertieren#######################################
	
//Letzte Block Kette aus Redis lesen#########################################################################

	//void read_previous_chains();
	//read_previous_chains();
	void get_last_block();
	get_last_block();
	//AUCH HIER AUF DEN BLOCKCHAIN SERVER GEHEN
	//Get Chain Size und get singel block wegen preivios hash

	//cout<<"vorhandene_ketten#"<<vorhandene_ketten<<endl;
	//cout<<"last_block_chain_id#"<<last_block_chain_id<<endl;;
	//cout<<"previous_hash_block#"<<previous_hash_block<<endl;;
	//debug_file<<"previous_hash_block in blockchain_daemon.cpp#"<<previous_hash_block<<"#"<<endl;

//#########################################################################
	
	
//Zeitstempel ermitteln####################################################

	void zeitstempel();
	zeitstempel();
	
	//cout<<"aktuelle_zeit#"<<aktuelle_zeit<<endl;

//#########################################################################


//Transaktionrohsdaten hashen############################

	//zu_hashende_daten = transaktions_rohdaten;
	
	//64 (this is a non-standard GNU extension) Range:	-9223372036854775808 to 9223372036854775807(signed) or 0-18446744073709551616(unsigned)
	unsigned long long block_chain_id_long_long;
	block_chain_id_long_long = stoll(last_block_chain_id);
	
	//unsigned long long previous_block_chain_id_long_long;
	//previous_block_chain_id_long_long = stoll(last_block_chain_id);
	
	//cout<<"last_block_chain_id_long_long#"<<last_block_chain_id_long_long<<endl;
	block_chain_id_long_long = block_chain_id_long_long + 1;
	//cout<<"block_chain_id_long_long#"<<block_chain_id_long_long<<endl;
	string block_chain_id_string;
	stringstream strstream;
	strstream << block_chain_id_long_long;
	strstream >> block_chain_id_string;
		
	//Bsp: bc-id: 3 # timestamp: 16.09.2018 16:30:30.307151371 # data: Transaktion 3 , 50€ an Alex
	zu_hashende_daten = "bc-id: " + block_chain_id_string + " # timestamp: " + aktuelle_zeit + " # Transaktion " + block_chain_id_string + " data: " + transaktions_rohdaten;
	//cout<<"zu_hashende_daten in blockchain_daemon.cpp#"<<zu_hashende_daten<<"#"<<endl;
	//debug_file<<"zu_hashende_daten in blockchain_daemon.cpp#"<<zu_hashende_daten<<"#"<<endl;
	
	//Object File definieren
	void hasher();
	hasher();
	
	//zu_hashende_daten = "NACH modul";
	//cout<<"TR hash in blockchain_daemon.cpp#"<<zu_hashende_daten<<endl;
	//debug_file<<"TR hash in blockchain_daemon.cpp#"<<zu_hashende_daten<<"#"<<endl;
	
//###################################################

//Nun ganzen Block hashen inkl Prevoius Block###################################################
	zu_hashende_daten = zu_hashende_daten + previous_hash_block;
	//cout<<"zu_hashende_daten#"<<zu_hashende_daten<<endl;
	void hasher();
	hasher();
	
	//cout<<"gesammter block hash#"<<zu_hashende_daten<<"#"<<endl;
	//debug_file<<"gesammter block hash in blockchain_daemon.cpp#"<<zu_hashende_daten<<"#"<<endl;
////###################################################

	
//####################################################################
//GnuPG prüfen ob Key angelegt wurde initial.
//GnuPG Agent konfiguieren und starten
//Initial beim starten einmal das Passwort von hand eingeben
//killall -q gpg-agent
//GPG Key Einmal Inital starten, manuell
//eval $(gpg-agent --daemon --enable-ssh-support --write-env-file "${HOME}/.gpg-agent-info")
	//eval $(gpg-agent --daemon)
//####################################################################

//GnuPG Hash verschlüsseln###################################################

	void create_gpg_encryption();
	create_gpg_encryption();
	
	//gpg_encryption = "-----BEGIN PGP MESSAGE-----\nVersion: GnuPG v2\n\n" + gpg_encryption + "-----END PGP MESSAGE-----\n";

	//cout<<"gpg_encryption###"<<gpg_encryption<<"####"<<endl;
	
	//cout<<"####################################################################"<<endl;
	//cout<<"####################################################################"<<endl;
	//cout<<"####################################################################"<<endl;
	
//####################################################################

//GnuPG Signature erzeugen###################################################

	//zu_hashende_daten
	void create_gpg_signature();
	create_gpg_signature();
	
	//cout<<"gpg_signature#"<<gpg_signature<<endl;
//###################################################

//Block Format zusammenbauen//###################################################
	//bc-id: 3 # timestamp: 16.09.2018 16:30:30.307151371 # data: Transaktion 3 , 50€ an Alex # prevoius_hash_bc-id 2: c94f4e029ef2ef # hash_block 3: 2a0ab7f1e4d824f # gpg_signature: -----BEGIN PGP SIGNED MESSAGE-----
	//cout<<"block_chain_id_string"<<block_chain_id_string<<endl;
	//cout<<"aktuelle_zeit"<<aktuelle_zeit<<endl;
	//cout<<"block_chain_id_string"<<block_chain_id_string<<endl;
	//cout<<"transaktions_rohdaten"<<transaktions_rohdaten<<endl;
	//cout<<"last_block_chain_id"<<last_block_chain_id<<endl;
	//cout<<"previous_hash_block"<<previous_hash_block<<endl;
	//cout<<"block_chain_id_string"<<block_chain_id_string<<endl;
	//cout<<"zu_hashende_daten"<<zu_hashende_daten<<endl;
	//cout<<"gpg_signature"<<gpg_signature<<endl;
	//cout<<"###BLOCK###"<<endl<<endl;
	//string block_formated;
	block_formated = "bc-id: " + block_chain_id_string + " # timestamp: " + aktuelle_zeit + " # Transaktion " + block_chain_id_string + " data: " + transaktions_rohdaten + " # prevoius_hash_bc-id " + last_block_chain_id + ": " + previous_hash_block + " # hash_block " + block_chain_id_string + ": " + zu_hashende_daten + " # gpg_signature: " + gpg_signature; 
	//cout<<block_formated<<endl;
	//cout<<"###ENDE-BLOCK###"<<endl;
	//string block_formated;
	//block_formated_redis = "redis-cli LPUSH blockchain_list \'bc-id: " + block_chain_id_string + " # timestamp: " + aktuelle_zeit + " # Transaktion " + block_chain_id_string + " data: " + transaktions_rohdaten + " # prevoius_hash_bc-id " + last_block_chain_id + ": " + previous_hash_block + " # hash_block " + block_chain_id_string + ": " + zu_hashende_daten + " # gpg_signature: " + gpg_signature + "\'"; 
	//block_formated_redis = "LPUSH blockchain_list \'bc-id: " + block_chain_id_string + " # timestamp: " + aktuelle_zeit + " # Transaktion " + block_chain_id_string + " data: " + transaktions_rohdaten + " # prevoius_hash_bc-id " + last_block_chain_id + ": " + previous_hash_block + " # hash_block " + block_chain_id_string + ": " + zu_hashende_daten + " # gpg_signature: " + gpg_signature + "\'"; 
	//block_formated_redis = "RPUSH blockchain_list \'bc-id: " + block_chain_id_string + " # timestamp: " + aktuelle_zeit + " # Transaktion " + block_chain_id_string + " data: " + transaktions_rohdaten + " # prevoius_hash_bc-id " + last_block_chain_id + ": " + previous_hash_block + " # hash_block " + block_chain_id_string + ": " + zu_hashende_daten + " # gpg_signature: " + gpg_signature + "\'"; 
	//cout<<"block_formated_redis#"<<block_formated_redis<<endl;
	
	//###########
	//remove non ASCII Chars
	//block_formated_redis.erase(remove_if(block_formated_redis.begin(),block_formated_redis.end(), invalidChar), block_formated_redis.end());  
	block_formated.erase(remove_if(block_formated.begin(),block_formated.end(), invalidChar), block_formated.end());  
	//block_formated_redis = block_formated_redis + "\n";
	//cout<<"block_formated#"<<block_formated<<endl;
	//##############

//Formatiert Block in redis schreiben###################################################

	//void insert_in_db();
	//insert_in_db();
	
	//Besser via Protokoll zum Blockchain Server senden
	void send_block_to_server();
	send_block_to_server();

	cout<<endl;
	//cout<<"BLOCK: "<<block_formated<<endl;
	cout<<"Block ID: "<<block_chain_id_string<<endl;
	cout<<"Transaktions Daten : "<<transaktions_rohdaten<<endl;
	
//###################################################

//###################################################
//Debug file schliesen.
//debug_file<<"###ENDE###"<<endl;
//debug_file.close();
//###################################################

	return (0);
}
