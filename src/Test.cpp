#include "ThreadPool.h"
#include <cmath>
using namespace tpool;
using namespace std;

void calc()
{
	cout << "Calculation start!" << endl;
	float x = 123.0f;
	for (int i = 0; i < 999999999; i++)
	{
		sqrtf(x * 1234567.89f);
	}

	cout << "Calculation complete!" << endl;
}

int main()
{
	ThreadPool *threadPool = new ThreadPool(4);
	threadPool->start();

	for (int i = 0; i < 6; i++)
	{
		threadPool->execute(&calc);
	}

	threadPool->shutdownGracefully();  // Or call threadPool->shutdown() to shutdown immediately

	return 0;
}