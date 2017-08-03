clean:
	rm -rf bin/*

build:
	gcc $(FLAG) -D $(MODE) -D SIZE=$(SIZE) -o bin/$(MODE) qsort.c

build_all:
	make build MODE=FIRST SIZE=$(SIZE) -o bin/FIRST qsort.c
	make build MODE=LAST SIZE=$(SIZE) -o bin/LAST qsort.c
	make build MODE=AVG SIZE=$(SIZE) -o bin/AVG qsort.c
	echo "Build Done"

build_debug_all:
	make build FLAG=-g MODE=FIRST SIZE=$(SIZE) -o bin/FIRST qsort.c
	make build FLAG=-g MODE=LAST SIZE=$(SIZE) -o bin/LAST qsort.c
	make build FLAG=-g MODE=AVG SIZE=$(SIZE) -o bin/AVG qsort.c
	echo "Debug Build Done"

run_first:
	./bin/FIRST
run_last:
	./bin/LAST
run_avg:
	./bin/AVG

