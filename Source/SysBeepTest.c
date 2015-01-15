/* SysBeepTest.c */

#include <Carbon/Carbon.h>

/* seeing as we are not building Sound.c into any sort of library
 * (at least not yet), just copy the function here for now: */
#if defined(__LP64__) && __LP64__
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "using handwritten 64-bit replacement for SysBeep()"
# endif /* __GNUC__ && !__STRICT_ANSI__ */
/*--------------------------------------------------------  SysBeep */
void SysBeep(short duration)
{
	short counter = 0;
	while (counter < duration) {
        /* On OS X, using the ASCII bell character with printf() has the
         * same effect as playing the system warning sound: */
		printf("\a");
		counter++;
	}
    /* FIXME: here we are using the "duration" parameter to vary the number
     * of beeps; this does not match the original behavior of SysBeep()
     * though... */
}
#endif /* __LP64__ */

int main(int argc, char *argv[]) {
#pragma unused (argc, argv)
	while (1) {
		short beepDuration;
		char *beepDurationString;
		void *buf;
		printf("Enter how long to beep> ");
		scanf("%s", &beepDurationString);
		if (beepDurationString != NULL) {
			beepDuration = (short)atoi((const char *)&beepDurationString);
		} else {
			exit(1);
		}
		printf("\n beeping for duration '%i'\n", beepDuration);
		buf = malloc(sizeof(beepDuration));
		SysBeep(beepDuration); /* throws an error if memory has not been malloced */
		free(buf);
	}
	return 0;
}

#if defined(__LP64__) && __LP64__
/*
 Local Variables:
 compile-command: "gcc -g3 -ggdb3 -O0 -fpascal-strings -fexceptions -m64 -mmacosx-version-min=10.4 -mfix-and-continue -Wall -Wextra SysBeepTest.c -framework Carbon -o SysBeepTest"
 End:
 */
#else
/*
 Local Variables:
 compile-command: "gcc -g3 -ggdb3 -O0 -fpascal-strings -fexceptions -m32 -mmacosx-version-min=10.4 -mfix-and-continue -Wall -Wextra -pedantic -ansi SysBeepTest.c -framework Carbon -o SysBeepTest"
 End:
 */
#endif /* __LP64__ */

/* EOF */
