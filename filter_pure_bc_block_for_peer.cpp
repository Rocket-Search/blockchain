//clear; rm -frv filter_pure_bc_block_for_peer.o; g++-7 -g -fPIC -Wall -c filter_pure_bc_block_for_peer.cpp

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

extern string pure_bc_block;

void filter_pure_bc_block_for_peer()
{
	//cout<<"\e[1m"<<"filter_pure_bc_block_for_peer.cpp"<<"\e[0m"<<endl;
	//cout<<"filter_pure_bc_block_for_peer.cpp"<<endl;
	//cout<<"pure_bc_block#"<<pure_bc_block<<endl;
	
	//Nachricht von Blockchain daemon:
	//set block ### bc-id: 12 # timestamp: 02.01.2019 13:36:29.566004716 # Transaktion 12 data: DADDSasdsad # prevoius_hash_bc-id 11: 57f91172396172bb180bf7b46b7438a8d9cd9ae49bea36e5b11e6b644227ec30306cb9bd7f4bd6c2276f1fe4e4ea329254fafd558195f3bc8f176c1cf80627f3 # hash_block 12: 4ddf0bb2b822bd238130a1fcf6de53db0723fd13e69ab068eb3519393f01463d93517aa681b935cde167663569e40ee8cd67da04d535d21e6b7df9086d22ed55 # gpg_signature: -----BEGIN PGP SIGNED MESSAGE-----@Hash: SHA512@@4ddf0bb2b822bd238130a1fcf6de53db0723fd13e69ab068eb3519393f01463d93517aa681b935cde167663569e40ee8cd67da04d535d21e6b7df9086d22ed55@-----BEGIN PGP SIGNATURE-----@Version: GnuPG v2@@iJwEAQEKAAYFAlwssE4ACgkQMSLX7mqmCejVEQQAr47YqEwg5FolZ0N/rMJYtSyz@bN6XSCN5FuvXjCWvKRubtgDbnCCHQYv83Mk/cHMs/fgFkI7I+8xU1Ylcc1SHeDNT@OT3L3xYeOc/0JjgaH0feP4TKDa4HdMaUfQC4a2SM+av5oFLglPooohL13niiEGch@2y27n1kJxPUS8fXKdIU=@=r50s@-----END PGP SIGNATURE-----@###
	
	int wo_ist_set_block = -1;
	wo_ist_set_block = pure_bc_block.find("set block to peer ###");
	//cout<<"wo_ist_set_block#"<<wo_ist_set_block<<endl;
	//pure_bc_block = pure_bc_block.substr(wo_ist_set_block + 22 ,pure_bc_block.length());		// "set block to bc_server### " abschneiden 14 zeichen
	if(wo_ist_set_block != -1){pure_bc_block = pure_bc_block.substr(wo_ist_set_block + 22 ,pure_bc_block.length());}else{cout<<"PROBLEM in filter_pure_bc_block_for_peer.cpp pure_bc_block"<<endl;}
	//cout<<"pure_bc_block#"<<pure_bc_block<<endl;
	
	int wo_ist_et_und_drei_gatter = -1;
	wo_ist_et_und_drei_gatter = pure_bc_block.rfind("###@###");
	//cout<<"wo_ist_et_und_drei_gatter#"<<wo_ist_et_und_drei_gatter<<endl;
	//pure_bc_block = pure_bc_block.substr(0,wo_ist_et_und_drei_gatter);		//von Pos. 0 bis zum ###@### anzeigen
	if(wo_ist_et_und_drei_gatter != -1){pure_bc_block = pure_bc_block.substr(0,wo_ist_et_und_drei_gatter);}else{cout<<"PROBLEM in filter_pure_bc_block_for_peer.cpp pure_bc_block"<<endl;}
		
	//cout<<"pure_bc_block#"<<pure_bc_block<<endl;
	
	//cout<<"ENDE"<<endl;
	
}