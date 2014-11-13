function afterReturn( ... )
	-- body
	b = "abcd";
	print(b);
	return b;
	-- print("lua BNF not allow code after <return>,Compile Error");
end

function afterBreak( ... )
	-- body
	b = "abcd";
	print(b);
	for i=1,10 do
		print(i)
		break;
		-- print("lua BNF not allow code after <break>,Compile Error");
	end
end

function oneLineDeclare( ... )
	-- body
	local x = 1 , y = 2;
	print("lua BNF not allow oneLineDeclare with ',',Compile Error");
end

print(b);
-- afterReturn();
afterBreak();