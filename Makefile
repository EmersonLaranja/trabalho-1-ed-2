
compile:
	gcc *.c -o main -lm

run1:
	valgrind ./main in-exemplos/1.txt 2 saida.txt

run2:
	valgrind ./main in-exemplos/2.txt 4 saida.txt

run3:
	valgrind ./main in-exemplos/3.txt 5 saida.txt

run4:
	valgrind ./main in-exemplos/4.txt 5 saida.txt
	
run5:
	valgrind ./main in-exemplos/5.txt 10 saida.txt

valgrind:
	valgrind ./main in-exemplos/entrada.txt 3 saida.txt --leak-check=full


valgrind1:
	./main henrique/in/1.txt 2 saida.txt --leak-check=full

valgrind2:
	./main henrique/in/2.txt 4 saida.txt --leak-check=full
	
valgrind3:
	./main henrique/in/3.txt 5 saida.txt --leak-check=full

valgrind4:
	./main henrique/in/4.txt 5 saida.txt --leak-check=full

valgrind5:
	./main henrique/in/5.txt 10 saida.txt --leak-check=full 

valgrind6:
	./main henrique/in/6.txt 3 saida.txt --leak-check=full

valgrind7:
	valgrind ./main henrique/in/7.txt 3 saida.txt --leak-check=full

valgrind8:
	valgrind ./main henrique/in/8.txt 10 saida.txt --leak-check=full -s

valgrind9:
	./main henrique/in/9.txt 42 saida.txt --leak-check=full

diff1:
	diff saida.txt henrique/out_nosso/saida1.txt	
diff2:
	diff saida.txt henrique/out_nosso/saida2.txt
diff3:
	diff saida.txt henrique/out_nosso/saida3.txt
diff4:
	diff saida.txt henrique/out_nosso/saida4.txt
diff5:
	diff saida.txt henrique/out_nosso/saida5.txt
diff6:
	diff saida.txt henrique/out_nosso/saida6.txt
diff7:
	diff saida.txt henrique/out_nosso/saida7.txt
diff8:
	diff saida.txt henrique/out_nosso/saida8.txt 
diff9:
	diff saida.txt henrique/out_nosso/saida9.txt 