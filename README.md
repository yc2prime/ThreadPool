# ThreadPool
A C++11 thread pool implementation base on [Boost.Asio](http://www.boost.org/doc/libs/1_61_0/doc/html/boost_asio.html)


## Basic usage
```C++
#include "ThreadPool.h"
#include <cmath>
using namespace tpool;
using namespace std;

//An example to execute a function in pool
void calc()
{
    cout << "Calc() start!" << endl;
    for (int i = 0; i < 99999999; i++)
    {
        sqrtf(123.0f * 1234567.89f);
    }
    cout << "Calc() complete!" << endl;
}

//An example to execute a function with params
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
    
    Sleep(10000);

    //Shutdown the pool
    threadPool->shutdownGracefully();  // Call threadPool->shutdown() to shutdown IMMEDIATELY

    return 0;
}
```
