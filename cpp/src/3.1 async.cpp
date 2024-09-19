#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

int sum(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));
    return a + b;
}

int main()
{
    future<int> func = async(sum, 1,1);
    cout << "1 + 1 = " << func.get() << endl;

    return 0;
}