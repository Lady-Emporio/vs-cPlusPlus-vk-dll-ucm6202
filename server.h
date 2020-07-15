#pragma once
#include <string>
#include "clearSky.h"
#include "ComponentBase.h"
#include "AddInDefBase.h"
//pAsyncEvent = (IAddInDefBase*)
void runListen(IAddInDefBase* eventMen,std::string ip,int port,std::string user,std::string password);

bool isCanRead(int s);