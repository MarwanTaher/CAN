#ifndef  BITWISE_H
#define BITWISE_H

#define Set_Bit(Register,Bit)        Register=Register|(1<<Bit)
#define Clear_Bit(Register,Bit)      Register=Register&(~(1<<Bit))
#define Get_Bit(Register,Bit)        ((Register>>Bit)&0x01)
#define Toggle_Bit(Register,Bit)     Register=Register ^(1<<Bit)


#endif

