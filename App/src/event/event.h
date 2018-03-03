/*
 * event.h
 *
 * Created: 2/28/2018 9:00:49 PM
 *  Author: Steve
 */ 


#ifndef EVENT_H_
#define EVENT_H_

#define MAX_TASK_EVENT_DATA_LENGTH 256
typedef struct
{
	uint16_t taskEventId;
	uint16_t len;
	uint8_t data[MAX_TASK_EVENT_DATA_LENGTH];
	TaskHandle_t senderTaskId;
} TaskMsg_t;

enum Task_event_ID_UI
{
	EVENT_UI_BLE_OFF = 0x00,
	EVENT_UI_BLE_SOLID,
	EVENT_UI_BLE_SLOW_FLASH,
	EVENT_UI_BLE_FAST_FLASH,
	EVENT_UI_MCU_OFF,
	EVENT_UI_MCU_SOLID,
	EVENT_UI_MCU_SLOW_FLASH,
	EVENT_UI_MCU_FAST_FLASH
};



#endif /* EVENT_H_ */