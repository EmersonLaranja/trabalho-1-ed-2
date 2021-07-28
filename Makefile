
compile:
	gcc *.c -o main -lm

run:
	./main in-exemplos/entrada.txt 3 saida.txt

valgrind:
	valgrind ./main henrique/in/5.txt 10 saida.txt -s