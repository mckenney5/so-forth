#ifndef _USING_CONFIG_H
#define _USING_CONFIG_H

/* Config file for soforth */

// size of data stack
#define MAX 250 // the max is this number -1 for under and overflow protection

// size of script files
#define MAX_SCRIPT 1024

// what is displayed to the user
#define PROMPT ""

// version number
#define VERSION "Alpha 0.0.1"
#ifdef DEBUGGING
	#define VERSION_FULL VERSION " DEBUGGING"
#else
	#define VERSION_FULL VERSION
#endif

#define MOTD "~soforth " VERSION_FULL "~\nTo exit, type 'bye'"

// padding of interp input
#define PADDING " "

// Forths true and false statement
#define _TRUE -1
#define _FALSE 0

#endif
