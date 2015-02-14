
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>


using namespace std;
// forward declaration
int factorial(unsigned int);
// a mutex will be needed to ensure proper shared data access
std::mutex myMutex;
// the function that will call the computation.
void driver(unsigned int n)
{
    unsigned int result = factorial(n);
    lock_guard<std::mutex> guard(myMutex);
    cout << n << "! = " << result << endl;
}
// classic recursion implementation of the n! function.
int factorial(unsigned int n)
{
    if(n < 1)
    {
        return 1;
    }
    else
        return n*factorial(n-1);
}
// tell the thread t to join the main thread
template <class T>
T* op_join(T* t)
{
    t->join();
    return t;
}
/*
// before templetization:
std::thread* op_join(std::thread* t)
{
    t->join();
    return t;
}
*/
// a function that deletes a thread pointer
template <typename T>
void op_delete(T* t)
{
    if(t)
    {
        delete t;
        t = nullptr;
    }
}
/*
// before templetization:
void op_delete(std::thread* t)
{
    if(t)
    {
        delete t;
        t = nullptr;
    }
}
*/
int main()
{
    // a vector of threads where threads will be stored.
    vector<thread*> threadsList;
    // input number of threads to generate
    unsigned int n;
    cout << "Input number of threads to create (max = 10): ";
    cin >> n;
    // negative numbers are not allowed, change sign if necessary
    if(n < 0)
    {
        n *= -1;
    }
    // the maximum number of threads is 10
    if(n > 10)
    {
        n = 10;
    }
    // start generating threads and assign them numbers "i+1" to compute (i+1)!
    for(unsigned int i = 0; i < n; i++)
    {
        threadsList.push_back(new thread(driver, i+1));
    }
    // make threads join the main thread
    transform(threadsList.cbegin(), threadsList.cend(), threadsList.begin(), op_join<std::thread>);
    // delete pointers and free memory
    for_each(threadsList.begin(), threadsList.end(), op_delete<std::thread>);

    return 0;
}
