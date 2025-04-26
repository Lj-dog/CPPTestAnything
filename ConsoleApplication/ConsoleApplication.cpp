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

#pragma region 类（含字段及虚方法，纯虚方法，非虚方法），接口（纯抽象类）多继承问题
class GrandParent_A
{
public:
	std::string a;
	GrandParent_A()
	{
		a = "GrandParent_A";
		std::cout << "GrandParent_A Constructed" << std::endl;
	}
	//static void Print()
	//{
	//	std::cout << "is GrandParent_A Function" << std::endl;
	//}
	void Print()
	{
		std::cout << "is GrandParent_A Function" << std::endl;
	}
	virtual void PrintVirtual()
	{
		std::cout << "is GrandParent_A virtual Function" << std::endl;
	}

	virtual void PrintPureVirtual() = 0;
};

class Parent_B :public GrandParent_A
{
public:
	std::string b;
	Parent_B()
	{
		b = "Parent_B";
		std::cout << "Parent_B Constructed" << std::endl;
	}
	virtual void PrintVirtual()
	{
		std::cout << "is Parent_B virtual Function" << std::endl;
	}
	void PrintPureVirtual() override {
		std::cout << "is Parent_B Purevirtual Function" << std::endl;

	}
};

class Parent_C :public GrandParent_A
{
public:
	std::string c;
	Parent_C()
	{
		c = "Parent_C";
		std::cout << "Parent_C Constructed" << std::endl;
	}
	virtual void PrintVirtual()
	{
		std::cout << "is Parent_C virtual Function" << std::endl;
	}
	void PrintPureVirtual() override {
		std::cout << "is Parent_C Purevirtual Function" << std::endl;
	}
};

class GrandSon_D :public Parent_B, public Parent_C
{
public:
	std::string d;
	GrandSon_D() {
		d = "GrandSon_D";
		std::cout << "GrandSon_D Constructed" << std::endl;
	}
	//virtual	void PrintVirtual()
	//{
	//	std::cout << "is GrandSon_D override Function" << std::endl;
	//}

};

#pragma region 虚继承
class Parent_VirtualB : virtual public GrandParent_A
{
public:
	std::string b;
	Parent_VirtualB()
	{
		b = "Parent_VirtualB";
		std::cout << "Parent_VirtualB Constructed" << std::endl;
	}
	//virtual void PrintVirtual()
	//{
	//	std::cout << "is Parent_VirtualB virtual Function" << std::endl;
	//}
	void PrintPureVirtual() override {
		std::cout << "is Parent_VirtualB Purevirtual Function" << std::endl;

	}
};

class Parent_VirutalC :virtual public GrandParent_A
{
public:
	std::string c;
	Parent_VirutalC()
	{
		c = "Parent_VirutalC";
		std::cout << "Parent_VirutalC Constructed" << std::endl;
	}
	//virtual void PrintVirtual()
	//{
	//	std::cout << "is Parent_VirutalC virtual Function" << std::endl;
	//}
	void PrintPureVirtual() override {
		std::cout << "is Parent_VirutalC Purevirtual Function" << std::endl;
	}
};

class GranSon_VirtualD :public Parent_VirtualB, public Parent_VirutalC
{

public:
	std::string d;
	GranSon_VirtualD() {
		d = "GranSon_VirtualD";
		std::cout << "GranSon_VirtualD Constructed" << std::endl;
	}
	void PrintPureVirtual() override {
		std::cout << "is GranSon_VirtualD Purevirtual Function" << std::endl;
	}
};
#pragma endregion


#pragma region 接口实现
class IGrandP_A
{
public:
	virtual void Print() = 0;
	IGrandP_A()
	{
		std::cout << "IGrandP_A Constructed" << std::endl;
	}
};

class IParent_B :public IGrandP_A
{
public:
	//virtual void Print() = 0;
	virtual void Print()
	{
		std::cout << "is IParent_B function" << std::endl;
	}
	IParent_B()
	{
		std::cout << "IParent_B Constructed" << std::endl;

	}
};

class IParent_C :public IGrandP_A
{
public:
	//virtual void Print() = 0;
	virtual void Print()
	{
		std::cout << "is IParent_C function" << std::endl;
	}
	IParent_C()
	{
		std::cout << "IParent_C Constructed" << std::endl;

	}
};

class GrandSon_ID :public IParent_B, public IParent_C
{
public:
	void Print()
	{
		std::cout << "is GrandSon_ID function" << std::endl;
	}
	GrandSon_ID()
	{
		std::cout << "GrandSon_ID Constructed" << std::endl;

	}
};

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
	//SolidersBase* aa;
	////SolidersBase bb;
	//SolidersBase* solider1 = new Cook(RANK::OR_1);
	//SolidersBase* solider2 = new Army(RANK::OR_2);
	//Hunter hunter;

	//std::cout << "solider1:" << solider1->GetRank() << "; " << "solider2:" << solider2->GetRank() << std::endl;
	//SomeOneShoot(&hunter);
	//SomeOneShoot((IShooting*)(Army*)(solider2));
	//if (auto* ifun = dynamic_cast<IShooting*>(solider1))
	//	SomeOneShoot(ifun);
	//else
	//{
	//	std::cout << "don't know shooting" << std::endl;
	//}
	//if (auto* ifun = dynamic_cast<IShooting*>(solider2))
	//	SomeOneShoot(ifun);
	//else
	//{
	//	std::cout << "don't know shooting" << std::endl;
	//}

#pragma endregion

#pragma region 类（含字段及抽象方法，非抽象方法），接口（纯抽象类）多继承问题
	GrandSon_D d;
	//std::cout << d.a << std::endl; //"GrandSon Da”不明确
	std::cout << d.Parent_B::a << std::endl;
	std::cout << d.Parent_C::a << std::endl;
	//d.Print(); //"GrandSonD::Print"不明确
	d.Parent_C::Print();
	d.Parent_B::Print();
	//d.PrintVirtual(); //"GrandSonD::PrintVirtual不明确
	d.Parent_C::PrintVirtual();
	d.Parent_B::PrintVirtual();
	//d.PrintPureVirtual(); //"GrandSonD:PrintPureVirtual"不明确
	d.Parent_C::PrintPureVirtual();
	d.Parent_B::PrintPureVirtual();

	std::cout << "--------------------------------" << std::endl;

	GrandSon_ID id;
	id.Print();
	std::cout << "--------------------------------" << std::endl;

	GranSon_VirtualD vd;
	std::cout << vd.a << std::endl;
	vd.Print();
	vd.PrintVirtual();
	vd.PrintPureVirtual();

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
