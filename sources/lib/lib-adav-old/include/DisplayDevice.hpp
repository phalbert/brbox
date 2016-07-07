#ifndef __DISPLAY_DEVICE_H_
#define __DISPLAY_DEVICE_H_
#include <iostream>
#include "ADCommon.hpp"
#include <stdint.h>
#include "I2CBusAccess.h"
//#include "DispsrvJsonDef.h"
using namespace std;
//important: keep enum DISPLAY_LINE and EJSON_DISPSRV_LINE same
typedef enum DISPLAY_LINE_T
{
	DISPLAY_LINE_1,
	DISPLAY_LINE_2,
	DISPLAY_LINE_3,
	DISPLAY_LINE_4,
	DISPLAY_LINE_FULL,
	DISPLAY_LINE_UNKNOWN,
	DISPLAY_LINE_NONE
}DISPLAY_LINE;
typedef enum TEXT_ALIGNMENT_T
{
	TEXT_ALIGNMENT_LEFT,
	TEXT_ALIGNMENT_RIGHT,
	TEXT_ALIGNMENT_CENTER,
	TEXT_ALIGNMENT_UNKNOWN,
	TEXT_ALIGNMENT_NONE
}TEXT_ALIGNMENT;
typedef enum ADLIB_DISPLAY_TYPE_T
{
	ADLIB_DISPLAY_TYPE_SSD1306_128x32,
	ADLIB_DISPLAY_TYPE_SSD1306_128x64,
	ADLIB_DISPLAY_TYPE_SSD1306_128x32_PI,//pi specific library access(to be removed later)
	ADLIB_DISPLAY_TYPE_SSD1306_128x64_PI,//pi specific library access(to be removed later)
	ADLIB_DISPLAY_TYPE_1602_DUAL_PCF,//adav developped board using two pcf8574
	ADLIB_DISPLAY_TYPE_1602_PCF,//standard converter board sold on ebay
	ADLIB_DISPLAY_TYPE_UNKNOWN,
	ADLIB_DISPLAY_TYPE_NONE
}ADLIB_DISPLAY_TYPE;
#define ADLIB_DISPLAY_TYPE_TABL  {"SSD1306_128x32","SSD1306_128x64","SSD1306_128x32_PI","SSD1306_128x64_PI",\
				  "DISPLAY_TYPE_1602_DUAL_PCF","DISPLAY_TYPE_1602_PCF","unknown","none","\0"}

class DisplayDevice : public I2CBusAccess
{
public:
	DisplayDevice(std::string devnode);
	~DisplayDevice();
	virtual RPC_SRV_RESULT init_display()=0;
	virtual RPC_SRV_RESULT clear_display()=0;
	virtual RPC_SRV_RESULT print_line(char* msg,DISPLAY_LINE line=DISPLAY_LINE_1,TEXT_ALIGNMENT align=TEXT_ALIGNMENT_CENTER)=0;
	//RPC_SRV_RESULT init_display();
	//RPC_SRV_RESULT clear_display();
	//RPC_SRV_RESULT print_line(int line, char* msg);
};
#endif