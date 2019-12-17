//clear; rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c read_config_file.cpp
//DEV//clear; rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c read_config_file.cpp ;rm -frv sap_bcc; g++-7 -g -fPIC -Wall sap_bcc.cpp -o sap_bcc read_config_file.o -static-libstdc++; date;
//PRD//clear; rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c read_config_file.cpp ;rm -frv sap_bcc; g++-7 -O3 -fPIC -Wall sap_bcc.cpp -o sap_bcc read_config_file.o -static-libstdc++; date;
//######################################
//cp -frv /root/smb_mount/cloud/Tech\ Docs/Programmieren/blockchain/sap_bcc /sapmnt/AL1/exe/uc/linuxx86_64/; chown al1adm:sapsys /sapmnt/AL1/exe/uc/linuxx86_64/sap_bcc
//######################################
//SAP Printer Commands
//https://help.sap.com/saphelp_nwmobile711/helpdata/en/d9/4a98ad51ea11d189570000e829fbbd/content.htm?no_cache=true
//SAP DB Report
// /nse38 -> /1BCDWB/DBBKPF
// /nse38 -> /1BCDWB/DBBSEG
//#####################################
//Files Verschlüsseln Sysmetirsch
//Verschl/Enc: gpg --passphrase test --cipher-algo AES256  --batch --quiet --yes --symmetric test.txt
//Entschl/Dec: gpg --passphrase test --batch --quiet --yes -o dec2.txt -d test.txt.gpg
//#####################################
//Manueller Aufruf. Achtung SAP Job abschalten (geplant).
//echo "BLABLA-`date`" > /tmp/print_file.txt; /sapmnt/AL1/exe/uc/linuxx86_64/sap_bcc /tmp/print_file.txt BSEG_Tabelle print_file.txt PASSWoRt
//time seq 10 | xargs -n 1 /usr/sap/bc_progs/sap_bcc_repeat.sh
//#####################################
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
//Header für setrlimit (ulimits setzen)
#include <sys/resource.h>
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
//iscntrl
#include <ctype.h>

using namespace std;

vector<string> config_file_parameter;
string config_file_pfad;

bool invalidChar (char c) 
{  
    return !(c>=0 && c <128);   
}
/*
bool invalidChar2 (char c) 
{  
    return !(iscntrl(c));   
}
*/
void signalHandler( int signum) 
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	cout<<"PROBLEM SAP Blockchain Connector"<<endl;
	
	exit (666);
}

