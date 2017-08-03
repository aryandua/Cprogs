clean:
	@rm *.out; rm out1; rm out2;
run:
	@./conv $(file) $(size) | sort -n > out1; gcc m2.c -o m2.out; ./m2.out $(size) > scc.txt; cat out1 >> scc.txt;gcc scc.c -o 2sat.out; ./2sat.out scc.txt > out2; cat out2;
