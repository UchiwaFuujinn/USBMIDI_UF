#include <MIDIUSB.h>

#define SYSEXBUFSIZE	128

#define UF_ID_H		0x00
#define UF_ID_M		0x48
#define UF_ID_L		0x02
#define UF_ASCII	0x01
#define UF_INT8		0x02
#define UF_INT16	0x03
#define UF_INT32	0x04
#define UF_FLOAT	0x05

#define min(a,b) ((a)<(b)?(a):(b))

class MIDIUSB_UF_
{
private:
	uint8_t m_UFBuf[SYSEXBUFSIZE]={0};
	uint8_t m_DevNum=0;

public:
	MIDIUSB_UF_(void){ }

	/// Sends a MIDI message to USB
	void sendMIDI(midiEventPacket_t event){ MidiUSB.sendMIDI(event); }
	/// Flushes TX midi channel
	void flush(void){ MidiUSB.flush(); }
	// Sends a System Exclusive Message
	void sendSysEx(uint8_t *sysex);
	// Uchiwa Fuujinn Send ASCII
	void UFsendASCII(char *buffer);
	// Uchiwa Fuujinn Send unsigned int8 ot signed int8
	void UFsendINT8(uint8_t x, uint8_t sign);
	// Uchiwa Fuujinn Send unsigned int16 ot signed int16
	void UFsendINT16(uint16_t x, uint8_t sign);
	// Uchiwa Fuujinn Send unsigned int32 ot signed int32
	void UFsendINT32(uint32_t x, uint8_t sign);
	// Uchiwa Fuujinn Send float
	void UFsendFLOAT(float fx);

};

