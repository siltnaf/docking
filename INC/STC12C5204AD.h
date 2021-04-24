
/*************	???????????	**************/
#include	"reg51.H"
#define	uchar	unsigned char
#define uint	unsigned int
/******************************************/

sfr P1ASF     = 0x9D;	//12C5204AD/S2??????(AD?LVD)??
sfr ADC_CONTR = 0xBC;	//?AD??
sfr ADC_RES   = 0xBD;	//?AD??
sfr ADC_RESL  = 0xBE;	//?AD??

//								7       6      5       4         3      2    1    0   Reset Value
//sfr ADC_CONTR = 0xBC;		ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	//AD ??????? 
#define ADC_OFF()	ADC_CONTR = 0
#define ADC_ON		(1 << 7)
#define ADC_90T		(3 << 5)
#define ADC_180T	(2 << 5)
#define ADC_360T	(1 << 5)
#define ADC_540T	0
#define ADC_FLAG	(1 << 4)	//???0
#define ADC_START	(1 << 3)	//???0
#define ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7


