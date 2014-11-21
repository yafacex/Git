function  ret_2int( ... )
	-- body
	return {1,2};
end

function testFuncAsValue( ... )
	-- body
	local func = ret_2int;

	local list = func();

	for i=1,#list do
		print(list[i])
	end
end

function testClosureFunc( ... )
	-- body
	local function innerFunc( ... )
		-- body
		print("In inner func");
	end 

	innerFunc();
end

function testPassOneTable( ... )
	-- print("仅传一个table当函数参数时，括号可以省略")
	local function funca(a)
		print("in funca")
	end
	funca{a = 1,b =2, c =3}
end
-- testFuncAsValue();
-- testClosureFunc();
testPassOneTable();




