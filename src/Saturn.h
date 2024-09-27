#ifndef _SATURN_H_
#define _SATURN_H_

#define CAN_BITRATE 1000000

#include <CAN.h>
#include <FlexCAN_T4.h>

#define MIN_DGR 0
#define MAX_DGR 180

#define MIN_PULSE_WIDTH 500
#define MAX_PULSE_WIDTH 2500

class Saturn : public CanControl{
    public:
        Saturn(CanControl* _can, int dip); //setupを行う
        void init();    //bitrateを指定する基板側で1e6[Hz]に指定
        void setTargetDgree(int addr, int dgr);
        void setTargetPulseWidth(int addr, uint16_t width);
        void send();    //データを基板(mars)に送信する
        
    private:
        CanControl* can;
        int dip;
        bool is_motor[4] = {};
        uint16_t width[4] = {};
};

#endif