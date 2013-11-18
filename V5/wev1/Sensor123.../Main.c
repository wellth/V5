#include "Main.h"

#define IN_TEXT_FILE            "MDB/in.txt"
#define IN_ENTERY_FILE       "MDB/Inpt.csv"
#define OT_TEXT_FILE           "MDB/out.txt"
#define OT_ENTERY_FILE      "MDB/Data.csv"

typedef struct{
	char Weight[10];
	char Comma;
	char Hight[10];
}_INPUT_DATA;
_INPUT_DATA Din;

typedef struct{
	char InBuf[10];
}_IN_FILE;
_IN_FILE Indata;

typedef struct{
	char Weight[10];
	char Comma;
	char BmiValue[10];
}_BMI_TEST;
_BMI_TEST Bmi;

typedef struct{
	char SysP[10];
	char Comma1;
	char DiaP[10];
	char Comma2;
	char PulseRate[10];
}_BP_TEST;
_BP_TEST Bp;

typedef struct{
	char BliValue[10];
}_BLI_TEST;
_BLI_TEST Bli;

/********************************************************************************************
			Function Declarations
*********************************************************************************************/
void CheckEndOfTest(void);
void DisplayMessage(void);
void OpenSerialPort(void);   	
void CallWhileLoop(void);
void ReadInputFile(void);
float ConvertHexToFloat(void);
extern unsigned char  ModbusOP(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer, unsigned char  numRetries);
extern unsigned char  ConstructRequest(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer,MDB_REQ_ADU *MbReqAdu, MDB_RSP_ADU *MbRspAdu);
/********************************************************************************************
			Variable Declarations
*********************************************************************************************/
int fd;
int baud,TestNo;
char cbuf;
short int MdbResponse = 0;	
short int Hight=0,TempWeight;
float Weight,Sub,Mul;
unsigned char MdbFlag = 0;
unsigned char RxBuf[100];
unsigned char TxBuf[30];
unsigned char BmiBuf[10];
unsigned char TempBuf[10];
volatile unsigned int LoopCase = 1;
	
extern unsigned short int BmiTestEn;
extern unsigned short int BpTestEn;
extern unsigned short int BliTestEn;
extern unsigned char HoldingReg[10];
float BMIValue;
float BLIValue;
volatile unsigned char Buf[5];
FILE *fp;

/********************************************************************************************
			Main Starts Here
*********************************************************************************************/
int main(int argc, char **argv[]){
	if(argc < 2) {
        printf("please input proper arguments");
		return -1;
 	}
	fd = nu_SerialComPort_Open(argv[1]);
	if(fd < 0) {
        printf("Error opening device");
        return -2;
	}
    baud = atoi(argv[2]);
    OpenSerialPort();	
    LoopCase = 1;
    MdbFlag = 0;
    printf(" Wellth System is runing \n");
    CallWhileLoop();
    close(fd);
	return 0;
}

