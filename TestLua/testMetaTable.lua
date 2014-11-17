function printTable( t )
	if(t == nil) then
		print("table is nil")
		return;
	end
	-- body
	print("\ntable content:{")
	for k,v in pairs(t) do
		print("\t"..k..":"..v)
	end
	print("}\n");
end

function testMetatable( ... )
	-- body
	local totest = {}
	setmetatable(totest,{
		__metatable={nimei = "totest's metatable"}
		});
	local t = getmetatable(totest)
	print("totest metatable is \n");
	printTable(t)
end

function testAdd( ... )
	local ta , tb = {1,2}, {3,4}
	local mt = {
		__add = function ( a,b )
			-- body
			local ret = {}
			for i,v in ipairs(a) do
				ret[i] = v + b[i];
				print("override __add :"..v.."+"..b[i].."="..ret[i]);
			end
			return ret;
		end
		}
	setmetatable(ta,mt)
	local tc = ta + tb;
	printTable(tc);
end

function testNewindex( ... )
	local obj = {};
	print("obj .... ");
	print(obj);
	local mt = {__newindex = 
		function ( tbl,k,v )
	
			print("tbl .... ");
			print(tbl);

			if v == nil then v = "nil" end

			print("\n[[[[[[[[[[\n__newindex:"..k..","..v);
			printTable(tbl);
			local rv = rawget(tbl,k);
			if rv ~= nil then 
				print("reAssign")
				print("raw value of key["..k.."] exists,it is "..rv)
			else 
				print("key["..k.."] not exists yet");
				rawset(tbl,k,v)
			end
			print("]]]]]]]]]]\n");
		end
	};

	local mt2 = {__index = 
		function ( tbl,k )
			print("__index:"..k);
		end
	}

	local mt3 = {__call = 
		function ( tbl,... )
			print("__call:");
			print(tbl);
			tbl.func();
		end
	}

	setmetatable(obj,mt3)
	

	obj["va"] = 100;
	obj["vb"] = 200;
	printTable(obj);
	-- __index/__newindex 是在 get/set 找不到 key 的时候触发的函数
	local testa = obj["vb"]
	obj["va"] = obj["vb"];
	obj["va"] = testa;
	obj["va"] = 500;
	obj["va"] = obj["vx"];
	printTable(obj);

	obj.func = function ()
		-- body
		print("call obj.funcA");
	end 

	obj();
end
-- testMetatable()
-- testAdd()
testNewindex();