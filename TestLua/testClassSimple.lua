trueGlobalTable = {}
setmetatable(_G, {

	__newindex = function(t, k, v)
		if rawget(trueGlobalTable, k) then
			assert(false, "Global Variable \"" .. tostring(k) .. "\" Already Defined Before !")
		end
		trueGlobalTable[k] = v
		--写入类名
		print("_G type",type(v))
		if type(v) == "table" and v then 
			v.___classname = tostring(k) or "unkown class"
			print("_G classname:",v.___classname)
		end
	end,

	__index = function(t, k)
		return trueGlobalTable[k]
	end
})

function debug:printObject(obj,name)
  if name then 
    print("TABLE["..name.."]");
  else
  	print("TABLE\n")
  end

  local function _printTab(n)
    -- io.write("[LUA-print] ")
    for i=1,n do
      io.write("  ")
    end
  end 

  local function _print( obj ,depth)
    if obj == nil then return end

    if type(obj) == "table" then
      if obj.class and obj.class.___classname then
        io.write("<"..obj.class.___classname..">\n")
       else
       	io.write("<"..tostring(obj)..">")
      end
      if depth == 1  then _printTab(depth) end
      io.write("{\n")
      for k,v in pairs(obj) do
        _printTab(depth+1)
        io.write(k.." = ")
        _print(v,depth+1)
        io.write("\n")
      end
      _printTab(depth)
      io.write("}")
    elseif type(obj) == "string" then
      io.write("\""..obj.."\"")
    elseif type(obj) == "boolean" then
      io.write(tostring(obj))
    else
      if obj then
        io.write(tostring(obj))
      else
        io.write("nil")
      end
    end
  end

  local depth=0;
  io.open("stdin")
  _printTab(depth)
  _print(obj,depth)
  io.write("\n\n")
  io.close()
end

function tba(level,isMore)
  local lv = 2;
  while true do

    local info = debug.getinfo(lv,"Sln");
    if not info then break end

    if lv >= level then
      print("<"..lv..">FUNC:[".. (info.name or "NULL").."]\tFILE:" .. info.short_src .. "["..info.currentline.."]");
      if lv == -1 or lv == level or (isMore and lv > level) then
        if info.name ~= "require" and info.name ~= "self" then 
          -- debug:printLocal(lv+1,-1,true);
        end
      end
    end

    lv = lv + 1
  end
end 


local _class={}
function class(super, classname)

	-- local class_type = { ctor = false, super = super}    -- 'ctor' field must be here
	local class_type = {};-- = {super = super}    -- 'ctor' field must be here
	local vtbl = {}
	_class[class_type] = vtbl
  	class_type.___classname = classname;

    -- 类实例get/set重定向到 虚函数表 的哈希表
	setmetatable(class_type, {
		__newindex= function(t,k,v)

			if rawget(vtbl, k) then
				print(debug.traceback());
				assert(false, "Class 's Memeber \"" .. tostring(k) .. "\" Already Defined Before, This May Cause Error !")
			end
			vtbl[k] = v 

			print("\n##","ClassSetBegin :　",k,tostring(v))
			print("My class_type is: ",tostring(class_type))
			debug:printObject(vtbl,"My vtbl")
			debug:printObject(class_type,"My Table")
			debug:printObject(_class[super],"Super's vtbl")
			print("@@","ClassSetEnd\n")

			if k == "___classname" then
				print("mark",tostring(class_type).." = "..v)
			end
		end,			
		__index = function(t,k) 
			print("\nBefore Vtbl Get :",k)
			local ret = vtbl[k]
			print("After Vtbl Get\n")
			return ret
		end,
	})

	class_type.super = super;

    -- 虚函数表重定向 get , 直接从super的虚函数表里拿值(函数) 
	if super then
		setmetatable(vtbl, { 
			__index= function(t, k)
				--  1]	注意class_type.new里把__index=_class[class_type]指向了这里（_class[class_type]其实就是vtbl），
				--		所以Object的get方法们会走这里
				--	2]	但是__index=_class[class_type]这个写法，还是只有找不到key的时候才会走这里
				--	3]	注意class_type.new里没把__newindex覆写，所以self.var=1还是走了Object的rawset,
				--		所以get成员变量不会触发这里（如果key找到了）,走的rawget
				--  4]	函数声明的时候其实是对Class进行的set,声明进来的函数们存在vtbl里了，
				--		所以Object的rawget找不到，会走到这里
				--	5]	下面这个local ret = _class[super][k]是精髓，这里虽然没写子类找不到func去父类找的逻辑，
				--		但是__index的特性里隐含了。一句_class[super][k]直接就向上遍历了父类，直到找到key为止。
				if k and _class[super] then
				    local ret = _class[super][k]
				    print("\n\nDo   Super",k,
				    	",\nRet is",tostring(ret),
				    	",\nMy class_type is:",tostring(class_type),
				    	",\nMy Vtbl is:",tostring(t),
				    	",\nSuper class_type is:",tostring(super),
				    	"\n")
				    -- if ret then
				    -- 	debug.debug()
				    -- end
				    return ret
				else 
					print("No Super")
					return nil 
				end
			end
		})
	end
    
    class_type.new = function(...)
        local obj = { class = class_type }
		local locals = {}	
        setmetatable(obj, { 
			__index = function (t,k)
				print("Obj get:",k)
				 local r = _class[class_type][k]
				 if not r then
				 	return locals[k];
				 else
				 	return r;
				 end
			end,
			__newindex = function (t,k,v)
				print("Obj set:",k,tostring(v))
				locals[k] = v
				if k == "var11" then
					debug.debug()
				end
			end
		})
        
        -- 倒序构造
        print("Begin new()")
        local inherit_list = {}
		local class_ptr = class_type
		while class_ptr do
			if class_ptr.ctor then table.insert(inherit_list, class_ptr) end
			class_ptr = class_ptr.super
		end
		local inherit_length = #inherit_list
		if inherit_length > 0 then
		    for i = inherit_length, 1, -1 do inherit_list[i].ctor(obj, ...) end
		end
        
        print("End new()")
        obj.class = class_type              -- must be here, because some class constructor change class property.

        return obj
    end
	
	return class_type
end

function typeTableClass(theTable)
	if type(theTable) and theTable.class and theTable.class.___classname then
		return theTable.class.___classname
	end
	return "";
end

----------------------------------------------
--- YafaceX Test
----------------------------------------------
function testInherit_3depth()
	classA = class();
	function classA:func()
		print("classA:func");
	end
	function classA:ctor()
		self.var = 1
	end


	classB = class(classA);
	function classB:func()
		print("classB:func "..self.var);
	end
	function classB:ctor()
		-- self.var = 2
	end


	classC = class(classB)
	-- function classC:func()
	-- 	print("classC:func");
	-- end
	function classC:ctor()
		-- self.var = 3
	end


	print("\n\n\n\tInitOver\n\n\n")
	local a = classA.new();
	local b = classB.new();
	local c = classC.new();
	print("\n\n\n\tCtorOver\n\n\n")
	-- a:func();
	-- b:func();
	print("Before c:func()")
	c:func();
	print("After c:func()")
	c.var11 = nil
	print("After nil")

end

testInherit_3depth();



