//
//  Project: Executor
//  Created:     17/07/2014
//  Author:      Cédric Verstraeten
//  Mail:        hello@cedric.ws
//  Website:     www.cedric.ws
//
//  The copyright to the computer program(s) herein
//  is the property of cedric.ws, Belgium.
//  The program(s) may be used and/or copied.
//
/////////////////////////////////////////////////////

#include "Executor.h"
using namespace kerberos;

// Helper function
void static sleep(int sec)
{
	#ifdef _WIN32
		_sleep(sec*1000);
	#endif
	#ifdef LINUX
		usleep(sec*1000000);
	#endif
}

// Class with a member function
struct Foo
{
	bool execute()
	{
		std::cout << "I (Foo) will execute this function." << std::endl;
		sleep(1);
		return true;
	}
};

// Static function
static void execute()
{
	std::cout << "I (static function) will execute this function" << std::endl;
	sleep(1);
}

int main(int argc, char** argv)
{
	// Executor can execute member functions of an object.
	Executor<Foo> executeFoo;
	executeFoo.setAction(new Foo(), &Foo::execute);
	executeFoo.setInterval("once in 10 executions");

	// Executor can execute static functions.
	/*Executor executeStatic;
	executeStatic.setAction(&execute);
	executeStatic.setInterval("2 times in 10 executions");*/

	while (true)
	{
		executeFoo();
		//executeStatic();
	}

    return 0;
}

