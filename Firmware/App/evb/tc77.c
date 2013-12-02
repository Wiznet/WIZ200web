
#include "tc77.h"


void tc77_init(void)
{
	TC77_READ_INIT();
//	TC77_CLK_INIT();
//	TC77_CLK_ON();

	TC77_CS_INIT();
	TC77_CS_ON();
}

unsigned char tc77_read(unsigned int* temp)
{
#if	TC77_SPI_SW
	unsigned int read_value = 0;
	unsigned char i;

	
	TC77_CS_OFF();
	
	for(i=0;i<16;i++)
	{
		TC77_CLK_ON();
		read_value <<= 1;
		if(TC77_READ())read_value |= 1;
		
		TC77_CLK_OFF();
	}
	TC77_CS_ON();
	
	*temp= (read_value>>3)&0x3FF;
	
	return ((read_value&0x8000)?1:0);
#else
	unsigned int read_value = 0;
	
	TC77_CS_OFF();
	
	read_value = (TC77_READ()<<8) &0xFF00;
	read_value |= TC77_READ();
	
	TC77_CS_ON();
	
	*temp= (read_value>>3)&0x3FF;
	
	return ((read_value&0x8000)?1:0);
#endif	
}


