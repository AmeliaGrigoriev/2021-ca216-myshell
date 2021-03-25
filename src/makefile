dst = ../bin

c = $(wildcard *.c)
bin = $(patsubst %.c, %, $(c))

build: $(addprefix $(dst)/, $(bin))
		@true

$(dst)/%: %.c
		gcc -o $@ $<
