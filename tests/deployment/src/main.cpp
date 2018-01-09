#include <signal.h>
#include <iostream>

#include <ngrest/utils/Log.h>
#include <ngrest/engine/Engine.h>
#include <ngrest/engine/ServiceDispatcher.h>
#include <ngrest/engine/Deployment.h>
#include <ngrest/engine/FilterDispatcher.h>
#include <ngrest/engine/FilterDeployment.h>
#include <ngrest/engine/HttpTransport.h>

#include "servercommon.h"
#include "Server.h"
#include "ClientHandler.h"

#include "TestFilterGroup.h"
#include "TestServiceGroup.h"

#if defined WIN32 || defined __APPLE__
typedef void(__cdecl *sighandler_t)(int);
#endif

int help() {
    std::cerr << "ngrest_server [-h][-p <PORT>]" << std::endl
              << "  -p        port number to use (default: 9098)" << std::endl
              << "  -h        display this help" << std::endl << std::endl;
    return 1;
}


int main(int argc, char* argv[])
{
    ngrest::StringMap args;

    for (int i = 1; i < argc; i += 2) {
        if (argv[i][0] != '-' || argv[i][1] == '\0' || (i + 1) == argc) {
            return help();
        }

        args[argv[i] + 1] = argv[i + 1];
    }

    static ngrest::Server server;
    ngrest::ServiceDispatcher dispatcher;
    ngrest::Deployment deployment(dispatcher);
    ngrest::FilterDispatcher filterDispatcher;
    ngrest::FilterDeployment filterDeployment(filterDispatcher);
    ngrest::HttpTransport transport;
    ngrest::Engine engine(dispatcher);
    ngrest::ClientHandler clientHandler(engine, transport);

    engine.setFilterDispatcher(&filterDispatcher);

    server.setClientCallback(&clientHandler);

    if (!server.create(args))
        return 1;

    sighandler_t signalHandler = [] (int) {
        ngrest::LogInfo() << "Stopping server";
        server.quit();
    };

    ::signal(SIGINT, signalHandler);
    ::signal(SIGTERM, signalHandler);
#ifndef WIN32
    ::signal(SIGPIPE, SIG_IGN);
#endif


    /*
    test with:
    async mode:
      curl -i -X GET -H "Content-Type:application/json" 'http://localhost:8080/td/sync?value=Hello_world'

    sync mode:
      curl -i -X GET -H "Content-Type:application/json" 'http://localhost:8080/td/async/Hello_world'
    */

    ngrest::TestFilterGroup filterGroup;
    filterDeployment.deployStatic(&filterGroup);

    ngrest::TestServiceGroup serviceGroup;
    deployment.deployStatic(&serviceGroup);

    return server.exec();
}
