#include "types.h"
#include "user.h"

// pipe(p) --> initializes an unnamed pipe and gives -
// p[0] - file descriptor for read end
// p[1] - file descriptor for write end

int main() {
	int p2c[2];
	int c2p[2];
	char buf[1];
	pipe(p2c);
	pipe(c2p);

	int pid;
	pid = fork();
	if (pid < 0) {
	printf(1, "Fork failed \n");
	exit();
	}
	if (pid==0){
		read(p2c[0], buf, 1); // read from parent
		printf(1, "%d: received ping \n", getpid());
		write(c2p[1], buf, 1);
		exit();
	} else {
		write(p2c[1], "x", 1);
		read(c2p[0], buf, 1);
		printf(1, "%d: received pong\n", getpid()); // 1 -> file descriptor -> standard output (0-stdin, 1- stdout, 2- stderr)
		wait();
		exit();
	}
}
