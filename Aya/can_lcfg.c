
/*****************************************************************************************************
 *                                          includes section
 ****************************************************************************************************/
#include "can_cfg.h"

/* defining configuration of recieveing side */
tCANMsgObject sMsgObjectRx = {0,0, (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER),1};


/* defining configuration of sanding side */
tCANMsgObject sMsgObjectTx = {MY_ID,0,MSG_OBJ_TX_INT_ENABLE,1,NULL};




