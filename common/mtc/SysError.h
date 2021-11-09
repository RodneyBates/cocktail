#define DEFINITION_SysError

extern BOOLEAN SysError_StatIsBad ARGS((INTEGER N));
extern void SysError_SysErrorMessageI ARGS((INTEGER N, CARDINAL ErrCl, CARDINAL InfCl, ADDRESS Info));
extern void SysError_SysErrorMessage ARGS((INTEGER N, CARDINAL ErrCl));
extern void SysError__init();
