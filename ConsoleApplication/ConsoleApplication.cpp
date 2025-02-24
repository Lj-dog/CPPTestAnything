// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <format>
#include <string>

#pragma region 尝试返回局部类型
class B
{
public:
	void Hello()
	{
		std::cout << "Hello B";
	}
};

class A
{
public:
	B& Get()
	{
		B b;
		return b;
	}
};

#pragma endregion

#pragma region make_unique与new区别


class Diff_New_Make_unique
{
public:
	void* operator new(std::size_t size)
	{
		auto p = std::malloc(size);
		std::cout << "new({" << size << "}) at {" << p << "}" << std::endl;
		return p;
	}

	void operator delete(void* p)
	{
		std::cout << "delete({" << p << "})" << std::endl;
		std::free(p);
	}
private:

	//std::unique_ptr<int> num;

public:
	int num;
	Diff_New_Make_unique(bool isBuild, int num);
	~Diff_New_Make_unique();

};

Diff_New_Make_unique::Diff_New_Make_unique(bool isBuild, int num)
{
	std::cout << "Construction" << num << std::endl;
	this->num = num;
	//this->num = new int(num);
	//this->num = std::move(std::unique_ptr<int>(new int(num)));
	if (!isBuild)
		throw "some error";
}

Diff_New_Make_unique::~Diff_New_Make_unique()
{
	std::cout << "Destruct" << num << std::endl;
	//delete num;
}

void doSomething(std::unique_ptr<Diff_New_Make_unique> a,
	std::unique_ptr<Diff_New_Make_unique> b)
{
	std::cout << (*a).num << std::endl;
	std::cout << (*b).num << std::endl;
}
#pragma endregion

#pragma region unique_ptr的其他用法 reset release std::move

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
#pragma endregion

#pragma region 抽象与接口，士兵与猎人，开枪
enum RANK
{
	OR_1,
	OR_2,
};
class SolidersBase
{
public:

	SolidersBase(RANK rank) :rank(rank) {}
	virtual RANK GetRank() = 0;
protected:
	RANK rank;
	std::string Department;
public:
	std::string name;
};

class IDuty
{
public:
	virtual std::string GetDuty() = 0;
};

class Cook :public SolidersBase, public IDuty
{
public:
	Cook(RANK r) :SolidersBase(r) {}
	//Cook(RANK r):rank(r){}
	RANK GetRank() override { return rank; }
	std::string GetDuty() { return "Cook"; }

};

class IShooting
{
public:
	virtual void Shooting() = 0;
};



class Army :public SolidersBase, public IDuty, public IShooting
{
public:
	Army(RANK r) :SolidersBase(r) {}
	RANK GetRank() override { return rank; }
	std::string GetDuty() { return "Fight"; }
	void Shooting() override { std::cout << "Solider shoot" << std::endl; }
};

class Hunter :public IShooting
{
public:
	void Shooting() override {
		std::cout << "Hunter shoot" << std::endl;
	}

};

void SomeOneShoot(IShooting* shooter)
{
	shooter->Shooting();
}


#pragma endregion
int main()
{
	std::cout << "Hello World!\n";

#pragma region 尝试返回局部类型
	//A a;
	//B b = a.Get();
	//b.Hello();
#pragma endregion

#pragma region make_unique与new区别

	//try
	//{
	//	//doSomething(std::unique_ptr<Diff_New_Make_unique>(new Diff_New_Make_unique(false, 1))
	//	//	, std::unique_ptr<Diff_New_Make_unique>(new Diff_New_Make_unique(true, 2)));

	//	doSomething(std::make_unique<Diff_New_Make_unique>(false,1)
	//		, std::make_unique<Diff_New_Make_unique>(true,2));


	//}
	//catch (...)
	//{
	//	std::cout << "Exception" << std::endl;
	//}
#pragma endregion

#pragma region unique_ptr的其他用法 reset release std::move
	//// std::make_unique是c++14才有
	//std::unique_ptr<Foo> pf = std::make_unique<Foo>(6);
	//// unique_ptr的复制构造函数和拷贝构造函数是删除了的，这样保证了对象独占，如果不是独占，那么跟shared_ptr
	//// 就是一样的功能了。
	//// std::unique_ptr<Foo> pf1 = pf;  // compile error

	//// 按值传参，会有拷贝问题，同上
	//// auto p = change_a(pf);   //compile error

	//auto p = change_a(std::move(pf));
	//std::cout << "get_a = " << p->get_a() << std::endl;
	//if (!pf)
	//{
	//	std::cout << "pf is nullptr" << std::endl;
	//}
	////owner transfer from function
	//std::unique_ptr<Foo> pf2 = std::make_unique<Foo>(11);
	//std::unique_ptr<Foo> p2 = change_a(std::move(pf2));
	//std::cout << "get_a = " << p2->get_a() << std::endl;
	//if (!pf2)
	//{
	//	std::cout << "pf2 is nullptr" << std::endl;
	//}

	////使用reset
	//pf2.reset(new Foo(12));
	//std::cout << "pf2 is not null: " << pf2->get_a() << std::endl;

	////release获取原始指针
	//Foo* ff = pf2.release();
	//if (!pf2)
	//{
	//	std::cout << "pf2 is nullptr" << std::endl;
	//}
	//std::cout << "ff is not null: " << ff->get_a() << std::endl;

	//return 0;
#pragma endregion

#pragma region 抽象与接口，士兵与猎人，开枪
	SolidersBase* aa;
	//SolidersBase bb;
	SolidersBase* solider1 = new Cook(RANK::OR_1);
	SolidersBase* solider2 = new Army(RANK::OR_2);
	Hunter hunter;

	std::cout << "solider1:" << solider1->GetRank() << "; " << "solider2:" << solider2->GetRank() << std::endl;
	SomeOneShoot(&hunter);
	SomeOneShoot((IShooting*)(Army*)(solider2));
	if (auto* ifun = dynamic_cast<IShooting*>(solider1))
		SomeOneShoot(ifun);
	else
	{
		std::cout << "don't know shooting" << std::endl;
	}
	if (auto* ifun = dynamic_cast<IShooting*>(solider2))
		SomeOneShoot(ifun);
	else
	{
		std::cout << "don't know shooting" << std::endl;
	}

#pragma endregion

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
