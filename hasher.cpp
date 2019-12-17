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

//OpenSSL (LibreSSL) Header für md5sum
//#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace std;

extern string zu_hashende_daten;

void hasher()
	{
		//cout<<"HASHER"<<endl;
		//cout<<"zu_hashende_daten#"<<zu_hashende_daten<<endl;
//####################################################################
//Debug to File by sap_bcc.cpp
//ofstream debug_file_3;
//debug_file_3.open ("/tmp/blockchain_daemon.cpp_debug_file.log", ios::app );
//####################################################################
		
		unsigned char digest[SHA512_DIGEST_LENGTH];
		//const char* string = "hello world"; 
		const char* string_sha512 = zu_hashende_daten.c_str(); 

		SHA512_CTX ctx;
		SHA512_Init(&ctx);
		SHA512_Update(&ctx, string_sha512, strlen(string_sha512));
		SHA512_Final(digest, &ctx);
	 
	 
		//char mdString[SHA512_DIGEST_LENGTH*2+1];
		/*
		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
			sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	 
		printf("SHA512 digest: %s\n", mdString);
		*/
		stringstream sha512_sum_2;
		
		//int i = 0;
		long long i = 0;
			
		for(i = 0; i < SHA512_DIGEST_LENGTH; i++) 
		{	
		
			//Konvertierung von const char array nach string
			 sha512_sum_2 << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned>(digest[i]);
		
		}
		
		
		string sha512_sum;
		
		sha512_sum = sha512_sum_2.str();
		//cout<<"sha512_sum#"<<sha512_sum<<endl;
		zu_hashende_daten = sha512_sum;
		
//debug_file_3<<"hasher.cpp z77 sha512_sum#"<<sha512_sum<<"#"<<endl;

//###################################################
//Debug file schliesen.
//debug_file_3.close();
//###################################################
	
	}
  