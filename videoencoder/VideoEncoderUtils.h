#ifndef __VIDEO_ENCODER_UTILS_H__
#define __VIDEO_ENCODER_UTILS_H__
#include <va/va.h>
#include <va/va_tpi.h>
#include "VideoEncoderDef.h"
#include "IntelMetadataBuffer.h"
#ifdef IMG_GFX
#include <hardware/gralloc.h>
#endif

#define MAP_ACTION_COPY         0x00000001  //mem copy
#define MAP_ACTION_ALIGN64      0x00000002  //align 64
#define MAP_ACTION_COLORCONVERT 0x00000004  //color convert
#define MAP_ACTION_RESIZE       0x00000008  //resize

class VASurfaceMap {
public:
    VASurfaceMap(VADisplay display, int hwcap);
    ~VASurfaceMap();

    Encode_Status doMapping();
    VASurfaceID getVASurface() {return mVASurface;}
    int32_t getValue() {return mValue;}
    ValueInfo* getValueInfo() {return &mVinfo;}

    void setVASurface(VASurfaceID surface) {mVASurface = surface;}
    void setValue(int32_t value) {mValue = value;}
    void setValueInfo(ValueInfo& vinfo) {memcpy(&mVinfo, &vinfo, sizeof(ValueInfo));}
    void setTracked() {mTracked = true;}
    void setAction(int32_t action) {mAction = action;}

private:
    Encode_Status doAllocation();
    Encode_Status doActionCopy();
    Encode_Status doActionColConv();
    Encode_Status MappingToVASurface();
    Encode_Status MappingSurfaceID();
    Encode_Status MappingGfxHandle();
    Encode_Status MappingKbufHandle();
    Encode_Status MappingMallocPTR();
    VASurfaceID CreateSurfaceFromExternalBuf(int32_t value, ValueInfo& vinfo);

    VADisplay mVADisplay;

    int32_t mValue;

    VASurfaceID mVASurface;
    int32_t mVASurfaceWidth;
    int32_t mVASurfaceHeight;

//    MetadataBufferType mType;

    ValueInfo mVinfo;
    bool mTracked;

    int32_t mAction;

    int32_t mSupportedSurfaceMemType;

#ifdef IMG_GFX
    //special for gfx color format converter
    buffer_handle_t mGfxHandle;
    bool mGfxHandleAllocated;
#endif
};

VASurfaceID CreateNewVASurface(VADisplay display, int32_t width, int32_t height);

#endif

