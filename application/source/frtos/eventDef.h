//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef EVENTDEF_H_
#define EVENTDEF_H_

typedef enum{
    kBLUETOOTH_CONNECTED,
    kBLUETOOTH_DISCONNECTED,
    kSTART_LOGGING,
    kSTOP_LOGGING,
    kEVENT_MAX,
    kEVENT_NULL
}event_t;

#endif /* EVENTDEF_H_ */
