#include <iostream>
#include <thread>

using namespace std;

void threadProcessing()
{
    cout << "subthread threadProcessing begin " << endl;
}

int main()
{
    // 创建并启动新线程
    thread t(threadProcessing);

    cout << "main process begin " << endl;

    // 等待线程运行结束
    t.join();

    return 0;
}