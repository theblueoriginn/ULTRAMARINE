default:
	@echo "Making script binary and executing.."
	@g++ script.cpp -o script.o
	@./script.o
