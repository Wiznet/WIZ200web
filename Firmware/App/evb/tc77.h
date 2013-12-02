#include "../mcu/types.h"
#include "../evb/lcd.h"

#define TC77_SPI_SW					0
//#define BM(Num)						(1<<(Num))

#define TC77_CS_INIT()				DDRB |= BM(0)  
#define TC77_CS_ON()				PORTB |= BM(0)
#define TC77_CS_OFF()				PORTB &= ~BM(0)

#define TC77_CLK_INIT()				DDRB |= BM(1)
#define TC77_CLK_ON()				PORTB |= BM(1)
#define TC77_CLK_OFF()				PORTB &= ~BM(1)

#if	TC77_SPI_SW
#define TC77_READ_INIT()			DDRB |= BM(2)
#define TC77_READ()					(PINB & BM(2))
#else
#define TC77_READ_INIT()			
#define TC77_READ()					SPI0_WriteReadByte(0)
#endif

void tc77_init(void);
unsigned char tc77_read(unsigned int* temp);
