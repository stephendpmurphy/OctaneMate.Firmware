//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#ifndef BLUETOOTH_APP_COMMANDS
#define	BLUETOOTH_APP_COMMANDS

/*-------------- DEFINITIONS -------------------------------------------------*/
/********************************************
* Read Local Information (OPCODE - 0x01)
*********************************************/
#define BM71_FIRMWARE_VERSION_OFFSET                            0x06
#define BM71_FIRMWARE_VERSION_LEN                               0x0C
#define BM71_BLUETOOTH_ADDRESS_OFFSET                           0x0A
#define BM71_BLUETOOTH_ADDRESS_LEN                              0x17
#define BM71_SILICON_ID_OFFSET                                  0x10
#define BM71_SILICON_ID_LEN                                     0x01

/********************************************
* Read BM7 Status (OPCODE - 0x03)
*********************************************/
#define BM71_STATUS_OFFSET                                      0x04
#define BM71_STATUS_LEN                                         0x01

/********************************************
* Read Device Name (OPCODE - 0x07)
*********************************************/
#define BM71_READ_DEVICE_NAME_OFFSET							0x06
#define BM71_MAX_DEVICE_NAME_LEN								0x20

/********************************************
* Write Device Name (OPCODE - 0x08)
*********************************************/
#define BM71_WRITE_DEVICE_NAME_OFFSET							0x05

/********************************************
* Set Advertising Enable (OPCODE - 0x1C)
*********************************************/
#define BM71_SET_ADVERTISING_EN_OFFSET							0x04

/*-------------- TYPEDEFS ----------------------------------------------------*/
typedef enum{
	READ_LOCAL_INFORMATION =									0x01,
	RESET,
	READ_STATUS,
	READ_ADC_VALUE,
	INTO_SHUTDOWN_MODE,
	READ_DEVICE_NAME =											0x07,
	WRITE_DEVICE_NAME,
	ERASE_ALL_PAIRED_DEVICE_INFO,
	READ_PAIRING_MODE_SETTING,
	WRITE_PAIRING_MODE_SETTING,
	READ_ALL_PAIRED_DEVICE_INFO,
	DELETE_PAIRED_DEVICE,
	DIGITAL_IO_CONTROL,
	PWM_CONTROL,
	READ_RSSI_VALUE =											0x10,
	WRITE_ADVERTISING_DATA,
	WRITE_SCAN_RESPONSE_DATA,
	SET_ADVERTISING_PARAMETERS,
	SET_SCAN_PARAMETERS =										0x15,
	SET_SCAN_ENABLE,
	LE_CREATE_CONNECTION,
	LE_CREATE_CONNECTION_CANCEL,
	CONNECTION_PARAMETER_UPDATE_REQUEST,
	DISCONNECT =												0x1B,
	SET_ADVERTISING_ENABLE_DISABLE,
	READ_REMOTE_DEVICE_NAME =									0x1F,
	GATT_CLIENT_DISCOVER_ALL_PRMY_SERVICES =					0x30,
	GATT_CLIENT_DISCOVER_SPECIFIC_PMY_SERVICE_CHAR,
	READ_CHARACTERISTIC_VALUE,
	GATT_CLIENT_READ_USING_CHARACTERISTIC_UUID,
	GATT_CLIENT_WRITE_CHARACTERISTIC_VALUE,
	GATT_CLIENT_ENABLE_TRANSPARENT_UART_SERVICE,
	GATT_SERVER_SEND_CHARACTERISTIC_VALUE =						0x38,
	GATT_SERVER_UPDATE_CHARACTERISTIC_VALUE,
	GATT_SERVER_READ_LOCAL_CHARACTERISTIC_VALUE,
	GATT_SERVER_READ_ALL_LOCAL_PRIMARY_SERVICES,
	GATT_SERVER_READ_SPECIFIC_LOCAL_PRIMARY_SERVICE,
	GATT_SERVER_SEND_WRITE_RESPONSE,
	TRANSPARENT_UART_SERVICE_SEND_DATA,
	PAIRING_PASSKEY_ENTRY_RESPONSE =							0x40,
	PAIRING_USER_CONFIRM_PASSKEY_RESPONSE,
	PAIRING_PAIR_REQUEST,
	LEAVE_CONFIGURATION_MODE =									0x52,
	PAIRING_PASSKEY_ENTRY_REQUEST_EVENT =						0x60,
	PAIRING_PAIR_COMPLETE_EVENT,
	PAIRING_PASSKEY_CONFIRM_REQUEST_EVENT,
	ADVERTISING_REPORT_EVENT =									0x70,
	LE_CONNECTION_COMPLETE_EVENT,
	DISCONNECT_COMPLETE_EVENT,
	CONNECTION_PARAMETER_UPDATE_EVENT,
	COMMAND_COMPLETE_EVENT =									0x80,
	STATUS_REPORT_EVENT,
	CONFIGURE_MODE_STATUS_EVENT =								0x8F,
	DISCOVER_ALL_PRIMARY_SERVICES_EVENT =						0x90,
	DISCOVER_SPECIFIC_PRMY_SERVICE_CHAR_DECLARATION_EVENT,
	DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_EVENT,
	GATT_SERVER_CLIENT_WRITE_CHARACTERISTIC_VALUE_EVENT =		0x98,
	GATT_TRANSPARENT_RECEIVED_TRANSPARENT_DATA_EVENT_RESP =		0x9A,
} BM71_OpCode_t;

