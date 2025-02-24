// ConsoleApplicationTemp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <memory>
#include <iostream>
#include <utility>

class Foo {

public:
    Foo() = default;
    Foo(int a) :_a(a) {}
    ~Foo() {}
    int get_a() {
        return _a;
    }
    void set_a(int a) {
        _a = a;
    }
private:
    int _a;

};

std::unique_ptr<Foo> change_a(std::unique_ptr<Foo> f)
{
    f->set_a(10);
    return f;
}

int main()
{
    // std::make_unique是c++14才有
    std::unique_ptr<Foo> pf = std::make_unique<Foo>(6);
    // unique_ptr的复制构造函数和拷贝构造函数是删除了的，这样保证了对象独占，如果不是独占，那么跟shared_ptr
    // 就是一样的功能了。
    // std::unique_ptr<Foo> pf1 = pf;  // compile error

    // 按值传参，会有拷贝问题，同上
    // auto p = change_a(pf);   //compile error

    auto p = change_a(std::move(pf));
    std::cout << "get_a = " << p->get_a() << std::endl;
    if (!pf)
    {
        std::cout << "pf is nullptr" << std::endl;
    }
    //owner transfer from function
    std::unique_ptr<Foo> pf2 = std::make_unique<Foo>(11);
    std::unique_ptr<Foo> p2 = change_a(std::move(pf2));
    std::cout << "get_a = " << p2->get_a() << std::endl;
    if (!pf2)
    {
        std::cout << "pf2 is nullptr" << std::endl;
    }

    //使用reset
    pf2.reset(new Foo(12));
    std::cout << "pf2 is not null: " << pf2->get_a() << std::endl;

    //release获取原始指针
    Foo* ff = pf2.release();
    if (!pf2)
    {
        std::cout << "pf2 is nullptr" << std::endl;
    }
    std::cout << "ff is not null: " << ff->get_a() << std::endl;

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
