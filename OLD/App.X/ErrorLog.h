/*
 * File:   ErrorLog.h
 * Author: Steve
 *
 * Created on November 8, 2017, 6:01 PM
 */

#ifndef ERRORLOG_H
#define	ERRORLOG_H

#define MAX_ERROR_LOG   20

typedef struct ErrorLog {
    uint16_t timestamp;
    uint8_t errorcode;
} ERRORLOG_t;

enum ErrorCodes_enum {
    NULL_ERROR = 0x00,
    MCU_INIT,
    BL_INIT,
    USB_INIT
};

#endif	/* ERRORLOG_H */
