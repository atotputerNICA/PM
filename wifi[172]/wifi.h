#ifndef WIFI_H
#define WIFI_H

#include <avr/io.h>                    /* Include AVR std. library file */
#include <util/delay.h>                /* Include Delay header file */
#include <stdbool.h>                /* Include standard boolean library */
#include <string.h>                    /* Include string library */
#include <stdio.h>                    /* Include standard IO library */
#include <stdlib.h>                    /* Include standard library */
#include <avr/interrupt.h>            /* Include avr interrupt header file */
#include "USART_RS232_H_file.h"        /* Include USART header file */

#define SREG    _SFR_IO8(0x3F)

#define DEFAULT_BUFFER_SIZE		160
#define DEFAULT_TIMEOUT			10000

/* Connection Mode */
#define SINGLE				0
#define MULTIPLE			1

/* Application Mode */
#define NORMAL				0
#define TRANSPERANT			1

/* Application Mode */
#define STATION				   1
#define ACCESSPOINT			 2
#define BOTH_STATION_AND_ACCESPOINT	3

/* Select Demo */
//#define RECEIVE_DEMO			/* Define RECEIVE demo */
#define SEND_DEMO			/* Define SEND demo */

/* Define Required fields shown below */
#define DOMAIN            "api.thingspeak.com"
#define PORT				      "80"
#define API_WRITE_KEY			"S4UL2UB628VWEKJS"
#define CHANNEL_ID			  "503858"

// #define SSID				      "atotputerNICA"
// #define PASSWORD		    	"atotputerNICA"
#define SSID				      "Summertime"
#define PASSWORD		    	"vreauvara"

enum ESP8266_RESPONSE_STATUS{
	ESP8266_RESPONSE_WAITING,
	ESP8266_RESPONSE_FINISHED,
	ESP8266_RESPONSE_TIMEOUT,
	ESP8266_RESPONSE_BUFFER_FULL,
	ESP8266_RESPONSE_STARTING,
	ESP8266_RESPONSE_ERROR
};

enum ESP8266_CONNECT_STATUS {
	ESP8266_CONNECTED_TO_AP,
	ESP8266_CREATED_TRANSMISSION,
	ESP8266_TRANSMISSION_DISCONNECTED,
	ESP8266_NOT_CONNECTED_TO_AP,
	ESP8266_CONNECT_UNKNOWN_ERROR
};

enum ESP8266_JOINAP_STATUS {
	ESP8266_WIFI_CONNECTED,
	ESP8266_CONNECTION_TIMEOUT,
	ESP8266_WRONG_PASSWORD,
	ESP8266_NOT_FOUND_TARGET_AP,
	ESP8266_CONNECTION_FAILED,
	ESP8266_JOIN_UNKNOWN_ERROR
};

void wifi_init();
void wifi_send(char* buff);

#endif //WIFI_H
