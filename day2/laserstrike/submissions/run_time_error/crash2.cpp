#include <unistd.h>
#include <signal.h>

int main() {
	raise(9);
	return 1;
}
