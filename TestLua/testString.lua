function testStringFunc( ... )
	-- body
	local x = "abcdefgcme"
	print("The String is\t" .. x);
	print("# is\t" .. #x);
	print("length is\t" .. string.len(x));

	local index = -2;
	print("string.byte at " .. index .. " is\t" .. string.byte(x,index));
	local char = 97
	print("string.char for " ..char.. " is\t" .. string.char(char));

	-- print("string.dump for me is\t" .. string.dump(testStringFunc))

	local b,e = string.find(x,"abc",1,true)
	print("string.find for \"abc\" is\t" ..  b .. "," .. e);
	print("string.sub for " ..b.. "," ..e.." is\t" .. string.sub(x,b,e));


	print("string.match for \"cde\" is\t" .. string.match(x,"cde"));
	-- print("string.gmatch for \"c%we\" is\t" .. string.gmatch(x,"c(%w+)e"));


	print("string.gmatch return function:builtin#88 !!!!!!!!!!!!!!!!");


	t = {}
    s = "from=world, to=Lua"
    print("gmatch return is");
    print(string.gmatch(s, "(%w+)=(%w+)"));
     for k, v in string.gmatch(s, "(%w+)=(%w+)") do
       t[k] = v
       print(k .. "," .. v)
     end

	x = string.gsub("home = $HOME, user = $USER", "%$(%w+)", "woqu")
	print(x)
	print("os.getenv is function:builtin#124!!!!!!!!");
	
	x = string.gsub("hello_&world_&nidaye_", "(%w+_)&(%w+_)&(%w+_)", "%0 %3 %1 %2")
	print("gsub support awk-column operation , by gsub ()()() %n %n %n !!!!!!!!!!");
	print(x);
	
	x = string.gsub("hello world from Lua", "(%w+)%s*(%w+)", "%2 %1")
	print(x);
	
	local t = {name="lua", version="5.1"}
    x = string.gsub("$name-$version.tar.gz", "%$(%w+)", t)
    print(x);
end

testStringFunc();