### Prime Numbers

Code requested for the subject Parallel and Distributed Programming (INE5645)

To compile the sequential code:
```sh
$ gcc main.c -o main
```
To run the sequential code you should add a limit number as an argument, e.g.:
```sh
$ ./main 10000
```

To compile the parallel code:
```sh
$ gcc main.c -o main -lpthread
```
To run the parallel code you should add two number arguments, the limit number and the number of threads, e.g.:
```sh
$ ./main 10000 10
```
