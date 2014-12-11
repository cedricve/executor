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

Executor can help you to keep your code clean.

#Usage

You can assign functions and static member functions to a executor.

	Executor execute;

	void doSomething(){}
	execute.setAction(&doSomething);
	execute.setInterval("twice in 4 function calls");

	// call the funcor methode
	execute(); // do nothing
	execute(); // execute function..
	execute(); // do nothing
	execute(); // execute function ..

But you can assign non-static member functions to the executor; this is a little bit complicater because you also need to pass a reference to an existing object (this is something C++ does in the background for you, when call member functions on objects).

	class Foo { void doSomething(){} }
	Foo foo;

	Executor<Foo> execute;
	execute.setAction(&foo, &Foo::doSomething);
	execute.setInterval("twice in 4 times");

	// call the funcor methode
	execute(); // do nothing
	execute(); // execute function..
	execute(); // do nothing
	execute(); // execute function ..

You can specify intervals by using human language:

	// but you can also specify time intervals
	execute.setInterval("four times a day");
	execute.setInterval("once a day");
	execute.setInterval("twice in 10 minutes");
	execute.setInterval("thrice in 120 functions calls");
