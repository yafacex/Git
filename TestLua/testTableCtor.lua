function retfunc( ... )
	-- body
	return {};
end

function testTableConstructor( ... )
	-- body
	local a = 1;local b = 2;
	local tableint = {0,1,2,3,4,5,6,7};
	local table = { a = 1, b = 2 , c = 3}
	-- local tableStr = { "a" = 1, "b" = 2 , "c" = 3}
	print(" retfunc 's return value is Table Address , if print , is table:0x???????? " );
	local tableFuncKey = { [retfunc()] = 1, [a] = 2 , [a+b] = 3}
	show(tableFuncKey);
end

function show( table )
	-- body
	for k,v in pairs(table) do
		print(k,v)
	end
end

function sampleKeyList( ... )
	-- body
	local list = "1"
	local table = { a = 1, b = 2 , c = 3}
	for k,v in pairs(table) do
		list = list .. k;	
	end
	print(list);
end

function sampleArray( ... )
	-- body
	local arr = {1,2,3}
	table.insert(arr,#arr+1,100);
	print("maxn \tis" ..  table.maxn(arr));
	print("length \tis" ..  #arr);
	show(arr);
	print("There are two ways to get table length : table.maxn  and  #")
end

-- testTableConstructor();
-- sampleKeyList();
sampleArray();
