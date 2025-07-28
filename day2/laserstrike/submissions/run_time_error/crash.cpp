#include <unistd.h>
#include <signal.h>

int main() {
	kill(getpid(), 9);
	return 1;
}
