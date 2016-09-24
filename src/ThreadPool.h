/*
* ThreadPool - A thread pool implementation base on Boost.Asio
* Copyright (C)  2016  yc2prime

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see http://www.gnu.org/licenses/.
*/ 

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

namespace tpool
{
	class ThreadPool
	{
	public:
		//Default Pool Size
		static const int DEFAULT_POOL_SIZE = 1;

		//Constructor 
		ThreadPool(int poolSize = DEFAULT_POOL_SIZE);
		
		//Destructor
		virtual ~ThreadPool();

		//start the pool
		void start();

		//stop the pool
		void shutdown();

		//shutdown after jobs are done
		void shutdownGracefully();
		
		//do the job of F
		template<class F> void execute(F f)
		{
			ioService.post(f);
		};

	protected:
		//I/O sync loop
		boost::asio::io_service ioService;

		//Thread container
		boost::thread_group pool;

		//Worker to inform ioService when it has work to do
		boost::asio::io_service::work* worker;
				
		//Pool size
		int size;

		//stop ioService
		void _shutdown();
	};

}  //namespace tpool

#endif //_THREADPOOL_H_