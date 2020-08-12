gcc -c -o main.o main.c
gcc -c -o jfes.o jfes.c
gcc -c -o example_1.o example_1.c
gcc -o main main.o jfes.o example_1.o
rm main.o jfes.o example_1.o