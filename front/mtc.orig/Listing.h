#define DEFINITION_Listing

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#define Listing_NoListing        0
#define Listing_Listing        1
typedef unsigned char Listing_tListMode;
extern IO_tFile Listing_SourceFile;
extern IO_tFile Listing_ListFile;
extern Listing_tListMode Listing_ListMode;
extern void Listing_PutError ARGS((CARDINAL Code, CARDINAL Class, CARDINAL Line, CARDINAL Column, CARDINAL InfoClass, ADDRESS Info));
extern BOOLEAN Listing_HasError ARGS(());
extern void Listing_GetError ARGS((CARDINAL *Code, CARDINAL *Class, CARDINAL *Line, CARDINAL *Column, CARDINAL *InfoClass, ADDRESS *Info));
extern void Listing__init();
