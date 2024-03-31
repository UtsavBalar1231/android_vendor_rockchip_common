/* © 2019 Silicon Laboratories Inc. */
#ifndef _ZWAVE_CONTROLLER_NETWORK_INFO_STORAGE_H
#define _ZWAVE_CONTROLLER_NETWORK_INFO_STORAGE_H

#include <stdint.h>
#include "ZW_nodemask_api.h"

// ---------------------------------------------------------------------------
// ZWave/API/config_lib.h
// ---------------------------------------------------------------------------

#define ZW_VERSION_MAJOR 7
#define ZW_VERSION_MINOR 11
#define ZW_VERSION_PATCH 0

// ---------------------------------------------------------------------------
// ZWave/API/ZW_controller_api.h
// ---------------------------------------------------------------------------

/* Defines for ZW_GetControllerCapabilities */
#define CONTROLLER_IS_SECONDARY                 0x01
#define CONTROLLER_ON_OTHER_NETWORK             0x02
#define CONTROLLER_NODEID_SERVER_PRESENT        0x04
#define CONTROLLER_IS_REAL_PRIMARY              0x08
#define CONTROLLER_IS_SUC                       0x10
#define NO_NODES_INCUDED                        0x20

// ---------------------------------------------------------------------------
// ZWave/ZW_transport.h
// ---------------------------------------------------------------------------

/* Listening in nodeinfo capabilitity */
#define ZWAVE_NODEINFO_LISTENING_SUPPORT         0x80

/* Optional Functionality bit in nodeinfo security field */
#define ZWAVE_NODEINFO_OPTIONAL_FUNC             0x80

// ---------------------------------------------------------------------------
// ZWave/ZW_controller_network_info_storage.h
// ---------------------------------------------------------------------------

#define SUC_UPDATE_NODEPARM_MAX  20
#define SUC_MAX_UPDATES          64

typedef struct _ex_nvm_nodeinfo_
{
  uint8_t capability;       /* Network capabilities */
  uint8_t security;         /* Network security */
  uint8_t reserved;
  uint8_t generic;          /* Generic Device Type */
  uint8_t specific;         /* Specific Device Type */
} EX_NVM_NODEINFO;

typedef struct _suc_update_entry_struct_
{
  uint8_t      NodeID;
  uint8_t      changeType;
  uint8_t      nodeInfo[SUC_UPDATE_NODEPARM_MAX];
} SUC_UPDATE_ENTRY_STRUCT;

typedef struct _routecache_line_
{
  uint8_t repeaterList[MAX_REPEATERS];
  uint8_t routecacheLineConfSize;
} ROUTECACHE_LINE;


// ---------------------------------------------------------------------------
// ZWave/ZW_controller_network_info_storage.c
// ---------------------------------------------------------------------------

typedef struct
{
  EX_NVM_NODEINFO NodeInfo;
  NODE_MASK_TYPE neighboursInfo;
  uint8_t ControllerSucUpdateIndex;
} SNodeInfo;

#define FILE_ID_NODEINFO                (0x50100)
#define FILE_SIZE_NODEINFO              (sizeof(SNodeInfo))

typedef struct
{
  ROUTECACHE_LINE  routeCache;
  ROUTECACHE_LINE  routeCacheNlwrSr;
} SNodeRouteCache;


#define FILE_ID_NODEROUTECAHE           (0x50400)
#define FILE_SIZE_NODEROUTECAHE         (sizeof(SNodeRouteCache))


#define FILE_ID_ZW_VERSION              (0x50000)
#define FILE_SIZE_ZW_VERSION            (sizeof(uint32_t))

typedef struct
{
  uint8_t                          PreferredRepeater[MAX_NODEMASK_LENGTH];
} SPreferredRepeaters;

#define FILE_ID_PREFERREDREPEATERS      (0x50002)
#define FILE_SIZE_PREFERREDREPEATERS    (sizeof(SPreferredRepeaters))

typedef struct
{
  SUC_UPDATE_ENTRY_STRUCT       aSucNodeList[SUC_MAX_UPDATES];
} SSucNodeList;

