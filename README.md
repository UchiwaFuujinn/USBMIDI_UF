# USBMIDI_UF

USBMIDI_UF is an Arduino library for IoTMIDI. <br>
Download this folder by ZIP and install Arduino IDE. 
It needs [USBMIDI](https://github.com/arduino-libraries/MIDIUSB) library.<br>
This library can send values or text data from Arduino to PC via MIDI.<br>
USBMIDI_UF class has following member functions.<br>
<br>

```MIDIUSB_UF.h
// Sends a MIDI message to USB
void sendMIDI(midiEventPacket_t event){ MidiUSB.sendMIDI(event); }
// Flushes TX midi channel
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
```

These messages formats are descrived on [UchiwaFuujinn System Exclusve](https://uchiwafuujinn.github.io/systemexclusive/uchiwa_sysex.html).
