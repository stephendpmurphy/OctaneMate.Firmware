/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef LOGGER_H
#define	LOGGER_H

/************ DEFINITIONS ***************/
#define TEN_HZ_INTERVAL 0x0064
#define TWENTY_HZ_INTERVAL 0x0032

/************** TYPEDEFS ****************/
typedef struct LOGGER {
    uint8_t LOGGER_ENABLE;
    TIMEOUT_HANDLE_t TIMEOUT_HANDLE;
} LOGGER_t;

/********* FUNCTION PROTOTYPES **********/
void InitLogger(void);
static void LogTenHz(void);
static void LogTwentyHz(void);
void EnableLogger(uint8_t);

#endif	/* LOGGER_H */
