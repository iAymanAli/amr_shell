amr: build/main.o build/autocompletion_handlers.o build/cmd_handlers.o build/tokenizers.o build/utils.o
	gcc build/main.o build/autocompletion_handlers.o build/cmd_handlers.o build/tokenizers.o build/utils.o -o build/amr -lreadline

build/main.o: src/main.c 
	gcc -Iinclude -c src/main.c -o build/main.o

build/autocompletion_handlers.o: src/autocompletion_handlers.c 
	gcc -Iinclude -c src/autocompletion_handlers.c -o build/autocompletion_handlers.o -lreadline

build/cmd_handlers.o: src/cmd_handlers.c 
	gcc -Iinclude -c src/cmd_handlers.c -o build/cmd_handlers.o

build/tokenizers.o: src/tokenizers.c 
	gcc -Iinclude -c src/tokenizers.c -o build/tokenizers.o

build/utils.o: src/utils.c 
	gcc -Iinclude -c src/utils.c -o build/utils.o

run:
	./build/amr

clean:
	rm build/*