void ReadInputFile(void){
    FILE *ffp;
    ffp = fopen (IN_TEXT_FILE, "r");
    if(ffp<0){
        printf(" System is not able to open file \n");
       LoopCase = 0;    
    }
    else{
        fread(&Indata,sizeof(Indata),1,ffp);
        fclose(ffp);
        if(strcmp(Indata.InBuf,"WeTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 1;
        }
        else if(strcmp(Indata.InBuf,"BpTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 2;
        }
        else if(strcmp(Indata.InBuf,"BliTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 3;
        }
        else{
            TestNo =0;
        }
       LoopCase = 1;    
    }
}
void CallWhileLoop(void){
	while(1){
		switch(LoopCase){		
			case 1:
                  ReadInputFile();
                 if(TestNo == 1){
                         LoopCase = 2;    
                        printf("Demon Code has received the Hight = ");
                        fp = fopen (IN_ENTERY_FILE, "r");
                        if(fp<0){
                            printf(" System is not able to open file \n");
                        }
                        else{
                            fread(&Din,sizeof(Din),1,fp);
                            fclose(fp);
                        }
                        sscanf(&Din.Hight,"%d",&Hight);
                        memset(Din.Hight,0,10);
                        printf("%d\n",Hight);
  			            printf("\n");     
  			            printf("BMI Test Starts Now \n");             
                    }
                    else if(TestNo == 2){
                        printf("Bp Test Starts Now \n");
                        LoopCase = 6;    
                    }
                    else if(TestNo == 3){
                        printf("BLI Test Starts now \n");      
                        printf("Demon Code has received the Hight = ");
                        fp = fopen (IN_ENTERY_FILE, "r");
                        if(fp<0){
                            printf(" System is not able to open file \n");
                        }
                        else{
                            fread(&Din,sizeof(Din),1,fp);
                            fclose(fp);
                        }
                        sscanf(&Din.Weight,"%d",&TempWeight);
                        sscanf(&Din.Hight,"%d",&Hight);
                        memset(Din.Weight,0,10);
                        memset(Din.Hight,0,10);
                        printf("The Hight Value %d\n",Hight);
                        printf("%d\n",Hight);
                       printf("The Weight Value %d\n",TempWeight);
                        printf("BLI Test Starts now \n");      
                       LoopCase = 9;  
  			            printf("\n");     
                  }
                  else{
                      LoopCase = 1;    
                  }
             break;
             //<<<<<<<<<<<<.................................................. Sensor No 1 Interface.......................................................................................>>>>>>>>>>>>>//
			case 2:
		       HoldingReg[1] = 0x00;   
               HoldingReg[0] = 0x01;
               MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000A, 0x000l, (unsigned char *)HoldingReg,1);
               if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
               }
               else{
               printf("Modbus Error Response %d \n",MdbResponse);
                    HoldingReg[1] = 0x00;   
                    HoldingReg[0] = 0x00;
     				LoopCase = LoopCase +1;
                }
			break;			
			case 3:
                MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
                if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
    				LoopCase = LoopCase +1;
    				BmiTestEn = 1;
                }
             break;
             case 4:      
                 MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000A, 0x0002, (unsigned char *)HoldingReg, 1);
                 if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
                 }
                else{  
                    Weight = ConvertHexToFloat();
                    printf("Modbus Got Sensor Response\n");
                    printf("Your Weight is = %f\n",Weight);   
                    BMIValue  = (Weight/Hight)*10000;
                    BMIValue = BMIValue / Hight;
                    printf("Your BMI Level is = %f\n",BMIValue);   
    				Buf[0] = '1';
                    memset(TempBuf,0,10);
                    sprintf(TempBuf,"%f",Weight);
                    strcpy(Bmi.Weight,TempBuf);
                    memset(TempBuf,0,10);
                    sprintf(TempBuf,"%f",BMIValue);
                    strcpy(Bmi.BmiValue,TempBuf);
                    memset(TempBuf,0,10);
                    
                    fp = fopen (OT_ENTERY_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Bmi,sizeof(Bmi),1,fp);
                        fclose(fp);
                    }
                    fp = fopen (OT_TEXT_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Buf,1,1,fp);
                        fclose(fp);
                    }
                    printf(" Demon has completed the  Wellth BMI Test\n");
                    BmiTestEn = 0;
             		LoopCase = 1;
                    printf("LoopCase Value is %d\n",LoopCase);
                    fp  = fopen(IN_ENTERY_FILE,"w");
                    fclose(fp);
                    fp = fopen(IN_TEXT_FILE,"w");
                    fclose(fp);                    
                }
             break;
             case 5:
             break;

             //<<<<<<<<<<<<.................................................. Sensor No 2 Interface.......................................................................................>>>>>>>>>>>>>//
             
			case 6:		
		       HoldingReg[1] = 0x00;   
               HoldingReg[0] = 0x01;
               MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000B, 0x000l, (unsigned char *)HoldingReg,1);
               if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
               }
               else{
                    HoldingReg[1] = 0x00;   
                    HoldingReg[0] = 0x00;
     				LoopCase = LoopCase +1;
                }
			break;			
			case 7:
                MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
                if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
    				LoopCase = LoopCase +1;
                    BpTestEn = 1;
                }
             break;
             case 8:      
                 MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000B, 0x0002, (unsigned char *)HoldingReg, 1);
                 if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
                 }
                else{  
                    printf("Modbus Got Sensor Response\n");
                    printf("Systolic Pressure is = %d\n",BmiBuf[0]);   
                    printf("Diastolic Pressure is = %d\n",BmiBuf[1]);   
                    printf("Pulse Rate is = %d\n",BmiBuf[2]);   
                    BpTestEn = 0;
                    Buf[0] = '1';
                    
                    sprintf(Bp.SysP,"%d",BmiBuf[0]);
                    sprintf(Bp.DiaP,"%d",BmiBuf[1]);
                    sprintf(Bp.PulseRate,"%d",BmiBuf[2]);
                   
                    fp = fopen (OT_ENTERY_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Bp,sizeof(Bp),1,fp);
                        fclose(fp);
                    }
                    fp = fopen (OT_TEXT_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Buf,1,1,fp);
                        fclose(fp);
                    }
                    printf(" Demon has completed the  Wellth BMI Test\n");
             		LoopCase = 1;
                    printf("LoopCase Value is %d\n",LoopCase);
                    fp  = fopen(IN_ENTERY_FILE,"w");
                    fclose(fp);
                    fp = fopen(IN_TEXT_FILE,"w");
                    fclose(fp);   
                }
             break;       
             
             //<<<<<<<<<<<<.................................................. Sensor No 3 Interface.......................................................................................>>>>>>>>>>>>>//
           case 9:
                LoopCase = LoopCase +1;
  			 break;  			 	  
			case 10:		
		       HoldingReg[1] = 0x00;   
               HoldingReg[0] = 0x01;
               MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000C, 0x000l, (unsigned char *)HoldingReg,1);
               if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
               }
               else{
                    HoldingReg[1] = 0x00;   
                    HoldingReg[0] = 0x00;
     				LoopCase = LoopCase +1;
                }
			break;			
			case 11:
                MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
                if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
    				LoopCase = LoopCase +1;
                    BpTestEn = 1;
                }
             break;
             case 12:      
                 MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000C, 0x0002, (unsigned char *)HoldingReg, 1);
                 if(MdbResponse!=0){
                    #if defined	SHOW_DISPLAY
                        printf("Modbus Error Response %d \n",MdbResponse);
                     #endif
                 }
                else{  
                    BliTestEn =  1;
                    BLIValue = ConvertHexToFloat();
                    printf("Modbus Got Sensor Response\n");
                    printf("Sensor Response is  = %f\n",BLIValue);   
                    BLIValue  = BLIValue*10000;
                    Mul = (Hight*Hight)/BLIValue;
                    Sub  = 12.297 + (0.287*Mul);
                    BLIValue  = 0.697 * TempWeight;
                    BLIValue = BLIValue  - Sub;
                    printf("Your BMI Level is = %f\n",BLIValue);   
    				LoopCase = 1;
                    BliTestEn =  0;
    				Buf[0] = '1';
                    memset(TempBuf,0,10);
                    sprintf(TempBuf,"%f",BLIValue);
                    strcpy(Bli.BliValue,TempBuf);
                    memset(TempBuf,0,10);
                    
                    fp = fopen (OT_ENTERY_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Bli,sizeof(Bli),1,fp);
                        fclose(fp);
                    }
                    fp = fopen (OT_TEXT_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Buf,1,1,fp);
                        fclose(fp);
                    }
                    printf(" Demon has completed the  Wellth BMI Test\n");
                    BliTestEn = 0;
             		LoopCase = 1;
                    printf("LoopCase Value is %d\n",LoopCase);
                    fp  = fopen(IN_ENTERY_FILE,"w");
                    fclose(fp);
                    fp = fopen(IN_TEXT_FILE,"w");
                    fclose(fp);            
                }
             break;        
             default:
			 break;
		}
	}
}

