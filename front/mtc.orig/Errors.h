#define DEFINITION_Errors

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#define Errors_NoText   0
#define Errors_SyntaxError   1
#define Errors_ExpectedTokens   2
#define Errors_RestartPoint   3
#define Errors_TokenInserted   4
#define Errors_WrongParseTable   5
#define Errors_OpenParseTable   6
#define Errors_ReadParseTable   7
#define Errors_Fatal   1
#define Errors_Restriction   2
#define Errors_Error   3
#define Errors_Warning   4
#define Errors_Repair   5
#define Errors_Note   6
#define Errors_Information   7
#define Errors_None   0
#define Errors_Integer   1
#define Errors_Short   2
#define Errors_Long   3
#define Errors_Real   4
#define Errors_Boolean   5
#define Errors_Character   6
#define Errors_String   7
#define Errors_Array   8
#define Errors_Set   9
#define Errors_Ident   10
#define Errors_eInteger   1
#define Errors_eShort   2
#define Errors_eLong   3
#define Errors_eReal   4
#define Errors_eBoolean   5
#define Errors_eCharacter   6
#define Errors_eString   7
#define Errors_eArray   8
#define Errors_eSet   9
#define Errors_eIdent   10
#define Errors_eTermSet   11
#define Errors_eFatal   1
#define Errors_eRestriction   2
#define Errors_eError   3
#define Errors_eWarning   4
#define Errors_eRepair   5
#define Errors_eNote   6
#define Errors_eInformation   7
#define Errors_SysOffset   100
#define Errors_eInternal   15
#define Errors_eImmediate        0
#define Errors_eNoListing        1
#define Errors_eListing        2
typedef unsigned char Errors_tReportMode;
#define Errors_MaxErrorClass   7
extern struct Errors_1 {
    SHORTCARD A[Errors_MaxErrorClass + 1];
} Errors_ErrorCount;
extern void Errors_ErrorMessage ARGS((CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position));
extern void Errors_ErrorMessageI ARGS((CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position, CARDINAL InfoClass, ADDRESS Info));
extern void Errors_BeginErrors ARGS(());
extern void Errors_SetReportMode ARGS((Errors_tReportMode mode));
extern void Errors_CloseErrors ARGS(());
extern BITSET Errors_ReportClass;
extern struct Errors_2 {
    CHAR A[255 + 1];
} Errors_ErrorTable;
extern void Errors__init();
