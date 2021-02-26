#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	
	if(argc<2){
		printf("Missing argument.\n");
		return 1;
	}

	long long int in = atoll(argv[1]);
	long long int num = in;
	long long int h = num;
	long long int s = 0;

	if(num<1){
		printf("Invalid positive integer.\n");
		return 1;
	}
	
	int pipe_ends[2];
	pipe(pipe_ends);

	int read_fd = pipe_ends[0];
	int write_fd = pipe_ends[1];

	pid_t pid = fork();

	if(pid == 0){
		while(num != 1){
			if(num % 2 == 0){
				num = num/2;
			}
			else{
				num = (num*3) + 1;
			}
			write(write_fd, &num, sizeof(num));
		}
	}

	else{
		printf("%lld, ", num);

		while(num != 1){

			read(read_fd, &num, sizeof(num));
			s++;

			if(num > h){
				h = num;
			}
			printf("%lld, ", num);
		}
		printf("(%lld, %lld)\n", s, h);
	
	}
}
