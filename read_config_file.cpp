//clear; rm -frv read_config_file.o; g++-7 -g -fPIC -Wall -c  read_config_file.cpp

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

using namespace std;

extern vector<string> config_file_parameter;
extern string config_file_pfad;

void extern read_config_file()
{
	//cout<<"READ CONFIG FILE"<<endl;
	//cout<<"\e[1m"<<"read_config_file.cpp"<<"\e[0m"<<endl;
	
	//cout<<"config_file_pfad"<<config_file_pfad<<endl;
	
	ifstream fileoperation_conf;

	//fileoperation_conf.open("/etc/blockchain/bc.cfg", ios::in); 
	fileoperation_conf.open(config_file_pfad.c_str(), ios::in);
	
	string config_parameter = "";
	string config_parameter_2 = "";
	
	int gleich_gefunden = 0;
	
	while (!fileoperation_conf.eof())
	{
		getline(fileoperation_conf, config_parameter);
		//cout<<"config_parameter: "<<config_parameter<<endl;
		//Filter der einzelnen Parameter######
		
		if (config_parameter == "")
		{
			//cout<<"leer config_parameter_2"<<config_parameter<<endl;
			continue;
		}
		
		gleich_gefunden = config_parameter.find_last_of("=");
		//cout<<"config_parameter: "<<config_parameter.substr(gleich_gefunden + 1 ,99)<<endl;
		//config_parameter_2 = config_parameter.substr(gleich_gefunden + 2 ,999);
		try{config_parameter_2 = config_parameter.substr(gleich_gefunden + 2 ,999);}catch( std::out_of_range& exception ){cout<<"Error read_config_file.cpp z. 61 config_parameter_2 std::out_of_range"<<endl;}

		//cout<<"config_parameter_2:"<<config_parameter_2<<endl;
		config_file_parameter.push_back(config_parameter_2);
	
	}
	
	fileoperation_conf.close();
	
	//cout<<config_file_parameter.size()<<endl;
	//cout<<config_file_parameter[1]<<endl;
	//cout<<"ENDE"<<endl;
	
}
	
	