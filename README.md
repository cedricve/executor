#Executor

Executor is a class that executes a function at specific times/intervals by using human language and a function pointer. This is helpful because sometimes you don't want to execute a function every time, and only once in a period. In most cases you will end with following solution:

	int i = 0;
	while(true)
	{
		if(i == 1000)
		{
			.. do function call	
			i = 0;
		}
		i++;
	}

Executor can help you to keep your code clean.

#Installation

Make sure you have a C++ compiler and cmake is installed. You can build the project with following command:

##Linux / OSX

Make sure you are at the root of the Executor folder.

	mkdir build && cd build && cmake .. && make

##Windows

* install the [cmake](http://www.cmake.org/download/) executable
* open the cmake GUI and select the source and build directory
* press the configure button
* press the generate button
* open the .sln file with Visual Studio (you can find it in the build directory)
* build the project
* execute the binary

#Usage

You can assign **void** functions, static **void** member functions and non-static **void** member functions to an executor.

Non-static member functions are a little bit complicater because you also need to pass a reference to an existing object (this is something C++ does in the background for you, when call member functions on objects).

	// Executor can execute member functions of an object.
	Executor<Foo> executeMember;
	executeMember.setAction(new Foo(), &Foo::execute);
	executeMember.setInterval("once in 10 executions");

	// Executor can execute static member functions of an object.
	Executor<> executeStaticMember;
	executeStaticMember.setAction(&Foo::staticExecute);
	executeStaticMember.setInterval("thrice in 10 executions");

	// Executor can execute static functions.
	Executor<> executeStatic;
	executeStatic.setAction(&execute);
	executeStatic.setInterval("2 times in 10 executions");

	while (true)
	{
		executeMember();
		executeStatic();
		executeStaticMember();
	}

You can specify intervals by using human language:

	// but you can also specify time intervals
	execute.setInterval("four times a day");
	execute.setInterval("once a day");
	execute.setInterval("twice in 10 minutes");
	execute.setInterval("thrice in 120 functions calls");
