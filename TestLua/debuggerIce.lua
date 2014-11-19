-- [LUA-print] ##
-- [LUA-print] ldb:linedefined,25
-- [LUA-print] ldb:currentline,28
-- [LUA-print] ldb:lastlinedefined,28
-- [LUA-print] ldb:source,@fbcore/ui/Director.lua
-- [LUA-print] ldb:what,Lua
-- [LUA-print] ldb:namewhat,
-- [LUA-print] ldb:short_src,fbcore/ui/Director.lua
function debug:printLocal(level,which,isShowVal)
    local index = 1
    while true do
      local key,value = debug.getlocal(level,index);
      if not key then break end
      print("\t["..index.."]["..key.."]("..type(value)..")");
      if isShowVal and (which == -1 or index == which) then
        dump(value)
      end
      index = index + 1
    end
end


function debug:tracebackAll(level,isMore)
  local lv = 2;
  while true do

    local info = debug.getinfo(lv,"Sln");
    if not info then break end

    print("<"..lv..">FUNC:[".. (info.name or "NULL").."]\tFILE:" .. info.short_src .. "["..info.currentline.."]");
    if lv == -1 or lv == level or (isMore and lv > level) then
      if info.name ~= "require" then 
        debug:printLocal(lv+1,-1,true);
      end
    end

    lv = lv + 1
  end
end 
-- break -- 
function bk()
  debug.debug();
  -- body
end
-- traceback --
function tb()
  print("tb");
  print(debug.traceback());
end
function tu()
  if not level then level = 6 end;
  print("tl");
  debug:tracebackAll(level,true)
end
function te(level)
  if not level then level = 6 end;
  print("te");
  debug:tracebackAll(level,false)
end

-- local --
function ln(which,level)
  print("ln");
  if not level then level = 6 end
  if which  then
    debug:printLocal(level,which,true);
  else
    debug:printLocal(level,-1,isShowVal);
  end
end
function la(level)
  print("la");
  if not level then level = 6 end
  debug:printLocal(level,-1,true);
end