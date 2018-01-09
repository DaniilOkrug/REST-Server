//Azamat
#ifndef NGREST_SERVERCOMMON_H
#define NGREST_SERVERCOMMON_H

#include <map>
#include <string>

#ifdef WIN32
#include <winsock2.h>
#endif

namespace ngrest {

#ifndef WIN32
typedef int Socket;
#define NGREST_SOCKET_ERROR -1
#else
typedef SOCKET Socket;
#define NGREST_SOCKET_ERROR static_cast<SOCKET>(SOCKET_ERROR)
#endif

typedef std::map<std::string, std::string> StringMap;

}

#endif // NGREST_SERVERCOMMON_H