typedef enum{
	COMMAND_SUCCEEDED =											0x00,
	UNKOWN_COMMAND,
	UNKOWN_CONNECTION_ID,
	HARDWARE_FAILURE,
	AUTHENTICATION_FAILURE =									0x05,
	PIN_KEY_MISSING,
	MEMORY_CAPACITY_EXCEEDED,
	CONNECTION_TIMEOUT,
	CONNECTION_LIMIT_EXCEEDED,
	ACL_CONNECTION_ALREADY_EXISTS =								0x0B,
	COMMAND_DISALLOWED,
	CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES,
	CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS,
	CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR,
	CONNECTION_ACCEPT_TIMEOUT_EXCEEDED,
	UNSUPPORTED_FEATURE_PARAMETER_VALUE,
	INVALID_COMMAND_PARAMETERS,
	REMOTE_USER_TERMINDATED_CONNECTION,
	REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES,
	REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF,
	CONNECTION_TERMINATED_BY_LOCAL_HOST,
	PAIRING_NOT_ALLOWED =										0x18,
	UNSPECIFIED_ERROR =											0x1F,
	INSTANT_PASSED =											0x28,
	PAIRING_W_UNIT_KEY_NOT_SUPPORTED,
	INSUFFICIENT_SECURITY =										0x2F,
	CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND =		0x39,
	CONTROLLER_BUSY,
	UNACCEPTABLE_CONNECTION_INTERVAL,
	DIRECTED_ADVERTISING_TIMEOUT,
	CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE,
	CONNECTION_FAILED_TO_BE_ESTABLISHED,
	INVALID_OFFSET =											0x77,
	INVALID_HANDLE =											0x81,
	READ_NOT_PERMITTED,
	WRITE_NOT_PERMITTED,
	INVALID_PDU,
	INSUFFICIENT_AUTHENTICATION,
	REQUEST_NOT_SUPPORTED,
	INSUFFICIENT_AUTHORIZATION =								0x88,
	PREPARE_QUEUE_FULL,
	ATTRIBUTE_NOT_FOUND,
	ATTRIBUTE_NOT_LONG,
	INSUFFICIENT_ENCRYPTION_KEY_SIZE,
	INVALID_ATTRIBUTE_VALUE_LENGTH,
	UNLIKELY_ERROR,
	INSUFFICIENT_ENCRYPTION,
	UNSUPPORTED_GROUP_TYPE,
	INSUFFICIENT_RESOURCES,
	APPLICATION_DEFINDED_ERROR =								0xF0,
	UART_CHECKSUM_ERROR =										0xFF
} BM71_CommandCompleteEventParams_t;


typedef enum {
    SCANNING_MODE =                                             0x01,
    CONNECTING_MODE,
    STANDBY_MODE,
    BROADCAST_MODE =                                            0x05,
    TRANSPARENT_SERVICE_ENABLED_MODE =                          0x08,
    IDLE_MODE,
    SHUTDOWN_MODE,
    CONFIGURE_MODE,
    BLE_CONNECTED_MODE
} BM71_StatusReportEventParams_t;
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
// SOM  -  LMSB  -  LLSB  -  OP CODE  -  PARAMTER  -  CRC
const uint8_t CMD_readLocalInfo[4] = {0xAA, 0x00, 0x01, 0x01};
const uint8_t CMD_readBM71Status[4] = {0xAA, 0x00, 0x01, 0x03};
const uint8_t CMD_readDeviceName[4] = {0xAA, 0x00, 0x01, 0x07};
const uint8_t CMD_writeDeviceName[5] = {0xAA, 0x00, 0x00, 0x08, 0x00};
const uint8_t CMD_setAdvertisingEnable[5] = {0xAA, 0x00, 0x02, 0x1C, 0x00};

#endif	/* BLUETOOTH_APP_COMMANDS */
