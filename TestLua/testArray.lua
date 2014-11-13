function  ret_2int( ... )
	-- body
	return {1,2};
end
function  ret_3int( ... )
	-- body
	return {1,2,3};
end
function  ret_4int( ... )
	-- body
	return {1,2,3,4};
end

function show(x)
	-- body
	print("Content")
	for i=1,#x do
		print(x[i])
	end
end

local x = {9};
for i,v in ipairs(ret_3int()) do
	table.insert(x,#x+1,v);
end

show(x)

table.remove(x,#x,1)

show(x)

print("length is\t" .. #x)

