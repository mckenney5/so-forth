#ifndef _USING_CONFIG_H
#define _USING_CONFIG_H

/* Config file for soforth */

// size of memory
#define MAX 250 // the max is this number -1 for under and overflow protection

// size of script files
#define MAX_SCRIPT 1024

// what is displayed to the user
#define PROMPT ""


#define MOTD "~soforth~\nTo exit, type 'bye'"

// padding of interp input
#define PADDING " "

// Forths true and false staement
#define _TRUE -1
#define _FALSE 0

#endif
