#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Foo
{
public:

    class MyTimer {
    public:
        virtual void scheduleInASeconds(const std::function<void()>& cb) = 0;
    };

private:
    MyTimer& m_mt;

public:
    Foo(MyTimer& mt)
        : m_mt(mt)
    {
        m_mt.scheduleInASeconds(std::bind(&Foo::callback, this)); // 1 way
        m_mt.scheduleInASeconds([this](){ callback(); }); // another way
    }

private:
    void callback() { std::cout << "hello pavlos" << std::endl; };
    
    
};

class MyTimerImpl : public Foo::MyTimer {
    std::vector<std::function<void()>> m_cb;
public:
    virtual void scheduleInASeconds(const std::function<void()>& cb) override
    {
        m_cb.push_back(cb);
    }

    void call()
    {
        for (auto& i: m_cb) {
            i();
        }
    }
};

int main()
{
    MyTimerImpl impl;
    Foo foo(impl);

    // sleep(1);
    impl.call();
}
