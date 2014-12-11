#Executor

Executor is a class that executes a function at specific times/intervals by using human language and a function pointer. This is helpfull because sometimes you don't want to execute a function every time, and only once in a period. In most cases you will end with following solution:

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

which is very nast if you would do it often. If you are in this situation a lot, Executor can help you to keep your code clean.

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