int main(int argc, char *argv[]) 
{
		
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

	putenv("XTERM_LOCALE=en_US.UTF-8");
	putenv("LC_CTYPE=en_US.UTF-8");
	setlocale(LC_ALL, "en_US.UTF-8");
	//Bei csh "setenv LANG en_US.UTF-8"
	//LC_COLLATE=en_US.UTF-8
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


//####################################################################################################################	
	config_file_pfad = "/etc/blockchain/sap_bcc.cfg";
	void read_config_file();
	read_config_file();
	//cout<<"config_file_parameter#"<<config_file_parameter[0];
	
//####################################################################################################################


//Spool Parameter vom SAP System empfangen############################################################################
//####################################################################################################################
	//Spool File Path + Name  &F
	string sap_spool_file;
	sap_spool_file = argv[1];
	//cout<<"argv[1]#"<<sap_spool_file<<endl;
	
	//Spool Titel &T
	string sap_spool_titel;
	sap_spool_titel = argv[2];
	//cout<<"argv[2]#"<<sap_spool_titel<<endl;
	
	//Spool File Name &f
	string sap_spool_filename;
	sap_spool_filename = argv[3];
	//cout<<"argv[3]#"<<sap_spool_filename<<endl;
	
	//Spool File Name &f
	string pass;
	pass = argv[4];
	//cout<<"argv[4]#"<<pass<<endl;
	
	string copy_command ;
	//copy_command = "cp -fr " + sap_spool_file + " /usr/sap/bc_folder/";
	copy_command = config_file_parameter[0] + " -fr " + sap_spool_file + " " + config_file_parameter[1];
	//cout<<"copy_command#"<<copy_command<<endl;
	system(copy_command.c_str());
	
	string convert_to_utf;
	//convert_to_utf = "iconv  --verbose --from-code=iso-8859-1 --to-code=UTF-8 000hrRAX.AL1 > 000hrRAX.AL1_UTF"
	//convert_to_utf = "iconv  --verbose --from-code=iso-8859-1 --to-code=UTF-8 /usr/sap/bc_folder/" + sap_spool_filename + " > /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8";
	convert_to_utf = config_file_parameter[2] + " --verbose --from-code=iso-8859-1 --to-code=UTF-8 " + config_file_parameter[1] + sap_spool_filename + " > " + config_file_parameter[1] + sap_spool_filename + "_UTF8";
	//cout<<"convert_to_utf#"<<convert_to_utf<<endl;
	system(convert_to_utf.c_str());
	
	//string test;
	//test = "echo \"sap_spool_titel# " + sap_spool_titel + "  sap_spool_file# " + sap_spool_file + "   sap_spool_filename# " + sap_spool_filename + "\" >> /usr/sap/bc_folder/debug_file.log"  ;
	//system(test.c_str());
	
	//####################################
	//Bsp.
	//diff 000tDwTB.AL1 diff_bseg.txt
	//cp -frv 000tDwTB.AL1 diff_bseg.txt
	//rm -frv 000tDwTB.AL1
	//####################################
	string bseg_command_rueckgabe = "";
	string bkpf_command_rueckgabe_2 = "";
	
//BSEG Tabellen Daten einfangen####################################################################################################################
//####################################################################################################################	
	//if (sap_spool_titel == "BSEG_Tabelle")
	//cout<<"config_file_parameter[7]#"<<config_file_parameter[7]<<endl;
	if (sap_spool_titel == config_file_parameter[7])
	{

	//Entschl/Dec
	string dec_diff_file_command;
	//dec_diff_file_command = "gpg --passphrase test --batch --quiet --yes -o /usr/sap/bc_folder/diff_bseg.txt -d /usr/sap/bc_folder/diff_bseg.txt.gpg";
	//diff Dateinamen einheitlicher machen
	//dec_diff_file_command = config_file_parameter[3] + " --passphrase test --batch --quiet --yes -o " + config_file_parameter[1] +"/diff_bseg.txt -d "+ config_file_parameter[1] +  "/diff_bseg.txt.gpg";
	dec_diff_file_command = config_file_parameter[3] + " --passphrase " + pass + " --batch --quiet --yes -o " + config_file_parameter[1] +"/diff_bseg.txt -d "+ config_file_parameter[1] +  "/diff_bseg.txt.gpg";
	//cout<<"dec_diff_file_command#"<<dec_diff_file_command<<endl;
	system(dec_diff_file_command.c_str());
		
	//inhalt einfangen###############################################################
		string command;
		//command = "diff /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8 /usr/sap/bc_folder/diff_bseg.txt";
		//command = "diff --changed-group-format='%<%>' --unchanged-group-format='' /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8 /usr/sap/bc_folder/diff_bseg.txt";
		command = config_file_parameter[4] + " --changed-group-format='%<%>' --unchanged-group-format='' " + config_file_parameter[1] + sap_spool_filename + "_UTF8 " + config_file_parameter[1] + "diff_bseg.txt";
		//command = "diff -n /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8 /usr/sap/bc_folder/diff_bseg.txt";
		//command = "diff -n /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8 /usr/sap/bc_folder/diff_bseg.txt | cut -f 1 -d$'\n' --complement";
		//cout<<"command#"<<command<<endl;
		char *command_char = {(char *) command.c_str()}; 
		FILE *pipe;
		//char str[1000];
		char str[900000];
		//wchar_t str[50000];
		pipe = popen (command_char, "r" );
		if(pipe == NULL)
		{
			perror("open failed");
			pclose(pipe);
			exit(0);
		}
		//cout<<"Status popen signalHandler pipe# "<<pipe<<endl;
		//cout<<command_char<<endl;
		string command_rueckgabe_temp = "";
		//string command_rueckgabe = "";
		while(fgets ( str, 900000, pipe ) != NULL)
			{
				command_rueckgabe_temp = string(str);
				//command_rueckgabe.append(command_rueckgabe_temp);
				bseg_command_rueckgabe.append(command_rueckgabe_temp);
			}
		pclose(pipe);
		//##################################################################################

		//ofstream debug_file;
		//debug_file.open ("/usr/sap/bc_folder/debug_file.log", ios::app );
		////debug_file<<"sap_spool_titel# " + sap_spool_titel + "  sap_spool_file# " + sap_spool_file + "   sap_spool_filename# " + sap_spool_filename <<endl;
		////debug_file<<"BSEG DIFF INHALT# "<<bseg_command_rueckgabe<<endl;
		////debug_file<<convert_to_utf<<endl;
		//debug_file<<bseg_command_rueckgabe<<endl;
		//debug_file.close();
	
		//copy
		string cp_diff_file_command;
		//cp_diff_file_command = "cp -fr /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8 /usr/sap/bc_folder/diff_bseg.txt";
		cp_diff_file_command = config_file_parameter[0] + " -fr " + config_file_parameter[1] + sap_spool_filename + "_UTF8 " + config_file_parameter[1] + "diff_bseg.txt";
		//cout<<"cp_diff_file_command#"<<cp_diff_file_command<<endl;
		system(cp_diff_file_command.c_str());

		//Verschl/Encr
		string enc_diff_file_command;
		//enc_diff_file_command = "gpg --passphrase test --cipher-algo AES256 --batch --quiet --yes --symmetric /usr/sap/bc_folder/diff_bseg.txt";
		//enc_diff_file_command = config_file_parameter[3] + " --passphrase test --cipher-algo AES256 --batch --quiet --yes --symmetric " + config_file_parameter[1] + "diff_bseg.txt";
		enc_diff_file_command = config_file_parameter[3] + " --passphrase "+ pass + " --cipher-algo AES256 --batch --quiet --yes --symmetric " + config_file_parameter[1] + "diff_bseg.txt";
		//cout<<"enc_diff_file_command#"<<enc_diff_file_command<<endl;
		system(enc_diff_file_command.c_str());

		//löschen Spool File
		string rm_file_command;
		//rm_file_command = "rm -fr /usr/sap/bc_folder/" + sap_spool_filename ;
		rm_file_command = config_file_parameter[8] + " -fr " + config_file_parameter[1] + sap_spool_filename ;
		//cout<<"rm_file_command#"<<rm_file_command<<endl;
		system(rm_file_command.c_str());
		
		//löschen Spool File UTF8
		string rm_file_command_uft8;
		//rm_file_command_uft8 = "rm -fr /usr/sap/bc_folder/" + sap_spool_filename + "_UTF8";
		rm_file_command_uft8 = config_file_parameter[8] + " -fr " + config_file_parameter[1] + sap_spool_filename + "_UTF8";
		//cout<<"rm_file_command_uft8#"<<rm_file_command_uft8<<endl;
		system(rm_file_command_uft8.c_str());
		
		//löschen NICHT verschl File
		string rm_unencr_file_command;
		//rm_unencr_file_command = "rm -fr /usr/sap/bc_folder/diff_bseg.txt";
		rm_unencr_file_command = config_file_parameter[8] + " -fr " + config_file_parameter[1] + "diff_bseg.txt";
		//cout<<"rm_unencr_file_command#"<<rm_unencr_file_command<<endl;
		system(rm_unencr_file_command.c_str());

	}

//Datene in Blockchain Format bringen####################################################################################################################

	if (bseg_command_rueckgabe.length() > 0)
	{
		//ofstream debug_file_5;
		//debug_file_5.open ("/usr/sap/bc_folder/debug_file.log", ios::app );
		//debug_file_5<<"sap_spool_titel# " + sap_spool_titel + "  sap_spool_file# " + sap_spool_file + "   sap_spool_filename# " + sap_spool_filename <<endl;
		//debug_file_5<<"TEST# "<<ps_ef_rueckgabe<<endl;
		//debug_file_5<<"bseg_command_rueckgabe# "<<bseg_command_rueckgabe<<endl;
		//cout<<"bseg_command_rueckgabe# "<<bseg_command_rueckgabe<<endl;
		//debug_file_5.close();
/*	
//SSH kann nur max 4000 Charsacter in einem Argument übertragen. Daher hier Länge des Strings ermitteln und ggf. aufteilen
int bseg_command_rueckgabe_laenge = bseg_command_rueckgabe.size();
//debug_file_5<<"bseg_command_rueckgabe_laenge# "<<bseg_command_rueckgabe_laenge<<endl;
if (bseg_command_rueckgabe_laenge > 3000 )
{
	debug_file_5<<"bseg_command_rueckgabe_laenge# "<<bseg_command_rueckgabe_laenge<<endl;
	
}
*/
//###############################################

		// \n entfernen ggf. mit invalidChar2 arbeiten siehe create_gpg_signature.cpp
		int wo_ist_newline = -1;
		wo_ist_newline = bseg_command_rueckgabe.find("\n");
		if(wo_ist_newline != -1)
		{
			char chars[] = "\n";
			for (unsigned int i = 0; i < strlen(chars); ++i)
			{
				bseg_command_rueckgabe.erase(std::remove(bseg_command_rueckgabe.begin(), bseg_command_rueckgabe.end(), chars[i]), bseg_command_rueckgabe.end());
			}

			char chars2[] = "\r";
			for (unsigned int i = 0; i < strlen(chars2); ++i)
			{
				bseg_command_rueckgabe.erase(std::remove(bseg_command_rueckgabe.begin(), bseg_command_rueckgabe.end(), chars2[i]), bseg_command_rueckgabe.end());
			}
			
			char chars3[] = "\f";
			for (unsigned int i = 0; i < strlen(chars3); ++i)
			{
				bseg_command_rueckgabe.erase(std::remove(bseg_command_rueckgabe.begin(), bseg_command_rueckgabe.end(), chars3[i]), bseg_command_rueckgabe.end());
			}
		}

		bseg_command_rueckgabe.erase(remove_if(bseg_command_rueckgabe.begin(),bseg_command_rueckgabe.end(), invalidChar), bseg_command_rueckgabe.end());  

//C-Shel (csh) Special Character maskieren
//info: https://earthsci.stanford.edu/computing/unix/shell/specialchars.php		https://docstore.mik.ua/orelly/unix/upt/ch08_19.htm




		//debug_file_5<<"bseg_command_rueckgabe OHNE NEWLINE# "<<bseg_command_rueckgabe<<endl;

		/*
		bseg_command_rueckgabe.erase(0, bseg_command_rueckgabe.find("\n") + 1);
		cout<<"bseg_command_rueckgabe###"<<bseg_command_rueckgabe<<endl;
		
		
		int find_pfeil = 999;
		//while(find_pfeil == -1)
		//while(find_pfeil != NULL)
		//while(1)
		while(find_pfeil >= -1)
		{
			find_pfeil = bseg_command_rueckgabe.find('<');
			cout<<"find_pfeil#"<<find_pfeil<<endl;
			bseg_command_rueckgabe.erase(std::find(bseg_command_rueckgabe.begin(), bseg_command_rueckgabe.end(), '<')) ;
			cout<<"bseg_command_rueckgabe###"<<bseg_command_rueckgabe<<endl;
		}
		*/
		if (config_file_parameter[5] == "true")
		{

				//SSH Command zum Aufruf an dem Blockchain Server
				//ssh root@172.17.190.78 "/root/smb_mount/cloud/Tech\ Docs/Programmieren/blockchain/blockchain 'TEST DATEN' "
				string ssh_bc_command;
				//char32_t ssh_bc_command;
				//wchar_t ssh_bc_command;
				//u32string ssh_bc_command;
				//wstring ssh_bc_command;
				//ssh_bc_command = "ssh root@172.17.190.78 \"/root/smb_mount/cloud/Tech\\ Docs/Programmieren/blockchain/blockchain '" + bseg_command_rueckgabe + "'\"" ;
				//ssh_bc_command = "ssh root@172.17.190.84 \"/root/smb_mount/cloud/Tech\\ Docs/Programmieren/blockchain/blockchain '" + bseg_command_rueckgabe + "'\"" ;
				ssh_bc_command = config_file_parameter[6] + " " + config_file_parameter[9] + "@" + config_file_parameter[10] + " \"" + config_file_parameter[11] + "blockchain '" + bseg_command_rueckgabe + "'\"" ;
				//cout<<"ssh_bc_command#"<<ssh_bc_command<<endl;
				//debug_file_5<<"ssh_bc_command#"<<ssh_bc_command<<endl;
				system(ssh_bc_command.c_str());
		}
		if (config_file_parameter[5] == "false")
		{	
			//cout<<"Block Chain Generator Lokal aufrufen "<<endl;
		}
		
		if (config_file_parameter[5] == "false")
		{
			//cout<<"BC LOKAL"<<endl;
			string bc_command_local;
			bc_command_local = "/usr/bin/blockchain '" + bseg_command_rueckgabe + "'" ;
			system(bc_command_local.c_str());
		}
		
		//debug_file_5.close();
		 
	}
	return (0);
}
