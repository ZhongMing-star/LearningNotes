#include <iostream>
#include <future>

using namespace std;

int divide(promise<double> &&prom, int a, int b)
{
    try{
        if (b == 0)
            throw std::runtime_error("Divide by zero exception");
        double result = 1.0 * a / b;
        prom.set_value(result);
    }
    catch(...){
        prom.set_exception(current_exception());
    }
}

int main()
{
    promise<double> prom;
    future<double> fut = prom.get_future();

    thread t(divide, move(prom), 3, 0);
    t.join();

    try{
        double result = fut.get();
        cout << "Result = " << result ;
    }
    catch(const std::exception& e){
        cout << "Exception :" << e.what();
    }
}