void OpenSerialPort(void){
	if(nu_SerialComPort_Init(fd, baud) < 0 ){
		printf("baud not set");
		return ;
	} 
}
void DisplayMessage(void){
 	printf("You are in Wellth System \n");
	printf("Enter 1 To Check Your BMI Level\n");
	printf("Enter 2 To Check Your Blood Pressure  \n");
	printf("Enter 3 To Check Your BLI Level\n");
}

float ConvertHexToFloat(void){
        float Result;
        signed int Bmi;
        long int Byte1=0,Byte2=0,Byte3=0,Byte4=0;
        
        if(BliTestEn){
          Byte1 = BmiBuf[1];
            Byte2  = BmiBuf[0];
            Byte2 = (Byte2<<8);
            Byte3 = BmiBuf[3];
            Byte3 = (Byte3<<16);
            Byte4= BmiBuf[2];
            Byte4  = (Byte4<<24);
        }        
        else
        {        
            Byte1 = BmiBuf[0];
            Byte2  = BmiBuf[1];
            Byte2 = (Byte2<<8);
            Byte3 = BmiBuf[2];
            Byte3 = (Byte3<<16);
            Byte4= BmiBuf[3];
            Byte4  = (Byte4<<24);
        }        
        Bmi = (Byte1| Byte2| Byte3|Byte4);    
        printf("The int value is %x \n",Bmi);    
        Result = *((float *)&Bmi);     
        return Result;
}


