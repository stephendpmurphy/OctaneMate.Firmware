/*
 * debug_task_API.h
 *
 * Created: 3/2/2018 7:32:28 PM
 *  Author: Steve
 */


#ifndef DEBUG_TASK_API_H_
#define DEBUG_TASK_API_H_

#include <semphr.h>

#define DEBUG_OUTPUT_ENABLED 1

#define STARTUP_PRINTLN(...) DEBUG_println(__VA_ARGS__)

#if (DEBUG_OUTPUT_ENABLED == 1)
#define DEBUG_PRINTLN(...) DEBUG_println(__VA_ARGS__)
#define BLE_DEBUG_PRINTLN(...) ((BLE_DEBUG_ENABLED == true) ? DEBUG_println(__VA_ARGS__) : DEBUG_VOID_println());
#define UI_DEBUG_PRINTLN(...) ((UI_DEBUG_ENABLED == true) ? DEBUG_println(__VA_ARGS__) : DEBUG_VOID_println());
#else
#define DEBUG_PRINTLN(...) //DO NOTHING...
#define BLE_DEBUG_PRINTLN(...) //DO NOTHING...
#define UI_DEBUG_PRINTLN(...) //DO NOTHING...
#endif


enum DEBUG_OUTPUT_TYPE {
	BLE_DEBUG_OUTPUT = 0x00,
	UI_DEBUG_OUTPUT
};

void DEBUG_initTask(void);
void DEBUG_println(const char *frmt, ...);
void DEBUG_VOID_println(void);

extern bool BLE_DEBUG_ENABLED;
extern bool UI_DEBUG_ENABLED;

#endif /* DEBUG_TASK_API_H_ */
