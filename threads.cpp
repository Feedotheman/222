#include <thread>
#include <iostream>
// v2
#include <vector>
// v3
#include <mutex>
using namespace std;

mutex coutMutex;

void print_hello(int id, double& sum)
{
    coutMutex.lock();
    sum+=id;
    cout << "Thread "<< id << ": " << sum << endl;
    coutMutex.unlock();
}

int main()
{
    double sum = 0;
    // version 2
    vector <thread> threads;
    for (int i=0; i<8; i++)
    {
        threads.push_back(thread(print_hello, i, ref(sum)));
    }
    
    coutMutex.lock();
    cout << "Main thread" << endl;
    coutMutex.unlock();
    
    for(auto& th:threads)
    {
        if(th.joinable())
            th.join();
    }

    cout << "sum = " << sum << endl;

    // version1
    // cout << "Main thread" << endl;
    // thread thread2(print_hello);
    // thread2.join();
}