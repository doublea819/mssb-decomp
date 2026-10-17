// Apple TV: apps get no permanent file storage (the user folder is a cache tvOS may
// clear when space runs low), so small saves are mirrored into NSUserDefaults and put
// back if the file is gone. Built only for tvOS.
#import <Foundation/Foundation.h>

#include <cstdio>

extern "C" void port_store_backup(const char* path, const char* key)
{
    @autoreleasepool {
        NSData* data = [NSData dataWithContentsOfFile:[NSString stringWithUTF8String:path]];
        if (data == nil || data.length > 256 * 1024)
            return;
        NSUserDefaults* d = [NSUserDefaults standardUserDefaults];
        [d setObject:data forKey:[NSString stringWithUTF8String:key]];
        [d synchronize];
    }
}

// Writes the backup to `path` when the file is missing. Returns 1 if it did.
extern "C" int port_store_restore(const char* path, const char* key)
{
    @autoreleasepool {
        NSString* p = [NSString stringWithUTF8String:path];
        if ([[NSFileManager defaultManager] fileExistsAtPath:p])
            return 0;
        NSData* data = [[NSUserDefaults standardUserDefaults] dataForKey:[NSString stringWithUTF8String:key]];
        if (data == nil)
            return 0;
        [[NSFileManager defaultManager] createDirectoryAtPath:[p stringByDeletingLastPathComponent]
                                  withIntermediateDirectories:YES
                                                   attributes:nil
                                                        error:nil];
        if (![data writeToFile:p atomically:YES])
            return 0;
        fprintf(stderr, "[store] %s restored from the backup\n", key);
        return 1;
    }
}
