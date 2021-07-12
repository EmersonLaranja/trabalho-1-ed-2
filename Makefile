
compile:
	gcc *.c -o main -lm

run:
	./main in-exemplos/5.txt 10 saida.txt
valgrind:
	valgrind ./main in-exemplos/5.txt 10 saida.txt 