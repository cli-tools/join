.PHONY: clean install

join-$(shell uname -s)-$(shell uname -m): join.c
	cc -posix -std=c89 -Wall -static -o $@ $<

clean:
	$(RM) join-$(shell uname -s)-$(shell uname -m)

install: join-$(shell uname -s)-$(shell uname -m)
	install $< /usr/local/bin/join
