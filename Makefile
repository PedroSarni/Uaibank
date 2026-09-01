CC = gcc
CFLAGS = -Wall -Wextra -pedantic
FONTE = src/UAIBANK.c src/funcões.c
EXECUTAVEL = build/UAIBANK

.PHONY: build run clean

build: $(EXECUTAVEL)

$(EXECUTAVEL): $(FONTE)
	mkdir -p build
	$(CC) $(CFLAGS) $(FONTE) -o $(EXECUTAVEL)

run: build
	./$(EXECUTAVEL)

clean:
	rm -f $(EXECUTAVEL)