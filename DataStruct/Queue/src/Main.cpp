#include <iostream>
#include "LinkQueue.hpp"


using namespace queue;

int main(int argc, char* argv[])
{

    LinkQueue lqueue;

    lqueue.printfQueue();

    lqueue.push(1u);
    lqueue.printfQueue();
    lqueue.push(2u);
    lqueue.printfQueue();
    lqueue.push(3u);
    lqueue.printfQueue();

    std::cout << "First node value: "<< lqueue.front() << "    Last node value: "<< lqueue.back() << std::endl;

    lqueue.pop();
    lqueue.printfQueue();
    lqueue.pop();
    lqueue.printfQueue();
    lqueue.pop();
    lqueue.printfQueue();

    return 0;
}
