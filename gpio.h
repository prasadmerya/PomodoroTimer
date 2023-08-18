#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>

#define GPIO_PATH "/sys/class/gpio/"

//To Export GPIO
void exportGPIO(int gpioNUM){
	FILE *fp;
	fp=fopen(GPIO_PATH "export","w");
	if(fp == NULL)
	{
		perror("ERROR exporting GPIO");
	}else{
		fprintf(fp, "%d", gpioNUM);
        fclose(fp);
	}
}
//To Set GPIO direction
void setDirection(int gpioNUM,const char *direction){
	char path[50];
    sprintf(path,"%sgpio%d/direction",GPIO_PATH,gpioNUM);

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
       perror("Error setting Direction"); 
    }else{
	    fprintf(fp, "%s", direction);
        fclose(fp);
	}
}

//To Set GPIO value
void setValue(int gpioNUM,int value){
	char path[50];
    sprintf(path,"%sgpio%d/value",GPIO_PATH, gpioNUM);

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
		perror("Error setting value");
        
    }else{
		fprintf(fp, "%d", value);
        fclose(fp);
	}
}

//For Unexport GPIO
void unexportGPIO(int gpioNUM) {
    FILE *fp = fopen(GPIO_PATH "unexport", "w");
    if (fp == NULL) {
        perror("Error unexporting GPIO");
    } else {
        fprintf(fp, "%d", gpioNUM);
        fclose(fp);
    }
}

void init()
{
	int gpioNumber = 17;  // GPIO 17 used
	
    // Export GPIO
    exportGPIO(gpioNumber);

    // Set GPIO direction to "out"
    setDirection(gpioNumber, "out");

}

void Deinit()
{
	// Set GPIO value to low
    setValue(17, 0);
	// Unexport GPIO
    unexportGPIO(17);
}


#endif /*GPIO_H*/