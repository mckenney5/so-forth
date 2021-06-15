#ifndef _USING_COLORS_H
#define _USING_COLORS_H

/* Foreground Colors */
#ifndef NO_COLOR
	#define RED "\x1B[31m"
	#define GREEN "\x1B[32m"
	#define YELLOW "\x1B[33m"
	#define BLUE "\x1B[34m"
	#define MAGENTA "\x1B[35m"
	#define CYAN "\x1B[36m"
	#define WHITE "\x1B[37m"
	#define RESET "\x1B[0m"
#else
	#define RED ""
	#define GREEN ""
	#define YELLOW ""
	#define BLUE ""
	#define MAGENTA ""
	#define CYAN ""
	#define WHITE ""
	#define RESET ""
#endif

#endif
