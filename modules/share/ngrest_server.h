//@Daniil Okrug
#ifndef NGREST_SERVER_H
#define NGREST_SERVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ngrest_server_request
{
    void* req;               
    const char* method;      
    const char* uri;        
    const char* clientHost;  
    const char* clientPort; 
    int hasBody;            
    int64_t bodySize;     
};

typedef int(*iterate_request_headers_callback)(void* context, const char* header, const char* value);

struct ngrest_mod_callbacks
{
    void (*iterate_request_headers)(void* req, void* context, iterate_request_headers_callback callback);
    int64_t (*read_block)(void* req, char* buffer, int64_t size);

    void (*set_response_header)(void* req, const char* header, const char* value);
    void (*set_content_type)(void* req, const char* contentType);
    void (*set_content_length)(void* req, int64_t contentLength);
    int64_t (*write_block)(void* req, const void* buffer, int64_t size);
    void (*finalize_response)(void* req, int statusCode);
};

int ngrest_server_startup(const char* servicesPath, const char* filtersPath);
int ngrest_server_shutdown();
int ngrest_server_dispatch(struct ngrest_server_request* request, struct ngrest_mod_callbacks callbacks);

#ifdef __cplusplus
}
#endif

#endif // NGREST_SERVER_H
