#include <stdio.h>
#include <time.h>
#include <unistd.h>//sleep()
#include <stdlib.h>
#include <signal.h>
#include "gpio.h"
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

int tm_work;
int tm_break;
int tm_longbreak;
int focus_period;

bool flag_break;
bool flag_work;
bool flag_BUZZER;

int writeDatfile(char *filename,int data);
int readDatfile(char *filename);
void pomo_init();
void *Pomodorotimer(void *ptr);


// Signal handler function
void signal_handler(int sig)
{
	Deinit();//GPIO Deinitialization
	printf("\n.............Closing the program......\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	
	signal(SIGINT, &signal_handler);
	printf("\n.............Starting Pomodoro.....................\n");
	pomo_init();
	init();//GPIO Initialization
	//creating thread
	pthread_t trdTIMER;
	int td = pthread_create(&trdTIMER,NULL,Pomodorotimer,NULL);
	if (td != 0) {
        printf("Failed TO Create Thread\n");
        return 1;
    }
	
	struct timespec delay;
	delay.tv_sec = 1;
	delay.tv_nsec = 0;
	int cnt = 0;
	while(1){
		if(flag_BUZZER==true)
		{
			setValue(17, 1);//Buzzer ON(GPIO17)
			nanosleep(&delay,NULL);
			setValue(17, 0);//Buzzer OFF
			nanosleep(&delay,NULL);
			cnt++;
			if(cnt==3){
				flag_BUZZER=false;
				cnt=0;
			}
		}
	}
	
	pthread_join(trdTIMER,NULL);
	return 0;
}
//timer thread function
void *Pomodorotimer(void *ptr){
	int cnt = 0;
	while(1){
		printf("\nIt's Time for Focus\n");
		time_t prev=time(0);
		time_t ct=time(0);
        int diff=ct-prev;
		while(flag_work)//focus loop
		{
			ct=time(0);
			diff=ct-prev;
			int min,sec;
			min=diff/60;
			sec=diff%60;
			printf("\rFocus Time:%d:%d",min,sec);
			fflush(stdout);
			if(min==tm_work)//reset values
			{
				min=0;
				flag_break=true;
				flag_work=false;
				flag_BUZZER=true;
				cnt++;
			}
			sleep(1);
		}
		printf("\nCongratulations cycle %d Completed\n",cnt);
		int cond=tm_break;
		if(cnt==4){
			cond=tm_longbreak;
		}
		if(cnt==focus_period){
			flag_break=false;
		    raise(SIGINT);//EXIT the program
		}
		prev=time(0);
		while(flag_break)//break loop
		{
			ct=time(0);
			diff=ct-prev;
			int min,sec;
			min=diff/60;
			sec=diff%60;
			printf("\rBreak Time:%d:%d",min,sec);
			fflush(stdout);
			if(min==cond)//reset values
			{
				min=0;
				flag_work=true;
				flag_break=false;
				flag_BUZZER=true;
			}
			sleep(1);
		}
	}
}

//Initialization function
void pomo_init(){
	
	int rt = system("mkdir Configrutaion");
	//Checking the content of a data file for work/focus time. If not found, setting default values.
	tm_work=readDatfile((char *)"./Configrutaion/workFL.dat");
	if(tm_work==0)
	{
		tm_work=25;
		writeDatfile((char *)"./Configrutaion/workFL.dat",tm_work);
	}
	
	//Checking the content of a data file for short break time. If not found, setting default values.
	tm_break=readDatfile((char *)"./Configrutaion/breakFL.dat");
	if(tm_break==0)
	{
		tm_break=5;
		writeDatfile((char *)"./Configrutaion/breakFL.dat",tm_break);
	}
	
	//Checking the content of a data file for long break time. If not found, setting default values.
	tm_longbreak=readDatfile((char *)"./Configrutaion/longBreackFL.dat");
	if(tm_longbreak==0)
	{
		tm_longbreak=20;
		writeDatfile((char *)"./Configrutaion/longBreackFL.dat",tm_longbreak);
	}
	
	//Checking the content of a data file for focus period. If not found, setting default values.
	focus_period=readDatfile((char *)"./Configrutaion/FocusPeriod.dat");
	if(focus_period==0)
	{
		focus_period=4;
		writeDatfile((char *)"./Configrutaion/FocusPeriod.dat",focus_period);
	}
	//Display all settings
	printf("\nFocus Time:%d min, Short break:%d min, Focus Interval:%d times\n",tm_work,tm_break,focus_period);
	printf("If the focus interval is more than 4, then after the fourth cycle, you will get a %d-minute break.\n",tm_longbreak);
	printf("\n");
	// Get the current time
    time_t startTime;
    time(&startTime);
	
    int last = -1;

    // Run the loop for up to 5 seconds 
    while (difftime(time(NULL), startTime) < 5.0) {
        int current = (int)difftime(time(NULL), startTime);
        if (current != last) {
            printf("\rStarting in %d seconds", 6-current);
            fflush(stdout); // Flush the output buffer
            last = current;
        }
		// Sleep for a short time to avoid excessive printing
        usleep(500000); // Sleep for 500 milliseconds (0.5 seconds)
	}
	printf("\n");
	flag_work=true;
	flag_break=false;
	flag_BUZZER=false;
}

//function for reading file content and return 
int readDatfile(char *filename){
	int filecontent;
	char str[50];
	FILE *fp;
	
	fp=fopen(filename,"r");
	if(fp == NULL)
	{
		perror("Error while opening file");
		return 0;
	}
	
	 while (fgets(str, 50, fp) != NULL) {
        //printf("%s", str);
    }
	filecontent=atoi(str);
	fclose(fp);
	return filecontent;
}

//function for writting int value to file.
int writeDatfile(char *filename,int data)
{
	FILE *fp;
	
	fp=fopen(filename,"wb");
	if(fp == NULL)
	{
		perror("Error while opening file");
		return 1;
	}
	
	fprintf(fp, "%d", data);
	fclose(fp);
	return 0;
}