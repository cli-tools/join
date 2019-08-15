PREFIX?=/usr/local

.PHONY: clean install

join-$(shell uname -s)-$(shell uname -m): join.c
	$(CC) -posix -std=c89 -Wall -static -o $@ $<
	strip $@

clean:
	$(RM) join-$(shell uname -s)-$(shell uname -m)

install: join-$(shell uname -s)-$(shell uname -m)
	install $< $(addprefix $(PREFIX)/,bin/join)
