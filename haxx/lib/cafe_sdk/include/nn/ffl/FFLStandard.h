#ifndef FFL_STANDARD_H_
#define FFL_STANDARD_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FFL_MIIDATA_PACKET_SIZE (0x60)

typedef struct FFLStoreData
{
    union
    {
        u8 data[FFL_MIIDATA_PACKET_SIZE];
        u32 value32[FFL_MIIDATA_PACKET_SIZE / sizeof(u32)];
    };
}
FFLStoreData;

#ifdef __cplusplus
}
#endif

#endif // FFL_STANDARD_H_
