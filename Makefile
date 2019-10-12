
main:
	touch RIDER.DAT RIDERS.DAT
	g++ -g -o main main.cpp

clean:
	rm -rf main ||:
	rm -rf main.exe ||:
	rm -rf RIDER.DAT ||:
	rm -rf RIDERS.DAT ||:
