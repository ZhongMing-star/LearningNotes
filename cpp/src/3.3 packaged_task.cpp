#include <iostream>
#include <future>

using namespace std;

int sum(int a, int b){ return a + b; }

int main()
{
    packaged_task<int(int, int)> task(sum);
    future<int> fut = task.get_future();

    thread t(move(task), 1, 2);
    t.join();

    int result = fut.get();
    cout << "Result = " << result ;
}