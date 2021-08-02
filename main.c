#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define RC (c=rdchr())
#define PC putchar(c)

char *argv0;
char c;
unsigned int curbyte = 0;

void
usage(void)
{
	fprintf(stderr, "usage: %s\n", argv0);
	exit(1);
}

void
synerr(void)
{
	fprintf(stderr, "%s: syntax error at byte %d\n", argv0, curbyte);
	exit(1);
}


char
rdchr(void)
{
	curbyte++;
	return getchar() ;
}

void
hndltag(void)
{
	char tagname[64];
	char *buf = tagname ;

	/* Skip spaces in front of tag name. */
	while(isspace(RC))
		PC;

	/* Reading tag name. */
	putchar(*buf++ = c);
	while( !isspace(RC) && c!='>' )
		putchar(*buf++ = c);
	*buf = 0 ;

	/* Getting the rest of tag data. */
	if(c!='>'){
		PC;
		while(RC != '>'){
			if(c==EOF) synerr() ;
			PC;
		}
	}
	PC;

	/* Return if singleton tag. */
	if(RC != '{'){
		PC;
		return;
	}

	/* Handle inside data. */
	while(RC != '}'){
		if(c == EOF) synerr() ;
		PC;
		if(c == '<') hndltag() ;
	}
	printf("</%s>", tagname);
}

int
main(int argc, char *argv[])
{
	argv0 = argv[0] ;
	if(argc!=1) usage() ;

	while(RC != EOF){
		putchar(c);
		if(c == '<')
			hndltag();
	}

	return 0 ;
}

