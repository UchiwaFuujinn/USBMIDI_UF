#include <MIDIUSB_UF.h>

void MIDIUSB_UF_::sendSysEx(uint8_t *sysex)
{
	uint8_t data[4];
	midiEventPacket_t sysex_event={0,0,0,0};
	short sysex_size=0,ip;
	uint8_t cin;
	if(sysex[sysex_size]!=0xf0) return;
	sysex_size++;
	while(sysex[sysex_size]!=0xf7){
		if(sysex_size>=SYSEXBUFSIZE) return;
		sysex_size++;
	}

	sysex_size++;
	ip=0;
	while(sysex_size>0){
		if(sysex_size>3)      { cin=0x4; }
		else if(sysex_size==3){ cin=0x7; }
		else if(sysex_size==2){ cin=0x6; }
		else if(sysex_size==1){ cin=0x5; }
		sysex_event.header=cin;

		switch(cin){
			case 4:
			case 7:
			sysex_event.byte1=sysex[ip]; sysex_size--; ip++;
			sysex_event.byte2=sysex[ip]; sysex_size--; ip++;
			sysex_event.byte3=sysex[ip]; sysex_size--; ip++;
			break;
	 		case 6:
			sysex_event.byte1=sysex[ip]; sysex_size--; ip++;
			sysex_event.byte2=sysex[ip]; sysex_size--; ip++;
			sysex_event.byte3=0;
			break;
			case 5:
			sysex_event.byte1=sysex[ip]; sysex_size--; ip++;
			sysex_event.byte2=0;
			sysex_event.byte3=0;
			break;
		}
		sendMIDI(sysex_event);
	}
}

void MIDIUSB_UF_::UFsendASCII(char *buffer)
{
	uint8_t chsize=min(sizeof(buffer),SYSEXBUFSIZE-7);
	uint8_t i;

	m_UFBuf[0]=0xF0;
	m_UFBuf[1]=UF_ID_H;
	m_UFBuf[2]=UF_ID_M;
	m_UFBuf[3]=UF_ID_L;
	m_UFBuf[4]=m_DevNum;
	m_UFBuf[5]=UF_ASCII;

	i=0;
	while(buffer[i]!='\0'){
		m_UFBuf[6+i]=buffer[i];
		i++;
	}
	m_UFBuf[6+i]=0xF7;

	sendSysEx(m_UFBuf);
}

void MIDIUSB_UF_::UFsendINT8(uint8_t x, uint8_t sign)
{
	m_UFBuf[0]=0xF0;
	m_UFBuf[1]=UF_ID_H;
	m_UFBuf[2]=UF_ID_M;
	m_UFBuf[3]=UF_ID_L;
	m_UFBuf[4]=m_DevNum;
	m_UFBuf[5]=UF_INT8;
	m_UFBuf[6]=((x&0x80)>>7) | ((sign&0x01)<<4);
	m_UFBuf[7]=x&0x7F;
	m_UFBuf[8]=0xF7;

	sendSysEx(m_UFBuf);
}


void MIDIUSB_UF_::UFsendINT16(uint16_t x, uint8_t sign)
{
	m_UFBuf[0]=0xF0;
	m_UFBuf[1]=UF_ID_H;
	m_UFBuf[2]=UF_ID_M;
	m_UFBuf[3]=UF_ID_L;
	m_UFBuf[4]=m_DevNum;
	m_UFBuf[5]=UF_INT16;
	m_UFBuf[6]=(uint8_t)((x&0xC000)>>14) | ((sign&0x01)<<4);
	m_UFBuf[7]=(uint8_t)((x&0x3F80)>>7);
	m_UFBuf[8]=(uint8_t)(x&0x007F);
	m_UFBuf[9]=0xF7;

	sendSysEx(m_UFBuf);
}

void MIDIUSB_UF_::UFsendINT32(uint32_t x, uint8_t sign)
{
	m_UFBuf[0]=0xF0;
	m_UFBuf[1]=UF_ID_H;
	m_UFBuf[2]=UF_ID_M;
	m_UFBuf[3]=UF_ID_L;
	m_UFBuf[4]=m_DevNum;
	m_UFBuf[5]=UF_INT32;
	m_UFBuf[6]=(uint8_t)((x&0xF0000000)>>28) | ((sign&0x01)<<4);
	m_UFBuf[7]=(uint8_t)((x&0x0FE00000)>>21);
	m_UFBuf[8]=(uint8_t)((x&0x001FC000)>>14);
	m_UFBuf[9]=(uint8_t)((x&0x00003F80)>>7);
	m_UFBuf[10]=(uint8_t)(x&0x0000007F);
	m_UFBuf[11]=0xF7;

	sendSysEx(m_UFBuf);
}


void MIDIUSB_UF_::UFsendFLOAT(float fx)
{
	uint32_t *x = (uint32_t*)&fx;

	m_UFBuf[0]=0xF0;
	m_UFBuf[1]=UF_ID_H;
	m_UFBuf[2]=UF_ID_M;
	m_UFBuf[3]=UF_ID_L;
	m_UFBuf[4]=m_DevNum;
	m_UFBuf[5]=UF_FLOAT;
	m_UFBuf[6]=(uint8_t)((x[0]&0xF0000000)>>28);
	m_UFBuf[7]=(uint8_t)((x[0]&0x0FE00000)>>21);
	m_UFBuf[8]=(uint8_t)((x[0]&0x001FC000)>>14);
	m_UFBuf[9]=(uint8_t)((x[0]&0x00003F80)>>7);
	m_UFBuf[10]=(uint8_t)(x[0]&0x0000007F);
	m_UFBuf[11]=0xF7;

	sendSysEx(m_UFBuf);
}
