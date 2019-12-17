//clear; rm -frv create_gpg_encryption.o; g++-7 -g -fPIC -Wall -c create_gpg_encryption.cpp
//"gpg --cipher-algo AES256 --batch --quiet --yes --symmetric --armor"	= Manuell erzeugen
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

#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <gpgme.h>

using namespace std;

extern string zu_hashende_daten;
extern string gpg_encryption;
extern vector<string> config_file_parameter;

#define SIZE 1024

bool invalidChar3 (char c) 
{  
   return !(c>=0 && c <128);   
} 
	
void create_gpg_encryption()
	{
		//cout<<"create_gpg_encryption.cpp"<<endl;
		//cout<<"\e[1m"<<"create_gpg_encryption.cpp"<<"\e[0m"<<endl;
		
		char buf[SIZE];
	
	gpgme_check_version (NULL);
	gpgme_error_t err;
	gpgme_data_t plain, cipher;
	gpgme_ctx_t ctx;
	gpgme_key_t recp[2] = { NULL, NULL };
	gpgme_encrypt_flags_t flags = GPGME_ENCRYPT_ALWAYS_TRUST;
	gpgme_new (&ctx);
	gpgme_set_armor (ctx, 1);
	
	
	//char *fp = "6AA609E8";				//gpg --list-keys -> "pub   1024R/29EEBC53 2018-09-16"
	//cout<<"GPG Key in create_gpg_encryption.cpp config_file_parameter[4]"<<config_file_parameter[4]<<endl;
	char *fp =  (char *) config_file_parameter[4].c_str();				//gpg --list-keys -> "pub   1024R/29EEBC53 2018-09-16"
	
	gpgme_get_key (ctx, fp, &recp[0], 0);
	//char *plaintext = "##### BLOCK CHAIN HASHWERT #####\0";
	//char *plaintext = "54d85a5a23ecc1f2b6695458eca362a4fd599821a760c054179bc0463bfe1f9105c3551f75659421694f638830aa8343b56ae0c455a8870046ad81b2ae77c31e";
	char *plaintext = (char *) zu_hashende_daten.c_str();
	//cout<<"plaintext in create_gpg_encryption#"<<zu_hashende_daten<<endl;
	
	err = gpgme_data_new_from_mem (&plain, plaintext, strlen(plaintext), 0);
	//cout<<"gpgme_data_new_from_mem"<<err<<endl;
	gpgme_data_new (&cipher);
	gpgme_op_encrypt (ctx, recp, flags, plain, cipher);

	gpgme_data_seek(cipher, 0, SEEK_SET);
	//size_t max_buflen = 2048, buflen;
	size_t max_buflen = 999999, buflen;
	//buflen = gpgme_data_read(cipher, buf, max_buflen);
	//cout<<"buflen gpgme_data_read"<<buflen<<endl;
	int ret;
	ret = gpgme_data_seek (cipher, 0, SEEK_SET);
	while ((ret = gpgme_data_read (cipher, buf, max_buflen)) > 0) 
	{
		// Write the contents of "buf" to "outputFile"
		//fwrite (buf, ret, 1, outputFile);
		//cout<<buf;
		gpg_encryption.append(buf);
	}
	
	//cout<<"gpg_encryption in create_gpg_encryption.cpp#"<<gpg_encryption<<endl;
	
	gpgme_data_release (cipher);
	gpgme_data_release (plain);
	gpgme_release (ctx);

	//##########################################################################
	//Nur den Entschlüsselungs Code übergeben###
	//wo_ist_newline = gpg_encryption.find("\n");
	//cout<<"wo_ist_newline#"<<wo_ist_newline<<endl;
	//gpg_encryption = gpg_encryption.substr(wo_ist_newline, gpg_encryption.length() );
	//Die ersten drei Zeilen löschen (-----BEGIN PGP MESSAGE----- .. Version: GnuPG v2 )
	//for (int i = 0; i < 3; i++)
	//for (unsigned long long i = 0; i < 3; i++)
	for (unsigned long long i = 0; i < 2; i++)
	{
		gpg_encryption.erase(0, gpg_encryption.find("\n") + 1);
	}
	//gpg_encryption.erase(0, gpg_encryption.find("\n") + 1);
	//gpg_encryption.erase(0, gpg_encryption.find("\n") + 1);
	//cout<<"gpg_encryption LÖSCHEN  \\n#"<<gpg_encryption<<endl;

	int wo_ist_end_pgp_message = -1;
	wo_ist_end_pgp_message = gpg_encryption.find("--END PGP MESSAGE--");
	//gpg_encryption = gpg_encryption.substr(0,wo_ist_end_pgp_message);
	//gpg_encryption = gpg_encryption.substr(0,wo_ist_end_pgp_message - 1);
	//cout<<"gpg_encryption#"<<gpg_encryption<<endl;
	if (wo_ist_end_pgp_message != -1){gpg_encryption = gpg_encryption.substr(0,wo_ist_end_pgp_message - 1);}else{cout<<"PROBLEM in create_gpg_encryption.cpp gpg_encryption z. 110 "<<endl; exit(-1);}
	//cout<<"gpg_encryption#"<<gpg_encryption<<endl;

	gpg_encryption.erase(remove_if(gpg_encryption.begin(),gpg_encryption.end(), invalidChar3), gpg_encryption.end()); 
	//cout<<"gpg_encryption###"<<gpg_encryption<<"###"<<endl;
	//##########################################################################

	/* free data */
	//gpgme_data_release(data);

	/* free context */
	//gpgme_release(ctx);
	
	//cout<<"ENDE"<<endl;
	}