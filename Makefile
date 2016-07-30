all:
	g++ -O3 -I${AMDAPPSDKROOT}/include/ -c *.cpp
	g++ ${AMDAPPSDKROOT}/lib/x86/lib*.so *.o -o simulatoreAC

clean:
	rm *.o
