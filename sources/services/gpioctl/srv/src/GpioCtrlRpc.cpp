#include "GpioCtrlRpc.h"
#include "RaspiIo.h"
/* ------------------------------------------------------------------------- */
GpioCtrlRpc:: GpioCtrlRpc(std::string rpcName,int myIndex,bool emu, bool log,GPIOCTL_CMN_DATA_CACHE *pData):ADJsonRpcMgrConsumer(rpcName,myIndex,emu,log)
{
	pDataCache=pData;	
}
/* ------------------------------------------------------------------------- */
GpioCtrlRpc::~ GpioCtrlRpc()
{
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::MapJsonToBinary(JsonDataCommObj* pReq,int index)
{
	EJSON_GPIOCTL_RPC_TYPES command =(EJSON_GPIOCTL_RPC_TYPES)index;
	switch(command)
	{
		case EJSON_GPIOCTL_RPC_IO_GET :return json_to_bin_gpio_get(pReq);
		case EJSON_GPIOCTL_RPC_IO_SET :return json_to_bin_gpio_set(pReq);
		default:break;
	}
	return -1;//0;
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::MapBinaryToJson(JsonDataCommObj* pReq,int index)
{
	EJSON_GPIOCTL_RPC_TYPES command =(EJSON_GPIOCTL_RPC_TYPES)index;
	switch(command)
	{
		case EJSON_GPIOCTL_RPC_IO_GET :return bin_to_json_gpio_get(pReq);
		case EJSON_GPIOCTL_RPC_IO_SET :return bin_to_json_gpio_set(pReq);
		default:break;
	}
	return -1;
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::ProcessWork(JsonDataCommObj* pReq,int index)
{
	EJSON_GPIOCTL_RPC_TYPES command =(EJSON_GPIOCTL_RPC_TYPES)index;
	switch(command)
	{
		case EJSON_GPIOCTL_RPC_IO_GET :return process_gpio_get(pReq);
		case EJSON_GPIOCTL_RPC_IO_SET :return process_gpio_set(pReq);
		default:break;
	}
	return 0;
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::ProcessWorkAsync(unsigned char* pWorkData)
{
	return 0;
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::json_to_bin_gpio_get(JsonDataCommObj* pReq)
{
	GPIOCTL_IO_ACCESS_PACKET* pPanelCmdObj=NULL;
	PREPARE_JSON_REQUEST(RPC_SRV_REQ,GPIOCTL_IO_ACCESS_PACKET,RPC_SRV_ACT_READ,EJSON_GPIOCTL_RPC_IO_GET);
	JSON_STRING_TO_INT(GPIOCTL_RPC_IO_ADDR_ARG,pPanelCmdObj->addr);
	return 0;
}
int GpioCtrlRpc::bin_to_json_gpio_get(JsonDataCommObj* pReq)
{
	PREPARE_JSON_RESP_INT(RPC_SRV_REQ,GPIOCTL_IO_ACCESS_PACKET,GPIOCTL_RPC_IO_DATA_ARG,data);
	return 0;
}
int GpioCtrlRpc::process_gpio_get(JsonDataCommObj* pReq)
{
	RaspiIo Raspi;
	RPC_SRV_REQ *pPanelReq=NULL;
	pPanelReq=(RPC_SRV_REQ *)pReq->pDataObj;
	GPIOCTL_IO_ACCESS_PACKET* pPacket;
	pPacket=(GPIOCTL_IO_ACCESS_PACKET*)pPanelReq->dataRef;

	//pPacket->data=pDataCache->tmpData;
	//pPanelReq->result=RPC_SRV_RESULT_SUCCESS;
	pPanelReq->result=Raspi.ReadGPIO (pPacket->addr,pPacket->data);
	//RPC_SRV_RESULT RaspiIo::WriteGPIO(unsigned int addr,unsigned int data)



	//set debug logging flag
	//ImgId.logflag=get_debug_log_flag();//get_debug_log_flag() is a function f parent class ADJsonRpcMgrConsumer
	//pPanelReq->result=ImgId.IdentifyPattern(pPacket->pattern_type,pDataCache->StrImgIdDebugFile);
	return 0;
}
/* ------------------------------------------------------------------------- */
int GpioCtrlRpc::json_to_bin_gpio_set(JsonDataCommObj* pReq)
{
	GPIOCTL_IO_ACCESS_PACKET* pPanelCmdObj=NULL;
	PREPARE_JSON_REQUEST(RPC_SRV_REQ,GPIOCTL_IO_ACCESS_PACKET,RPC_SRV_ACT_WRITE,EJSON_GPIOCTL_RPC_IO_SET);
	JSON_STRING_TO_INT(GPIOCTL_RPC_IO_ADDR_ARG,pPanelCmdObj->addr);
	JSON_STRING_TO_INT(GPIOCTL_RPC_IO_DATA_ARG,pPanelCmdObj->data);
	return 0;
}
int GpioCtrlRpc::bin_to_json_gpio_set(JsonDataCommObj* pReq)
{
	PREPARE_JSON_RESP(RPC_SRV_REQ,GPIOCTL_IO_ACCESS_PACKET);
	return 0;
}
int GpioCtrlRpc::process_gpio_set(JsonDataCommObj* pReq)
{
	RPC_SRV_REQ *pPanelReq=NULL;
	pPanelReq=(RPC_SRV_REQ *)pReq->pDataObj;
	GPIOCTL_IO_ACCESS_PACKET* pPacket;
	pPacket=(GPIOCTL_IO_ACCESS_PACKET*)pPanelReq->dataRef;

	RaspiIo Raspi;
	pPanelReq->result=Raspi.WriteGPIO(pPacket->addr,pPacket->data);
	//pDataCache->tmpData=pPacket->data;
	//pPanelReq->result=RPC_SRV_RESULT_SUCCESS;
	return 0;
}
/* ------------------------------------------------------------------------- */


