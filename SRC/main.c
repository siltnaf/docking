
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU Programme Demo ----------------------------*/
/* --- Fax: 86-755-82944243 ----------------------------------------*/
/* --- Tel: 86-755-82948412 ----------------------------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#include "../INC/STC12C5204AD.h"
#include "../INC/app.h"

/*************	??????	**************/

#

/************* ?????? **************/
void	Tx1Send(uchar dat);
void	PrintString(unsigned char code *puts);
void  	delay_ms(unsigned char ms);
uchar	GetAdc8(uchar channel);	//channel = 0~7


void TX_ADC(uchar chn, uchar adc)
{
	Tx1Send('A');
	Tx1Send('D');
	Tx1Send(chn+'0');
	Tx1Send('=');
	Tx1Send(adc / 100 + '0');
	Tx1Send(adc % 100 / 10 + '0');
	Tx1Send(adc % 10 + '0');
	Tx1Send(0x0d);
	Tx1Send(0x0a);
}

/********************* ??? *************************/
void main(void)
{
	uint	j;

	PrintString("****** STC12C5204AD??ADC?? 2011-02-27 ******\r\n");	//?????????????

	P1ASF = 1 << ADC_CH0;			//12C5204AD??????(AD)??
	ADC_CONTR = ADC_360T | ADC_ON;

	while(1)
	{
		delay_ms(250);		//1???1?
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		
		GetAdc8(0);			// P1.0 ADC, ??
		j = GetAdc8(0);		// P1.0 ADC
		TX_ADC(0,j);

		Tx1Send(0x0d);
		Tx1Send(0x0a);
	}
}

/********************* ???ADC?? *******************/
uchar	GetAdc8(uchar channel)	//channel = 0~7
{
	uchar	i;

	ADC_RES = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | channel; 

	for(i=0; i<250; i++)		//13T/loop, 40*13=520T=23.5us @ 22.1184M
	{
		if(ADC_CONTR & ADC_FLAG)
		{
			ADC_CONTR &= ~ADC_FLAG;
			return	ADC_RES;
		}
	}while(--i);
	return	0;	//??
}

//========================================================================
// ??: void  delay_ms(unsigned char ms)
// ??: ?????
// ??: ms,????ms?.
// ??: none.
// ??: VER1.0
// ??: 2010-12-15
// ??: 
//========================================================================
void  delay_ms(unsigned char ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 14000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}


/********************** ????????************************/

void	BitTime(void)	//?????
{
	uint i;
	i = ((MAIN_Fosc / 100) * 104) / 140000L - 1;		//???????????
	while(--i);
}

//??????
void	Tx1Send(uchar dat)		//9600,N,8,1		??????
{
	uchar	i;
	EA = 0;
	P_TXD1 = 0;
	BitTime();
	for(i=0; i<8; i++)
	{
		if(dat & 1)		P_TXD1 = 1;
		else			P_TXD1 = 0;
		dat >>= 1;
		BitTime();
	}
	P_TXD1 = 1;
	EA = 1;
	BitTime();
	BitTime();
}

void PrintString(unsigned char code *puts)		//???????
{
    for (; *puts != 0;	puts++)  Tx1Send(*puts); 	//?????0??
}