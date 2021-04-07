#include <stdio.h>
#include <signal.h>

void handleSignals(int signal);

int main()
{
	void (*sigHandlerInterrupt)(int);
	void (*sigHandlerQuit)(int);
	void (*sigHandlerReturn)(int);

	sigHandlerInterrupt = sigHandlerQuit = handleSignals;
	sigHandlerReturn = signal(SIGINT, sigHandlerInterrupt);

	if (sigHandlerReturn == SIG_ERR)
	{
		perror("signal error: ");
		return 1;
	}

	sigHandlerReturn = signal(SIGQUIT, sigHandlerQuit);

	if (sigHandlerReturn == SIG_ERR)
	{
		perror("signal error: ");
		return 1;
	}
	while (1)
	{
		printf("A program leallitasahoz:\n");
		printf("Nyisson meg egy masik terminalt\n");
		printf("Adja ki a parancsot: kill %d vagy Control + C ketszer\n", getpid());
		sleep(10);
	}
	return 0;
}
void handleSignals(int signalNumber)
{
	switch (signalNumber)
	{
	case SIGINT:
		printf("Nyomja meg a Control + C billentyukombinaciot!\n");
		signal(SIGINT, SIG_DFL);
		break;
	case SIGQUIT:
		printf("Nyomja meg a Control +\\\n");
		break;
	default:
		printf("Fogadott signal szama: %d\n", signalNumber);
		break;
	}
}
