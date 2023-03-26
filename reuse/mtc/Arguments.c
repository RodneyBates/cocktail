/* $Id: Arguments.c */

/*
 *	Implementation of procedures GetArgs and GetEnv
 *	from Modula-2 def module Arguments
 *
 *      RMB 93/10/14  This version works with WRL Modula-2.
 */

#define FALSE		((BOOLEAN)0)
#define TRUE		((BOOLEAN)1)

typedef long    	INTEGER;
typedef unsigned char	BOOLEAN;
typedef unsigned char	CHAR;

typedef struct Arguments_1 {
    struct Arguments_2 {
        CHAR A[999 + 1];
    } *A[999 + 1];
} *Arguments_ArgTable;

/**/
extern void GetArgs (INTEGER *argc, Arguments_ArgTable *argv);
extern void GetEnv (Arguments_ArgTable *env);
extern void Arguments__init(); 
/**/

extern INTEGER parameters_argc;
extern Arguments_ArgTable parameters_argv;
extern Arguments_ArgTable parameters_envp;

/*
void GetArgs
# ifdef __STDC__
(INTEGER *argc, Arguments_ArgTable *argv)
# else
(argc, argv) INTEGER *argc; Arguments_ArgTable *argv;
# endif
{
  *argc = parameters_argc;
  *argv = parameters_argv;
}

void GetEnv
# ifdef __STDC__
(Arguments_ArgTable *env)
# else
(env)
Arguments_ArgTable *env;
# endif
{
  *env = parameters_envp;
}
 
void Arguments__init () { }
*/





