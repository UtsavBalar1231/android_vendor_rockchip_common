/* © 2019 Silicon Laboratories Inc. */

#include <stdio.h>
#include <port.h>

#include "Serialapi.h"

#include "zgw_data.h"
#include "zgw_restore_cfg.h"
#include "zgwr_serial.h"

extern uint16_t MyNodeID;
extern uint32_t homeID;

const struct SerialAPI_Callbacks callbacks =
   {
      0, //ApplicationCommandHandlerSerial,
      0, //ApplicationNodeInformation,
      0, //ApplicationControllerUpdate,
      0,
      0, //ApplicationInitSW,
      0,
      0,
      0, //ApplicationCommandHandlerSerial,
      0 //SerialAPIStarted
  };


int zgwr_serial_init(void) {
   const char* port;
   int res = 0;

   port = serial_port_get();
   printf("opening serial port: %s\n", port);

   res =  SerialAPI_Init(port, &callbacks);
   return res;
}

void zgwr_serial_close(void)
{
   SerialClose();
}

/**
 * Read required zgw-data from the newly restored chip.
 *
 * Open serial if and read protocol data for the controller and the
 * nodes and insert this into the internal data structure of restore.
*/
int zgw_restore_serial_data_read(zw_controller_t **ctrl) {
   uint8_t ver, capabilities, len, chip_type, chip_version;
   nodemask_t nodelist = {0};
   int i;
   uint8_t SUCid;

   /* Add the gateway */

   MemoryGetID((BYTE*) &homeID, &MyNodeID);
   SerialAPI_GetInitData(&ver, &capabilities, &len, nodelist, &chip_type, &chip_version);
   SUCid= ZW_GetSUCNodeID();

   *ctrl = zw_controller_init(SUCid);

   NODEINFO tmp;
   for (i = 1; i <= ZW_MAX_NODES; i++)
   {
      if (BIT8_TST((i-1),nodelist))
      {
         ZW_GetNodeProtocolInfo(i, &tmp);
         zw_node_data_t* gw_node_data = calloc(1,sizeof(zw_node_data_t));
         gw_node_data->node_id = i;
         gw_node_data->capability = tmp.capability;
         gw_node_data->security = tmp.security;
         gw_node_data->neighbors = NULL;
         gw_node_data->node_type.basic = tmp.nodeType.basic;
         gw_node_data->node_type.generic = tmp.nodeType.generic;
         gw_node_data->node_type.specific = tmp.nodeType.specific;

         zw_controller_add_node(*ctrl, i, gw_node_data);
      }
   }
   return 0;
}
