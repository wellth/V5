#include <stdlib.h>
#include <math.h>
#include <stdio.h>  
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>   
#include <errno.h> 
#include <termios.h>
#include "SerialComPort.h"

#include <string.h>

#define ENABLE_TIMEOUT
#define OK_RESPONSE_TIMEOUT_SEC 1


static int sms_fd;
char CharArr;
unsigned char retStr[255];

int open_sms_port(){
	FILE*rfid_fp;
	sms_fd = -1;
	char PrevLine[512];
	char Line[512];
	char *ArrStr[4], cha = 0;
	char *StrPtr, co_start;
	char StrSerialPortName[64];
	int len, i, dum_fd;
#if 0
//	system("/bin/dmesg | grep \"cp210x converter now\" > /home/ab.c");
	system("/bin/dmesg | grep \"pl2303 converter now\" > /home/ab.c");
	rfid_fp = fopen("/home/ab.c", "r");
	while( GetLine(rfid_fp, Line) != 0){
		strcpy(PrevLine, Line);
		//printf("%s\n", Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "pl2303 converter now attached to");
//	StrPtr = strstr(PrevLine, "cp210x converter now attached to");
	if(StrPtr == NULL) {
		printf("\n******************************************\nError : The QuecTel Board is not connected\n******************************************\n");
		return 0;
	} else {
		StrPtr = strstr(PrevLine, "tty");
		strcpy(StrSerialPortName, "/dev/");
		strcat(StrSerialPortName, StrPtr);
		len = strlen(StrSerialPortName);
		printf(">>>%s -- %d\n", StrSerialPortName, len);
		StrSerialPortName[len] = 0;
		//strcpy(MODBUS_USB, StrSerialPortName);
		//fd = ArgOpenSerialPort(StrSerialPortName, 19200);
		sms_fd = InitMODEM(StrSerialPortName);
		if (sms_fd < 0){
			printf("\nAlert: reconnect the QuecTel port USB and restart the ");
			return 0;
		} else {
			//SerialPortStatus = 1;
		}
	}
	if(sms_fd < 0) {
		printf("__Error : The Co-Processor is not connected __");
		return 0;
	}
#endif
	
	sms_fd  = InitMODEM("/dev/ttyO1");
//	sms_fd  = ArgOpenSerialPort("/dev/ttyO1", 9600);
		if (sms_fd < 0){
			printf("\nAlert: reconnect the master co-processor port USB and restart the daemon");
			return 0;
		} else {
			//SerialPortStatus = 1;
		}
	if(sms_fd < 0) {
		printf("__Error : The Co-Processor is not connected __");
		return 0;
	}
	printf("Quectel Connected to-%s", StrSerialPortName);
	return sms_fd;
}


int InitMODEM(char *portNameMODEM){ // return GPRS_fd (non zero opened discripter number) on success and zero(0) on error
	int bytes_written = 0;
	struct timeval start;
	long prevSecVal = 0;
	int testStartTime =0;
	int tries=0;

	int GPRS_fd = ArgOpenSerialPort( portNameMODEM, 19200);
	if(GPRS_fd < 0) {
		printf("not able to open serial port /dev/ttyUSB0 \n");
		return (0);
	}
	else{
		nu_SerialComPort_Init (GPRS_fd, 19200);
		tcflush (GPRS_fd, TCIOFLUSH);
		bytes_written = serial_port_write(GPRS_fd, "AT\r\n");
		printf("byte written= %d\n", bytes_written);
#if 0		
		for(tries=0; tries<3; tries++){
			memset(retStr, 0, sizeof(retStr));
			timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 4);
			printf("%s", retStr);
			if(strncmp(retStr, "AT", 2) == 0){
				memset(retStr, 0, sizeof(retStr));
				timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 4);
				printf("%s", retStr);
				if(strncmp(retStr, "OK", 2) == 0){
					return (GPRS_fd);
				} else {
					return (0);
				}
			} else {
				return (0);
			}
		}
		return 0;
#endif
#if 1
		while(1){
			if( read(GPRS_fd, &CharArr, 1) > 0)
				printf("%c", CharArr);
			if(CharArr == 'O'){
				nu_SerialComPort_BlockRead (GPRS_fd, retStr, 3);
				printf("response= %s\n", retStr);
				break;
			}
#ifdef ENABLE_TIMEOUT
			gettimeofday(&start, NULL);
			if(prevSecVal != start.tv_sec){
				prevSecVal = start.tv_sec;
				testStartTime++;
			}
			if(testStartTime >= OK_RESPONSE_TIMEOUT_SEC){
				return (GPRS_fd);
			}
#endif

		}
		return (GPRS_fd);
#endif
	}
}

