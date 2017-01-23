#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
class Counter {
public:
    Counter() : m_value(0) {}
    int getValue()
    {
        return m_value;
    }

    void increment()
    {
        m_mutex.lock();
        ++m_value;
        m_mutex.unlock();
    }

    void decrement()
    {
        m_mutex.lock();
        --m_value;
        m_mutex.unlock();
    }
private:
    std::mutex m_mutex;
    int m_value;
};

int main()
{
    Counter counter;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread([&](){
            for (int i = 0; i < 10000; ++i)
            {
                counter.increment();
            }
        }));
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    std::cout << counter.getValue() << std::endl;
    system("pause");
    return 0;
}