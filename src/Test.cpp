#include "ThreadPool.h"
#include <cmath>
using namespace tpool;
using namespace std;

void calc()
{
    cout << "Calc() start!" << endl;
    float x = 123.0f;
    for (int i = 0; i < 99999999; i++)
    {
        sqrtf(x * 1234567.89f);
    }

    cout << "Calc() complete!" << endl;
}

class Calculator
{
public:
    void calculate(float a, float b)
    {
        cout << "Calculate " << a << " and " << b << endl;
    };
};


int main()
{
    // Create thread pool with 4 threads
    ThreadPool *threadPool = new ThreadPool(4);

    //Start pool 
    threadPool->start();

    //Do something
    Calculator calculator;
    for (int i = 0; i < 6; i++)
    {
        threadPool->execute(&calc);
        threadPool->execute(&Calculator::calculate, calculator, 123.4f, 456.7f);
    }

    //Shutdown the pool
    threadPool->shutdownGracefully();  // Call threadPool->shutdown() to shutdown IMMEDIATELY

    return 0;
}