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

extern string aktuelle_zeit;

void zeitstempel()
	{
		//cout<<"ZEIT"<<endl;
		//aktuelle System Zeit in variable schreiben###################
		time_t Zeitstempel;
		tm *nun;
		Zeitstempel = time(0);
		nun = localtime(&Zeitstempel);
		
		//Tag
		int tag;
		tag = nun->tm_mday;
		string current_tag_string;
		std::stringstream ConvertStream_2;
		ConvertStream_2<<tag;
		ConvertStream_2>>current_tag_string;
		//cout<<current_tag_string<<endl;
		int anzahl_ziffern = current_tag_string.length();
		if (anzahl_ziffern < 2)
		{
			current_tag_string = "0" + current_tag_string;
			//cout<<"current_tag_string"<<current_tag_string<<endl;
		}
		
		//Monat
		int monat;
		monat = nun->tm_mon+1;
		//cout << "The local date and time is: " << asctime(monat) << endl;
		string current_monat_string;
		std::stringstream ConvertStream_3;
		ConvertStream_3<<monat;
		ConvertStream_3>>current_monat_string;
		//cout<<current_monat_string<<endl;
		anzahl_ziffern = current_monat_string.length();
		if (anzahl_ziffern < 2)
		{
			current_monat_string = "0" + current_monat_string;
			//cout<<"current_monat_string"<<current_monat_string<<endl;
		}
		
		//Jahr
		int current_jahr;
		current_jahr = nun->tm_year+1900;
		string current_jahr_string;
		std::stringstream ConvertStream_4;
		ConvertStream_4<<current_jahr;
		ConvertStream_4>>current_jahr_string;
		//cout<<current_jahr_string<<endl;
		
		//Stunde
		int current_stunde;
		current_stunde = nun->tm_hour;
		string current_stunde_string;
		std::stringstream ConvertStream_5;
		ConvertStream_5<<current_stunde;
		ConvertStream_5>>current_stunde_string;
		//cout<<current_stunde_string<<endl;
		anzahl_ziffern = current_stunde_string.length();
		if (anzahl_ziffern < 2)
		{
			current_stunde_string = "0" + current_stunde_string;
			//cout<<"current_stunde_string"<<current_stunde_string<<endl;
		}
		
		//Minute
		int current_minute;
		current_minute = nun->tm_min;
		string current_minute_string;
		std::stringstream ConvertStream_6;
		ConvertStream_6<<current_minute;
		ConvertStream_6>>current_minute_string;
		//cout<<current_minute<<endl;
		anzahl_ziffern = current_minute_string.length();
		if (anzahl_ziffern < 2)
		{
			current_minute_string = "0" + current_minute_string;
			//cout<<"current_minute_string"<<current_minute_string<<endl;
		}
		
		//Sekunde
		int current_sekunde;
		current_sekunde = nun->tm_sec;
		string current_sekunde_string;
		std::stringstream ConvertStream_7;
		ConvertStream_7<<current_sekunde;
		ConvertStream_7>>current_sekunde_string;
		//cout<<current_sekunde_string<<endl;
		anzahl_ziffern = current_sekunde_string.length();
		if (anzahl_ziffern < 2)
		{
			current_sekunde_string = "0" + current_sekunde_string;
			//cout<<"current_sekunde_string"<<current_sekunde_string<<endl;
		}
		
		/*
		//Microsekunden
		//int current_msec;
		long double current_msec;
		timeval time;
		gettimeofday(&time, NULL);
		current_msec = time.tv_usec;
		string current_msec_string;
		std::stringstream ConvertStream_8;
		ConvertStream_8<<current_msec;
		ConvertStream_8>>current_msec_string;
		//cout<<current_msec_string<<endl;
		*/
		
		//Nano Sekunden
		struct timespec time_structure;
		timespec_get(&time_structure, TIME_UTC);
		int current_nsec;
		current_nsec = time_structure.tv_nsec;
		string current_nsec_string;
		std::stringstream ConvertStream_8;
		ConvertStream_8<<current_nsec;
		ConvertStream_8>>current_nsec_string;
		//cout<<current_nsec_string<<endl;
		
		//Zeitstempel zusammenbauen
		string current_timestamp;
		current_timestamp = current_tag_string + "." + current_monat_string + "." + current_jahr_string + " " + current_stunde_string + ":" + current_minute_string + ":" + current_sekunde_string + "." + current_nsec_string ;
		//cout<<"Systemzeit:"<<current_timestamp<<endl; 
		
		aktuelle_zeit = current_timestamp;
	
		//##########################################
	
	}
	