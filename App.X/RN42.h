#ifndef RN42_H
#define RN42_H

/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/

/************ DEFINITIONS ***************/
#define CARRIAGE_RETURN 0x0D
/************ ACTION COMMANDS ***********/
#define ACTION_ENTER_COMMAND_MODE "$$$"
#define ACTION_EXIT_COMMAND_MODE "---"
#define ACTION_TOGGLE_LOCAL_ECHO "+"
#define ACTION_CONNECT_STORED_REMOTE "C"
#define ACTION_CONNECT_ADDRESS(X) return("C,"+X)
#define ACTION_CONNECT_FAST_MODE(X) return("CF,"+X)
#define ACTION_CONNECT_FAST_INQUIRY "CFI"
#define ACTION_CONNECT_FAST "CFR"
//TO-DO #define CT
#define ACTION_ENTER_FAST "F,1"
#define ACTION_DISPLAY_COMMANDS "H"
#define ACTION_INQUIRY_SCAN(X,Y) return("I,"+X+Y)
#define ACTION_INQUIRY_SCAN_NONAME(X,Y) return("IN,"+X+Y)
#define ACTION_INQUIRY_RSSI "IQ"
#define ACTION_DISCONNECT_PAIR "K,"
#define ACTION_LINK_QUALITY "L"
#define ACTION_REMOTE_SIGNAL_STAT "M"
#define ACTION_FORCE_REBOOT "R,1"
#define ACTION_GET_FW_VER "V"
#define ACTION_ENABLE_DISCOVERY "W"
#define ACTION_ENTER_DEEP_SLEEP "Z"
/************ GET COMMANDS **************/
#define GET_BASIC_SETTINGS "D"
#define GET_EXT_SETTINGS "E"
#define GET_BL_ADDRESS "GF"
#define GET_CONNECTION_STATUS "GK"
#define GET_REMOTE_ADDRESS "GR"
#define GET_GPIO_STATE "G&"
#define GET_SETTING(X) return("G"+X)
/************ SET COMMANDS **************/
#define SET_7BITMODE_ENABLE "S7,1"
#define SET_7BITMODE_DISABLE "S7,0"
#define SET_AUTHENTICATION_MODE(M) return("SA,"+M)
#define SET_BREAK(B) return("SB,"+B)
#define SET_SERVICE_CLASS(SC) return("SC,"+SC)
#define SET_CLASS_OF_DEVICE(COD) return("SD,"+COD)
//TO-DO #define SE
#define SET_FACTORY_DEFAULTS "SF,1"
//TO-DO #define SH
#define SET_INQUIRY_SCAN(I) return("SI,"+I)
#define SET_PAGE_SCAN (I) return("SJ,"+I)
#define SET_UART_PARITY(P) return("SL,"+P)
#define SET_MODE(M) return("SM,"+M)
#define SET_DEVICE_NAME(N) return("SN,"+N)
#define SET_EXTENDED_STATUS(N) return("SO,"+N)
#define SET_PIN_CODE(P) return("SP,"+P)
//TO-DO #define SQ
#define SET_REMOTE_ADDRESS(A) return("SR,"+A)
#define SET_SERVICE_NAME(S) return("SS,"+S)
#define SET_REMOTE_CONFIG_TIMER(T) return("ST,"+T)
#define SET_UART_BAUD_RATE(R) return("SU,"+R)
#define SET_LOW_POWER_SNIFF(L) return("SW,"+L)
#define SET_DEVICE_BONDING(X) return("SX,"+X)
#define SET_TRANSMIT_POWER(X) return("SY,"+X)
#define SET_CUSTOM_BAUD_RATE(X) return("SZ,"+X)
//TO-DO #define S~
#define SET_SERIALIZED_DEVICE_NAME(X) return("S-,"+X)
//TO-DO #define S?
#define SET_LOW_POWER_CONNECT(X) return("S|,"+X)

/************** TYPEDEFS ****************/
/********* FUNCTION PROTOTYPES **********/
/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* RN42_H */