#define FILE_ID_SUCNODELIST             (0x50003)
#define FILE_SIZE_SUCNODELIST           (sizeof(SSucNodeList))

typedef struct
{
  uint8_t                       HomeID[HOMEID_LENGTH];
  uint8_t                       NodeID;
  uint8_t                       LastUsedNodeId;
  uint8_t                       StaticControllerNodeId;
  uint8_t                       SucLastIndex;
  uint8_t                       ControllerConfiguration;
  uint8_t                       SucAwarenessPushNeeded;
  uint8_t                       MaxNodeId;
  uint8_t                       ReservedId;
  uint8_t                       SystemState;
} SControllerInfo;

#define FILE_ID_CONTROLLERINFO            (0x50004)
#define FILE_SIZE_CONTROLLERINFO          (sizeof(SControllerInfo))

#define FILE_ID_NODE_STORAGE_EXIST        (0x50005)
#define FILE_SIZE_NODE_STORAGE_EXIST      (sizeof(NODE_MASK_TYPE))

#define FILE_ID_APP_ROUTE_LOCK_FLAG       (0x50006)
#define FILE_SIZE_APP_ROUTE_LOCK_FLAG     (sizeof(NODE_MASK_TYPE))

#define FILE_ID_ROUTE_SLAVE_SUC_FLAG      (0x50007)
#define FILE_SIZE_ROUTE_SLAVE_SUC_FLAG    (sizeof(NODE_MASK_TYPE))

#define FILE_ID_SUC_PENDING_UPDATE_FLAG   (0x50008)
#define FILE_SIZE_SUC_PENDING_UPDATE_FLAG (sizeof(NODE_MASK_TYPE))

#define FILE_ID_BRIDGE_NODE_FLAG          (0x50009)
#define FILE_SIZE_BRIDGE_NODE_FLAG        (sizeof(NODE_MASK_TYPE))

#define FILE_ID_PENDING_DISCOVERY_FLAG    (0x5000A)
#define FILE_SIZE_PENDING_DISCOVERY_FLAG  (sizeof(NODE_MASK_TYPE))

#define FILE_ID_NODE_ROUTECACHE_EXIST     (0x5000B)
#define FILE_SIZE_NODE_ROUTECACHE_EXIST   (sizeof(NODE_MASK_TYPE))

/*
Protocol S2 not used for controllers (gateway links to libs2 instead)
CtrlStorageInit() will create empty copies of all S2 files
Here we hardcode sizes to 0 to avoid pulling in S2 struct definition
*/

#define FILE_ID_S2_KEYS                   (0x50010)
#define FILE_SIZE_S2_KEYS                 0 // (sizeof(Ss2_keys))

#define FILE_ID_S2_KEYCLASSES_ASSIGNED    (0x50011)
#define FILE_SIZE_S2_KEYCLASSES_ASSIGNED  0 // (sizeof(Ss2_keyclassesAssigned))

#define FILE_ID_S2_MPAN                   (0x50012)
#define FILE_SIZE_S2_MPAN                 0 // (sizeof(mpan_file))

#define FILE_ID_S2_SPAN                   (0x50013)
#define FILE_SIZE_S2_SPAN                 0 // (sizeof(span_file))

/* In version 1 of the nvm format (initial nvm format was version 0), the route caches and nodeinfos are grouped in four/eight elements pr file.*/
#define NODEINFOS_PER_FILE 4
#define FILE_ID_NODEINFO_V1                (0x50200)
#define FILE_SIZE_NODEINFO_V1              (sizeof(SNodeInfo) * NODEINFOS_PER_FILE)

#define NODEROUTECACHES_PER_FILE 8
#define FILE_ID_NODEROUTECAHE_V1           (0x51400)
#define FILE_SIZE_NODEROUTECAHE_V1         (sizeof(SNodeRouteCache) * NODEROUTECACHES_PER_FILE)


#endif // _ZWAVE_CONTROLLER_NETWORK_INFO_STORAGE_H
