#include "pch.h"

using namespace std;

class MyClass
{
public:
	string myName;

	string getName()
	{
		return myName;
	}
};

TEST(TestMyClass, myName) {
	MyClass myClass;
	myClass.myName = "example";

	EXPECT_EQ("example", myClass.myName);
	EXPECT_EQ("example", myClass.getName());
}