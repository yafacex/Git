function retfunc()
	return {};
end

function testForInt( ... )
	-- body
	for i=1,10 do
		print(i)
	end
end

function testForIntStep( ... )
	-- body
	for i=1,10,2 do
		print(i)
	end
end

function testForFloat( ... )
	-- body
	for i=1.1,10.1 do
		print(i)
	end
end

function testForFloatStep( ... )
	-- body
	for i=1.1,10.1,0.5 do
		print(i)
	end
end

function testForString( ... )
	-- body
	print("Follwing cause lua crash");
	for i="a","b" do
		print(i)
	end
end

function testForString( ... )
	-- body
	print("Follwing cause lua crash");
	local a = "aa" ; b = "bb";
	for i=a,b do
		print(i)
	end
end

function testWhile( ... )
	-- body
	local  x = 1
	while x < 10 do
		print(x);
		x=x+1;
	end
end

function testDoWhile( ... )
	-- body
	printf("no do while , Compile Error");
	-- local x = 1
	-- do
	-- 	print(x);
	-- 	x = x + 1;
	-- end while(x < 10)
end

function testRepeat( ... )
	-- body
	local x = 1
	repeat  
		print(x)
		x = x + 1;
	until x == 10


end

function testFori( ... )
	-- body
	print("Lua index starts from 1");
	local tableint  = {0,1,2,3,4,5,6,7};
	for i,v in ipairs(tableint) do
		print(i,v)
	end
end

function testForp( ... )
	-- body
	local a = 1;local b = 2;
	local tableint = {0,1,2,3,4,5,6,7};
	local table = { a = 1, b = 2 , c = 3}
	-- local tableStr = { "a" = 1, "b" = 2 , "c" = 3}
	local tableFuncKey = { [retfunc()] = 1, [a] = 2 , [a+b] = 3}
	print("Lua not allow < \"key\" = val> , Compile Error");
	for k,v in pairs(tableFuncKey) do
		print(k,v)
	end
end
print("begin");
-- testForInt();
-- testForFloat();
-- testForIntStep();
-- testForFloatStep();
-- testForString();
-- testWhile();
-- testRepeat();
-- testFori();
testForp();
print("end");
