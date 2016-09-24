#include "ThreadPool.h"

tpool::ThreadPool::ThreadPool(int poolSize /*= DEFAULT_POOL_SIZE*/)
{
    size = poolSize > 0 ? poolSize : DEFAULT_POOL_SIZE;
    worker = NULL;
}

tpool::ThreadPool::~ThreadPool()
{
    if (worker != NULL && !ioService.stopped())
    {
        _shutdown();
        delete worker;
        worker = NULL;
    }
}

void tpool::ThreadPool::start()
{
    if (worker != NULL)
    {
        return;
    }

    worker = new boost::asio::io_service::work(ioService);

    for (int i = 0; i < size; i++)
    {
        pool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService));
    }
}

void tpool::ThreadPool::shutdown()
{
    pool.interrupt_all();
    _shutdown();
}

void tpool::ThreadPool::shutdownGracefully()
{
    _shutdown();
    pool.join_all();
}


void tpool::ThreadPool::_shutdown()
{
    ioService.reset();
    ioService.stop();
}
