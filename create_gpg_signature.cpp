
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

extern string gpg_signature;
extern string zu_hashende_daten;
extern string gpg_encryption;

#define SIZE 1024
bool invalidChar2 (char c) 
{  
    return !(c>=0 && c <128);   
} 
	
void create_gpg_signature()
	{
		//cout<<"create_gpg_signature"<<endl;
		
		//cout<<"\e[1m"<<"create_gpg_signature.cpp"<<"\e[0m"<<endl;
		
		//###https://github.com/seiyak/GPGME-sample-code/blob/master/t-sign.c

		char *gnupg_api_version;
		//char buf[SIZE];
		//size_t read_bytes;
		//int tmp;
		gpgme_ctx_t ceofcontext;
		gpgme_error_t err;
		//gpgme_data_t data;
		
		//########################################
		setlocale (LC_ALL, "");
		gnupg_api_version = (char *) gpgme_check_version(NULL);
		//cout<<"gnupg_api_version#"<<gnupg_api_version<<endl;
		if (gnupg_api_version == NULL)
		{
			exit(666);
		}
		//printf("version=%s\n",p);
		/* set locale, because tests do also */
		gpgme_set_locale(NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));


		/* create our own context */
		err = gpgme_new(&ceofcontext);
		if(err != GPG_ERR_NO_ERROR) exit(666);
			
		//######################################

//######################################
//gpgme_hash_algo_name (GPGME_MD_SHA512);
//gpgme_hash_algo_t (GPGME_MD_SHA512);
//gpgme_ctx_set_engine_info (gpgme_ctx_t ctx, gpgme_protocol_t proto, const char *file_name, const char *home_dir)
//######################################


		// Set the context to textmode
		gpgme_set_textmode (ceofcontext, 1);
		// Enable ASCII armor on the context
		gpgme_set_armor (ceofcontext, 1);
		//gpgme_data_t in, out,plain;
		gpgme_data_t in, out;
//err = gpgme_data_new_from_mem (&in, "Hallo Leute\n", 12, 0);
//cout<<"zu_hashende_daten#"<<zu_hashende_daten<<endl;
//err = gpgme_data_new_from_mem (&in, zu_hashende_daten.c_str() , zu_hashende_daten.length(), 0);
err = gpgme_data_new_from_mem (&in, gpg_encryption.c_str() , gpg_encryption.length(), 0);
		//cout<<"gpgme_data_new_from_mem#"<<gpgme_data_new_from_mem<<endl;
		// Create a data object pointing to the out buffer
		err = gpgme_data_new (&out);
		// Error handling
		//cout<<"gpgme_data_new#"<<gpgme_data_new<<endl;
		gpgme_sig_mode_t sigMode = GPGME_SIG_MODE_CLEAR;
		err = gpgme_op_sign (ceofcontext, in, out, sigMode);
		//cout<<"gpgme_op_sign#"<<gpgme_op_sign<<endl;
		//cout<<"out#"<<out<<endl;
		//cout<<"out#"<<&out<<endl;
		int ret;
		ret = gpgme_data_seek (out, 0, SEEK_SET);
		//int BUF_SIZE = 512;
		int BUF_SIZE = 99999;
		char buf2[BUF_SIZE + 1];
		
		//char buf;
		while ((ret = gpgme_data_read (out, buf2, BUF_SIZE)) > 0) 
		{
			// Write the contents of "buf" to "outputFile"
			//fwrite (buf, ret, 1, outputFile);
			//cout<<buf2;
			gpg_signature.append(buf2);
		}

		//gpgme_recipients_release (rset);
		//gpgme_data_release (in);
		//gpgme_data_release (out);
		//gpgme_release (ctx);

		//Sonderzeichen und \n entfernen
		//cout<<"gpg_signature RAW###"<<gpg_signature<<"###"<<endl;
		//cout<<"####################################################################"<<endl;
		//cout<<"####################################################################"<<endl;
		//cout<<"####################################################################"<<endl;
	
		gpg_signature.erase(remove_if(gpg_signature.begin(),gpg_signature.end(), invalidChar2), gpg_signature.end());  
		//cout<<"gpg_signature ###"<<gpg_signature<<"###"<<endl;
		/*
		char chars[] = "\n";
		for (unsigned int i = 0; i < strlen(chars); ++i)
		{
			gpg_signature.erase(std::remove(gpg_signature.begin(), gpg_signature.end(), chars[i]), gpg_signature.end());
		}
		//cout<<"gpg_signature 2#"<<gpg_signature<<endl;
		*/
		int find_end_signature = -1;
		find_end_signature = gpg_signature.find("-----END PGP SIGNATURE-----");
		//gpg_signature =  gpg_signature.substr(0,find_end_signature + 27);
		if( find_end_signature != -1){gpg_signature =  gpg_signature.substr(0,find_end_signature + 27);}else{cout<<"PROBLEM in create_gpg_signature.cpp z.138 gpg_signature"<<endl;}
	
		//cout<<"gpg_signature 2,5#"<<gpg_signature<<endl;

		//An jedes Ende ein \n anfügen damit das später in redis passt####
		string gpg_signature_mit_crlf;
		istringstream f(gpg_signature);
		string zeile;    
		while (getline(f, zeile))
		{
			//cout << zeile <<"######"<< std::endl;
			gpg_signature_mit_crlf.append(zeile + "@");
			//gpg_signature_mit_crlf.append(zeile + "#");
			//gpg_signature_mit_crlf.append(zeile + "ENDE");
		}
		//cout<<"gpg_signature_mit_crlf#"<<gpg_signature_mit_crlf<<endl;
		gpg_signature = gpg_signature_mit_crlf;
		//cout<<"gpg_signature 3"<<gpg_signature<<endl;
		
		//Zum Entschlüsseln	 //echo "-----BEGIN PGP SIGNED MESSAGE-----@Hash: SHA512@@< KEY >@-----BEGIN PGP SIGNATURE-----@Version: GnuPG v2@@< KEY >@-----END PGP SIGNATURE-----@" |  sed 's/@/\n/g' | gpg -d
		
//ENDE################################################################################   
//cout<<"ENDE"<<endl;
	}
		
		