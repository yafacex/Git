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

-- testFuncAsValue();
testClosureFunc();




