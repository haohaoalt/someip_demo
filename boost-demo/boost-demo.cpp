/*
 * @Author: https://github.com/haohaoalt
 * @Date: 2023-08-16 15:38:38
 * @LastEditors: haohaoalt haohaoalt@163.com
 * @LastEditTime: 2023-08-16 15:38:38
 * @FilePath: /someip_demo/boost-demo/boost-demo.cpp
 * @Description: 
 * Copyright (c) 2023 by haohaoalt@163.com, All Rights Reserved. 
 */
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

boost::mutex mutex;

void print_block(int n, char c)
{
    // critical section (exclusive access to std::cout signaled by locking mtx):
    mutex.lock();
    for (int i = 0; i < n; ++i)
    {
        std::cout << c;
    }
    std::cout << '\n';
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    boost::thread thread1(&print_block, 300, '*');
    boost::thread thread2(&print_block, 300, '$');

    thread1.join();
    thread2.join();

    return 0;
}