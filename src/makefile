# Student Name: Amelia Grigoriev
# Student Number: 19348241
# In submitting this project, I declare that the project material, which I now submit, is my own work. Any assistance received by way of borrowing from the work of others has been cited and acknowledged within the work. I make this declaration in the knowledge that a breach of the rules pertaining to project submission may carry serious consequences.


dst = ../bin

c = $(wildcard *.c)
bin = $(patsubst %.c, %, $(c))

build: $(addprefix $(dst)/, $(bin))
		@true

$(dst)/%: %.c
		gcc -o $@ $<
