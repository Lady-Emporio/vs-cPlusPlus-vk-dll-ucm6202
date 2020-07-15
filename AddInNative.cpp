
#include "stdafx.h"

#ifdef __linux__
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#endif

#include "clearSky.h"
#include <thread>
#include <wchar.h>
#include <string>
#include <sstream> 
#include "AddInNative.h"
#include <Windows.h>
#include <fstream>
#include <string>






static const wchar_t g_kClassNames[] = L"CAddInNative"; //|OtherClass1|OtherClass2";
 
//---------------------------------------------------------------------------//
long GetClassObject(const wchar_t* wsName, IComponentBase** pInterface)
{
	myLog("GetClassObject");
    if(!*pInterface)
    {
        *pInterface= new CAddInNative();
        return (long)*pInterface;
    }
	myLog("GetClassObject bad end");
    return 0;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf)
{
	myLog("DestroyObject");
   if(!*pIntf)
      return -1;

   delete *pIntf;
   *pIntf = 0;
   return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames()
{
	myLog("GetClassNames");
    //static WCHAR_T* names = 0;
    /*if (!names)
        ::convToShortWchar(&names, g_kClassNames);*/
	WCHAR_T* lnames = L"CAddInNative";
    return lnames;

}



void CAddInNative::beginGivesMePhoto()
{
	MessageBox(NULL, "TEST", "TEST caption", MB_OK);

}



//---------------------------------------------------------------------------//
//CAddInNative
CAddInNative::CAddInNative()
{
	myLog("CAddInNative");
}
//---------------------------------------------------------------------------//
CAddInNative::~CAddInNative()
{
	myLog("~CAddInNative");
}
//---------------------------------------------------------------------------//
bool CAddInNative::Init(void* pConnection)
{ 
	myLog("Init");
	IAddInDefBase_point = (IDispatch *)pConnection;
	pAsyncEvent = (IAddInDefBase*)pConnection;
	if (!pAsyncEvent->SetEventBufferDepth(1000)) {
		myLog("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! set size buffer 1000 error");
		if (!pAsyncEvent->SetEventBufferDepth(500)) {
			myLog("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! set size buffer 500 error");
			if (!pAsyncEvent->SetEventBufferDepth(300)) {
				myLog("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! set size buffer 300 error");
			};
		};
	};
	return true;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetInfo()
{ 
	myLog("GetInfo");
    return 2000; 
}
//---------------------------------------------------------------------------//
void CAddInNative::Done()
{
	myLog("Done");
}
//---------------------------------------------------------------------------//
bool CAddInNative::RegisterExtensionAs(WCHAR_T** wsLanguageExt)
{ 
	myLog("RegisterExtensionAs");
	wchar_t *wsExtension = L"VkATSCameraThis";
	int iActualSize = ::wcslen(wsExtension) + 1;
	WCHAR_T* dest = 0;
	if (this->memManager)
	{
		auto res=this->memManager->AllocMemory((void**)wsLanguageExt, iActualSize * sizeof(WCHAR_T));
		if (res)
			::convToShortWchar(wsLanguageExt, wsExtension, iActualSize);
		myLog("RegisterExtensionAs return 'VkATSCameraThis'");
		return true;
	}
	myLog("RegisterExtensionAs bad end");
	return false;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetNProps()
{ 
	myLog("GetNProps");
    return eLastProp;
}
//---------------------------------------------------------------------------//
long CAddInNative::FindProp(const WCHAR_T* wsPropName)
{ 
	myLog("FindProp");
    return -1;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CAddInNative::GetPropName(long lPropNum, long lPropAlias)
{ 
	myLog("GetPropName");
    return 0;
}
//---------------------------------------------------------------------------//
bool CAddInNative::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{ 
	myLog("GetPropVal");
    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::SetPropVal(const long lPropNum, tVariant* varPropVal)
{ 
	myLog("SetPropVal");
    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::IsPropReadable(const long lPropNum)
{ 
	myLog("IsPropReadable");
    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::IsPropWritable(const long lPropNum)
{
	myLog("IsPropWritable");
	return false;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetNMethods()
{ 
	myLog("GetNMethods"); 
	return eLastMethod;
}
//---------------------------------------------------------------------------//
long CAddInNative::FindMethod(const WCHAR_T* wsMethodName)
{ 
	myLog("FindMethod"); 
	wchar_t* tempString = 0;
	convFromShortWchar(&tempString, wsMethodName);
	std::wstring wstring(tempString);
	std::string methodMame(wstring.begin(), wstring.end());
	myLog("FindMethod get:"+ methodMame);
	if ("setPort" == methodMame) {
		int result = CAddInNative::Methods::setPort;
		myLog("FindMethod return:"+ std::to_string(result));
		return result;
	}
	if ("setIp" == methodMame) {
		int result = CAddInNative::Methods::setIp;
		myLog("FindMethod return:" + std::to_string(result));
		return result;
	}
	if ("setUser" == methodMame) {
		int result = CAddInNative::Methods::setUser;
		myLog("FindMethod return:" + std::to_string(result));
		return result;
	}
	if ("setPassword" == methodMame) {
		int result = CAddInNative::Methods::setPassword;
		myLog("FindMethod return:" + std::to_string(result));
		return result;
	}
	if ("start" == methodMame) {
		int result = CAddInNative::Methods::start;
		myLog("FindMethod return:" + std::to_string(result));
		return result;
	}
	return -1;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CAddInNative::GetMethodName(const long lMethodNum, 
                            const long lMethodAlias)
{ 
	myLog("GetMethodName"); 
	return 0;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetNParams(const long lMethodNum)
{ 
	myLog("GetNParams:"+ std::to_string(lMethodNum));
	switch (lMethodNum)
	{
	case CAddInNative::Methods::setPort:
		return 1;
	case CAddInNative::Methods::setIp:
		return 1;
	case CAddInNative::Methods::setPassword:
		return 1;
	case CAddInNative::Methods::setUser:
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------//
bool CAddInNative::GetParamDefValue(const long lMethodNum, const long lParamNum,
                          tVariant *pvarParamDefValue)
{ 
	myLog("GetParamDefValue"); 
	return false;
} 
//---------------------------------------------------------------------------//
bool CAddInNative::HasRetVal(const long lMethodNum)
{ 
	myLog("HasRetVal:"+std::to_string(lMethodNum));
	switch (lMethodNum)
	{
	case CAddInNative::CAddInNative::start:
		return false;
	}
	return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray)
{ 
	myLog("CallAsProc get:"+std::to_string(lMethodNum));
	int llen;
	int lport;
	char* message;

	switch (lMethodNum)
	{
	case CAddInNative::Methods::setPort:
		myLog("CallAsProc need call 'setPort'.");
		lport = paParams->intVal;
		myLog("CallAsProc need call 'setPort' paParams port=." + std::to_string(lport));
		this->port = lport;
		return true;
		break;
	case CAddInNative::Methods::setIp:
	{
		int llen = paParams->wstrLen;
		wchar_t* message = paParams->pwstrVal;
		std::wstring l1messageW(message, llen);
		std::string l1messageL(l1messageW.begin(), l1messageW.end());
		myLog("CallAsProc need call 'setIp' paParams len str=." + std::to_string(llen) + " - " + l1messageL);
		this->ip = l1messageL;
		return true;
		break;
	}
	case CAddInNative::Methods::setPassword:
	{
		int llen = paParams->wstrLen;
		wchar_t* message = paParams->pwstrVal;
		std::wstring l1messageW(message, llen);
		std::string l1messageL(l1messageW.begin(), l1messageW.end());
		myLog("CallAsProc need call 'setPassword' paParams len str=." + std::to_string(llen) + " - " + l1messageL);
		this->password = l1messageL;
		return true;
		break;
	}
	case CAddInNative::Methods::setUser:
	{
		int llen = paParams->wstrLen;
		wchar_t* message = paParams->pwstrVal;
		std::wstring l1messageW(message, llen);
		std::string l1messageL(l1messageW.begin(), l1messageW.end());
		myLog("CallAsProc need call 'setUser' paParams len str=." + std::to_string(llen) + " - " + l1messageL);
		this->user = l1messageL;
		return true;
		break;
	}
	case CAddInNative::Methods::start:
	{
		std::string message = "run listener: ip" + this->ip + " port:" + std::to_string(this->port) + " user:" + this->user + "password:" + this->password;
		myLog(message);
		runListen(this->pAsyncEvent,this->ip, this->port, this->user, this->password);
		return true;
		break;
	}
	}
	return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{ 
	myLog("CallAsFunc"); 
	return false;
}
//---------------------------------------------------------------------------//
void CAddInNative::SetLocale(const WCHAR_T* loc)
{
	myLog("SetLocale");
#ifndef __linux__
    _wsetlocale(LC_ALL, loc);
#else
    int size = 0;
    char *mbstr = 0;
    wchar_t *tmpLoc = 0;
    convFromShortWchar(&tmpLoc, loc);
    size = wcstombs(0, tmpLoc, 0)+1;
    mbstr = new char[size];

    if (!mbstr)
    {
        delete[] tmpLoc;
        return;
    }

    memset(mbstr, 0, size);
    size = wcstombs(mbstr, tmpLoc, wcslen(tmpLoc));
    setlocale(LC_ALL, mbstr);
    delete[] tmpLoc;
    delete[] mbstr;
#endif
}
//---------------------------------------------------------------------------//
bool CAddInNative::setMemManager(void* mem)
{
	myLog("setMemManager");
	memManager = (IMemoryManager*)mem;
    return true;
}
//---------------------------------------------------------------------------//

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len)
{
	if (!len)
        len = ::wcslen(Source)+1;

    if (!*Dest)
        *Dest = new WCHAR_T[len];

    WCHAR_T* tmpShort = *Dest;
    wchar_t* tmpWChar = (wchar_t*) Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(WCHAR_T));
    do
    {
        *tmpShort++ = (WCHAR_T)*tmpWChar++;
        ++res;
    }
    while (len-- && *tmpWChar);

    return res;
}
//---------------------------------------------------------------------------//
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len)
{
    if (!len)
        len = getLenShortWcharStr(Source)+1;

    if (!*Dest)
        *Dest = new wchar_t[len];

    wchar_t* tmpWChar = *Dest;
    WCHAR_T* tmpShort = (WCHAR_T*)Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(wchar_t));
    do
    {
        *tmpWChar++ = (wchar_t)*tmpShort++;
        ++res;
    }
    while (len-- && *tmpShort);

    return res;
}
//---------------------------------------------------------------------------//
uint32_t getLenShortWcharStr(const WCHAR_T* Source)
{
    uint32_t res = 0;
    WCHAR_T *tmpShort = (WCHAR_T*)Source;

    while (*tmpShort++)
        ++res;

    return res;
}
//---------------------------------------------------------------------------//
