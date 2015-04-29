#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SysmgrJsonDef.h"
#include "NetRpc.h"
#include "ADJsonRpcMgr.hpp"
#include "MyCmdline.h"
#include "SrcControlVersion.h"
#include "ADTimer.hpp"

using namespace std;
int main(int argc, const char* argv[])
{
	//cmdline parsing
	char ver[255];snprintf(ver,254,"%05d",SRC_CONTROL_VERSION);
	MyCmdline CmdLine(CMDLINE_HELPER_MODE_SERVER,SYSMGR_JSON_PORT_NUMBER,ver);//40000 is the portnumber
	CmdLine.parse_cmdline_arguments(argc,(char**)argv);
	if(CmdLine.is_help_printed())
		return -1;//user just requested to print the help info

	//start 100ms timer
	ADTimer AppTimer(100);//only one instance per application(or process) must exist


	//attach rpc classes to ADJsonRpcMgr
	ADJsonRpcMgr RpcMgr(SRC_CONTROL_VERSION); //main rpc handler

	NetRpc MacGet  (SYSMGR_RPC_MAC_ADDR_GET ,EJSON_SYSMGR_RPC_GET_MAC_ADDR);  //network related rpc handler class
	NetRpc MacSet  (SYSMGR_RPC_MAC_ADDR_SET ,EJSON_SYSMGR_RPC_SET_MAC_ADDR);  //network related rpc handler class
	NetRpc Ethcount(SYSMGR_RPC_ETH_COUNT_GET,EJSON_SYSMGR_RPC_GET_ETH_COUNT); //network related rpc handler class
	NetRpc Ethname (SYSMGR_RPC_ETH_NAME_GET ,EJSON_SYSMGR_RPC_GET_ETH_NAME);  //network related rpc handler class

	RpcMgr.AttachRpc(&MacGet);
	RpcMgr.AttachRpc(&MacSet);
	RpcMgr.AttachRpc(&Ethcount);
	RpcMgr.AttachRpc(&Ethname);

	//start listening for rpc-commands
	RpcMgr.AttachHeartBeat(&AppTimer);//attach 100ms heartbeat to ADJsonRpcMgr
	RpcMgr.SupportShutdownRpc(false);//this is a system-manager, needs to be alive all the time, hence dont support shutdown via rpc
	RpcMgr.Start(CmdLine.get_port_number(),CmdLine.get_socket_log(),CmdLine.get_emulation_mode());
	//server is ready to serve rpc's
	RpcMgr.SetServiceReadyFlag(EJSON_RPCGMGR_READY_STATE_READY);


	//wait for sigkill or sigterm signal
	AppTimer.wait_for_exit_signal();//loop till KILL or TERM signal is received
	AppTimer.stop_timer();//stop sending heart-beats to other objects
	return 0;
}
