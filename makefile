SOFORTH_DEPENDS = src/ui.c src/interp.c src/interp.h src/stack.c src/stack.h src/config.h src/words.c src/words.h
LINENOISE_DEPENDS = libs/linenoise.c libs/linenoise.h
C_FILES = libs/linenoise.c src/ui.c src/interp.c src/stack.c src/words.c
C_FLAGS = -Wall -Wformat-truncation=0 -Wimplicit-fallthrough=0 -Ofast
C_DEBUG_FLAGS = -Wall -Wextra -O0 -g -DDEBUGGING -Wimplicit-fallthrough=0

soforth: $(SOFORTH_DEPENDS) $(LINENOISE_DEPENDS)
	$(CC) $(C_FLAGS) -o soforth.out $(C_FILES)

debug: $(SOFORTH_DEPENDS) $(LINENOISE_DEPENDS)
	# Used if you want debugging features on
	$(CC) $(C_DEBUG_FLAGS) -o soforth.debugging.out $(C_FILES)

clean:
	rm *.out

