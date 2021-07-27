
compile:
	gcc *.c -o main -lm

run:
	./main in-exemplos/entrada.txt 3 saida.txt
valgrind:
	valgrind ./main henrique/in/3.txt 5 saida.txt -s