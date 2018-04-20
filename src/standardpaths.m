#include <Cocoa/Cocoa.h>
#include <string.h>

char * osx_get_path(char *buffer, size_t len) {
    NSArray<NSURL*> *urls = [
        [NSFileManager defaultManager] 
        URLsForDirectory:NSApplicationSupportDirectory 
        inDomains:NSUserDomainMask
    ];

    if ([urls count] == 0) return NULL;

    NSURL *url = urls.firstObject;

    NSString *url_s = [url absoluteString];

    size_t slen =[url_s length];

    if (slen > len) return NULL;

    if (buffer == NULL)
        buffer = malloc(sizeof(char)*slen);
    
    memcpy(buffer, url_s, slen);

    return buffer;
}

char *get_path_osx(cs_stdpath_dir dir, cs_stdpath_domain domain) {
    NSArray<NSURL*> *urls = [
        [NSFileManager defaultManager] 
        URLsForDirectory:NSApplicationSupportDirectory 
        inDomains:NSUserDomainMask
    ];

    if ([urls count] == 0) return NULL;

    

}