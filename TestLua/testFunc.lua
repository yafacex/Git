function  ret_2int( ... )
	-- body
	return {1,2};
end

local func = ret_2int;

local list = func();

for i=1,#list do
	print(list[i])
end
