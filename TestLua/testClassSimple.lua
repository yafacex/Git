trueGlobalTable = {}
setmetatable(_G, {

	__newindex = function(t, k, v)
		if rawget(trueGlobalTable, k) then
			assert(false, "Global Variable \"" .. tostring(k) .. "\" Already Defined Before !")
		end
		trueGlobalTable[k] = v
		--写入类名
		print("type",type(v))
		if type(v) == "table" and v then 
			v.___classname = tostring(k) or "unkown class"
			print("classname:",v.___classname)
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

  local depth=1;
  io.open("stdin")
  _printTab(depth)
  _print(obj,depth)
  io.write("\n")
  io.close()
end

local _class={}
function class(super, classname)

	local class_type = { ctor = false, super = super}    -- 'ctor' field must be here
	local vtbl = {}
	_class[class_type] = vtbl
  	class_type.___classname = classname;
    -- class_type is one proxy indeed. (return class type, but operate vtbl)
	setmetatable(class_type, {
		__newindex= function(t,k,v)

			-- Check If Already Defined !
			if rawget(vtbl, k) then
				print(debug.traceback());
				assert(false, "Class 's Memeber \"" .. tostring(k) .. "\" Already Defined Before, This May Cause Error !")
			end
			debug:printObject(vtbl,k)
			debug:printObject(t,k)
			debug:printObject(class_type,k)
			vtbl[k] = v 
		end,			
		__index = function(t,k) 

			return vtbl[k] 
		end,
	})

    -- when first invoke the method belong to parent,retrun value of parent
    -- and set the value to child
	if super then
		setmetatable(vtbl, { 
			__index= function(t, k)

				local result = false
				if result then
					return result
				end

				-- Then Check Parent
				if k and _class[super] then
				    local ret = _class[super][k]
				    return ret
				else return nil end
			end
		})
	end
    
    class_type.new = function(...)
        local obj = { class = class_type }
        setmetatable(obj, { 
			__index = _class[class_type]
		})
        
        -- deal constructor recursively
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
		print("classA:func",self.var);
	end
	function classA:ctor()
		self.var = 1
	end


	classB = class(classA);
	-- function classB:func()
	-- 	print("classB:func");
	-- end
	function classB:ctor()
		self.var = 2
	end


	classC = class(classB)
	-- function classC:func()
	-- 	print("classC:func");
	-- end
	function classC:ctor()
		self.var = 3
	end


	local a = classA.new();
	local b = classB.new();
	local c = classC.new();
	a:func();
	-- b:func();
	-- c:func();

end

testInherit_3depth();



