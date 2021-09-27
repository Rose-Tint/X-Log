#ifndef TESTING_HPP
#define TESTING_HPP


class TestBase
{
    protected:
    static int idt;
    TestBase() = default;
    virtual bool run() = 0;

    public:
    TestBase(const TestBase&) = delete;
    TestBase(TestBase&&) = delete;
    void operator=(const TestBase&) = delete;
    void operator=(TestBase&&) = delete;
}

#endif