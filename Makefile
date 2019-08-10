join: join.c
	cc -posix -std=c89 -Wall -static -o $@ $<

install: join
	install join /usr/local/bin/join
