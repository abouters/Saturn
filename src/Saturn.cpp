#include "Saturn.h"
#include <Arduino.h>

Saturn::Saturn(CanControl* _canN, int dip){
    can = _canN;
    this->dip = dip;
}

void Saturn::init(){
	can->init(CAN_BITRATE);
}

void Saturn::setTargetDgree(int addr, int dgr){
    is_motor[addr-1] = true;
    width[addr-1] = map(dgr, MIN_DGR, MAX_DGR, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

void Saturn::setTargetPulseWidth(int addr, uint16_t width){
    is_motor[addr-1] = true;
    this->width[addr-1] = width;
}

void Saturn::send(){
    CAN_message_t msg;
    msg.id = 0x500 + dip;
    msg.len = 8;
    for(int i=0; i<4; i++){
        msg.buf[i*2] = width[i] & 0xff;
        msg.buf[i*2 + 1] = (width[i] >> 8) + (is_motor[i] << 7);
    }
    can->CANMsgWrite(msg);
}