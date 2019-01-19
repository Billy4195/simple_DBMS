TARGET=shell

all: $(TARGET)

shell: shell.c
	gcc $< -o $@

clean:
	rm $(TARGET)
