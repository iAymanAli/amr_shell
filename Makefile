amr: build/main.o build/autocompletion_handlers.o build/cmd_handlers.o build/tokenizers.o build/utils.o
	@printf "\033[33m Compiling amr executable \033[0m\n"
	gcc build/main.o build/autocompletion_handlers.o build/cmd_handlers.o build/tokenizers.o build/utils.o -o build/amr -lreadline
	@printf "\033[32m amr was compiled successfully and is ready for use \033[0m\n"

build/main.o: src/main.c 
	@mkdir -p build
	@printf "\033[33m Compiling main.o from main.c \033[0m\n"
	gcc -Iinclude -c src/main.c -o build/main.o
	@printf "\033[32m main.o was compiled successfully \033[0m\n"
	@printf "\n"

build/autocompletion_handlers.o: src/autocompletion_handlers.c 
	@printf "\033[33m Compiling autocompletion_handlers.o from autocompletion_handlers.c \033[0m\n"
	gcc -Iinclude -c src/autocompletion_handlers.c -o build/autocompletion_handlers.o -lreadline
	@printf "\033[32m autocompletion_handlers.o was compiled successfully \033[0m\n"
	@printf "\n"

build/cmd_handlers.o: src/cmd_handlers.c 
	@printf "\033[33m Compiling cmd_handlers.o from cmd_handlers.c \033[0m\n"
	gcc -Iinclude -c src/cmd_handlers.c -o build/cmd_handlers.o
	@printf "\033[32m cmd_handlers.o was compiled successfully \033[0m\n"
	@printf "\n"

build/tokenizers.o: src/tokenizers.c 
	@printf "\033[33m Compiling tokenizers.o from tokenizers.c \033[0m\n"
	gcc -Iinclude -c src/tokenizers.c -o build/tokenizers.o
	@printf "\033[32m tokenizers.o was compiled successfully \033[0m\n"
	@printf "\n"

build/utils.o: src/utils.c 
	@printf "\033[33m Compiling utils.o from utils.c \033[0m\n"
	gcc -Iinclude -c src/utils.c -o build/utils.o
	@printf "\033[32m utils.o was compiled successfully \033[0m\n"
	@printf "\n"

run:
	./build/amr

clean:
	@printf "\033[33m Deleting all object and executable files from build/ directory \033[0m\n"
	rm build/*
	@printf "\033[32m Files were deleted successfully \033[0m\n"