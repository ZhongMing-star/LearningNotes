#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void independentTherad()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "independentTherad i = " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "independentTherad Finshed !" << endl;
}

void dependedOnMainThread()
{

    thread t = thread(independentTherad);
    t.detach();

    for (int i = 0; i < 5; i++)
    {
        cout << "dependedOnMainThread i = " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "dependedOnMainThread Finshed !" << endl;

}

int main()
{  
    thread t = thread(dependedOnMainThread);
    t.join();
    return 0;
}