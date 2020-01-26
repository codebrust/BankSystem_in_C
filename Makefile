output: main.c
	gcc main.c

clean:
	rm *.o

hello:
	echo "Hello"
exit:
	taskkill /f /im a.exe
test:
	gcc test.c -o test;
	./test