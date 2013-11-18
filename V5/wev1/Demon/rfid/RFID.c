#include "Main.h"

int fd, baud, RFID_fd;
char CharArr[255];

char OpenSerialPort(void);
int ArgOpenSerialPort(char *SerialPortName, int baudRate);

char *SerialPortName[] = {	"/dev/ttyUSB0",
							"/dev/ttyUSB1",
							"/dev/ttyUSB2",
							"/dev/ttyUSB3",
							"/dev/ttyUSB4",
							"/dev/ttyUSB5",
							"/dev/ttyUSB6",
							"/dev/ttyUSB7",
							"/dev/ttyUSB8",
							"/dev/ttyUSB9",    
							"/dev/ttyS0",
							"/dev/ttyS1",                                                           
							"/dev/ttyS2",
							"/dev/ttyS3",
							"/dev/ttyS4",
							"/dev/ttyS5",
							"/dev/ttyS6",
							"/dev/ttyS7",
							"/dev/ttyS8",
							"/dev/ttyS9"
						};

void main (){
	FILE *rfid_fp;
	char PrevLine[512];
	char Line[512];
	char *ArrStr[4];
	char *StrPtr;
	char StrSerialPortName[64];
	int len;
	/********************Open RFID connected serial port*********************/
		system("/bin/dmesg | grep FTDI > /home/ab.c");
		rfid_fp = fopen("/home/ab.c", "r");
		while( GetLine(rfid_fp, Line) != 0){
			strcpy(PrevLine, Line);
			//printf("%s\n", Line);
		}
		printf("---\n %s\n", PrevLine);
		StrPtr = strstr(PrevLine, "FTDI USB Serial Device converter now attached to");
		if(StrPtr == NULL) {
			printf("\n******************************************\nError : The RFID Sensor is not connected\n******************************************\n");
		} else {
			StrPtr = strstr(PrevLine, "tty");
			strcpy(StrSerialPortName, "/dev/");
			strcat(StrSerialPortName, StrPtr);
			len = strlen(StrSerialPortName);
			printf(">>>%s -- %d\n", StrSerialPortName, len);
			StrSerialPortName[len] = 0;
			RFID_fd = ArgOpenSerialPort(StrSerialPortName, 9600);
		}
	
	/********************Open Co-Processor connected serial port*********************/
		system("/bin/dmesg | grep pl2303 > /home/ab.c");
		rfid_fp = fopen("/home/ab.c", "r");
		while( GetLine(rfid_fp, Line) != 0){
			strcpy(PrevLine, Line);
			//printf("%s\n", Line);
		}
		printf("---\n %s\n", PrevLine);
		StrPtr = strstr(PrevLine, "pl2303 converter now attached to");
		if(StrPtr == NULL) {
			printf("\n******************************************\nError : The Co-Processor is not connected\n******************************************\n");
		} else {
			StrPtr = strstr(PrevLine, "tty");
			strcpy(StrSerialPortName, "/dev/");
			strcat(StrSerialPortName, StrPtr);
			len = strlen(StrSerialPortName);
			printf(">>>%s -- %d\n", StrSerialPortName, len);
			StrSerialPortName[len] = 0;
			fd = ArgOpenSerialPort(StrSerialPortName, 9600);
		}

	    //OpenSerialPort();
		while(1){
			memset(CharArr, 0, sizeof(CharArr));
			read(RFID_fd, CharArr, 12);
			printf("%s",CharArr);
		}
}

int ArgOpenSerialPort(char *SerialPortName, int baudRate){
	int SerialPortStatus = 0;
    int fd, i=0;

	fd = nu_SerialComPort_Open(SerialPortName);
	if(fd < 0) {
		return -1;
	}
	else
 	{
		printf("Able to open the SerialPort %s \n ",SerialPortName);

    	if(nu_SerialComPort_Init(fd, baudRate) < 0 ){
    		printf("baud not set");
		    return -1;
    	}
	}
	return fd;
}

char OpenSerialPort(void){
	int SerialPortStatus = 0;
    int i=0;
    while(i<20){
      	fd = nu_SerialComPort_Open(SerialPortName[i]);
	    if(fd < 0) {
        }
	    else{
 	        printf("Able to open the SerialPort %s \n ",SerialPortName[i]);
  	        SerialPortStatus = 1;
            break;
	    }
	    i++;
	    
    }

    if(SerialPortStatus != 0){
        baud = 9600;    //atoi(argv[2]);
    	if(nu_SerialComPort_Init(fd, baud) < 0 ){
    		printf("baud not set");
		    return 0;
    	} 
    }
    else{
            printf("Unable to open the SerialPort \n ");
   		    return ;
    }
    return 1;
}