int getSignalStrength(int GPRS_fd){
	int index = 0, i = 0, bytes_written;
	struct timeval start;
	long prevSecVal = 0;
	int testStartTime =0, nbytes;
	int tries=0, sigStrength;
	char sigStrnthStr[4], *ptr;
	int comEchoDone=0, csqResDone=0, dummyDone=0, complete=0;

#if 0
	for(tries=0; tries<3; tries++){
		tcflush (GPRS_fd, TCIOFLUSH);
		if ( (bytes_written = serial_port_write(GPRS_fd, "AT+CSQ\r\n")) >= 8)
			printf("byte written= %d\n", bytes_written);
		else
			return 0;

		memset(retStr, 0, sizeof(retStr));
		timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 8);
		printf("%s", retStr);

		memset(retStr, 0, sizeof(retStr));
		timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 14);

		if( strncmp(retStr, "+CSQ", 4) == 0){
			printf("%s", retStr);
			ptr = strchr(&retStr[6], ',');
			*ptr = '\0';
			ptr = &retStr[6];
			printf("%s\n", ptr);
			sigStrength = atoi(ptr);
			memset(retStr, 0, sizeof(retStr));
			timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 3);
			printf("%s", retStr);
			memset(retStr, 0, sizeof(retStr));
			timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 5);
			printf("%s", retStr);
			if( strncmp(retStr, "OK", 2) == 0 ){
				return (sigStrength);
			} else {
				//retry return (0);
			}
		}
		return (-1);
	}
#endif
#if 1
	while(1){
#if 0
		while ((nbytes = read(fd, bufptr, sizeof(buffer) - 1)) > 0)
		{
			printf("---%d\n", nbytes);
break;
			bufptr += nbytes;
			if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
				break;
		}
#endif	
#if 1
		if( read(GPRS_fd, &CharArr, 1) > 0){
			retStr[index++] = CharArr;
			printf("%c\n", CharArr);
		}
		if(CharArr == 'O'){
			printf("entered in ");
			nu_SerialComPort_BlockRead (GPRS_fd, retStr, 3);
			while(i < index) {
				printf("%c -- index %d", retStr[i], index);
				i++;
			}
			printf("response= %s\n", retStr);
			break;
		}
#endif
#ifdef ENABLE_TIMEOUT
		gettimeofday(&start, NULL);
		if(prevSecVal != start.tv_sec){
			prevSecVal = start.tv_sec;
			testStartTime++;
		}
		if(testStartTime >= OK_RESPONSE_TIMEOUT_SEC){
			return (0);
		}
#endif

	}
#endif
}

int selectSMSFormat(int GPRS_fd, char *format){
	int bytes_written = 0;
	struct timeval start;
	long prevSecVal = 0;
	int testStartTime =0;
	char sendBuffer[32];

	tcflush (GPRS_fd, TCIOFLUSH);
	if(format[0] == 't' || format[0] == 'T')
		strcpy(sendBuffer, "AT+CMGF=1\r\n");
	else if(format[0] == 'p' || format[0] == 'P')
		strcpy(sendBuffer, "AT+CMGF=0\r\n");
	else
		strcpy(sendBuffer, "AT+CMGF=1\r\n");
		
	if ( (bytes_written = serial_port_write(GPRS_fd, sendBuffer)) >= 11)
		printf("byte written= %d\n", bytes_written);
	else
		return 0;

	while(1){
		if( read(GPRS_fd, &CharArr, 1) > 0)
			printf("%c", CharArr);
		if(CharArr == 'O'){
			nu_SerialComPort_BlockRead (GPRS_fd, retStr, 3);
			printf("response= %s\n", retStr);
			break;
		}

#ifdef ENABLE_TIMEOUT
		gettimeofday(&start, NULL);
		if(prevSecVal != start.tv_sec){
			prevSecVal = start.tv_sec;
			testStartTime++;
		}
		if(testStartTime >= OK_RESPONSE_TIMEOUT_SEC){
			return (0);
		}
#endif
	}
}

int sendMsgCammand(char* number){
	
}

int sendSMSTo(int GPRS_fd, char* number, char* SMSBuffer){
	int bytes_written = 0;
	struct timeval start;
	long prevSecVal = 0;
	int testStartTime =0, len;
	char sendBuffer[164];
	long int delay = 10000000;
	sprintf(sendBuffer, "AT+CMGS=\"%s\"\r\n", number);

	if ( (bytes_written = serial_port_write(GPRS_fd, sendBuffer)) >= 25)
		printf("byte written= %d\n", bytes_written);
	else
		return 0;

	while(delay--);
	strcpy(sendBuffer, SMSBuffer);
	len = strlen(SMSBuffer);
	sendBuffer[len] = 0x1A;

	if ( (bytes_written = serial_port_write(GPRS_fd, sendBuffer)) >= len)
		printf("byte written= %d\n", bytes_written);
	else
		return 0;

	while(1){
		if( read(GPRS_fd, &CharArr, 1) > 0)
			printf("%c", CharArr);
		if(CharArr == 'O'){
			timeout_SerialComPort_BlockRead (GPRS_fd, retStr, 3);
			printf("response= %s\n", retStr);
			break;
		}

#ifdef ENABLE_TIMEOUT
		gettimeofday(&start, NULL);
		if(prevSecVal != start.tv_sec){
			prevSecVal = start.tv_sec;
			testStartTime++;
		}
		if(testStartTime >= OK_RESPONSE_TIMEOUT_SEC){
			return (0);
		}
#endif
	}
}
