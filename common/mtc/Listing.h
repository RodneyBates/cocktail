#define DEFINITION_Listing

#ifndef DEFINITION_IO
#include "IO.h"
#endif

extern IO_tFile Listing_SourceFile;
extern IO_tFile Listing_ListFile;
extern BOOLEAN Listing_LongListing;
extern void Listing_PutError ARGS((INTEGER ErrorCode, INTEGER ErrorClass, INTEGER Line, INTEGER Column, INTEGER InfoClass, ADDRESS Info));
extern BOOLEAN Listing_HasError ARGS(());
extern void Listing_GetError ARGS((INTEGER *ErrorCode, INTEGER *ErrorClass, INTEGER *Line, INTEGER *Column, INTEGER *InfoClass, ADDRESS *Info));
extern void Listing__init();
