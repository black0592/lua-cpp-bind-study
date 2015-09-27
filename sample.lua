--module(..., package.seeall)  -- optionally omitting package.seeall if desired
--module("complex", package.seeall)

--define lua function
function luaPrint(str)
	print("luaPrint:"..str)
end

function luaSum(a, b)
	local sum = a + b
	print("luaSum:"..sum)
	return sum
end

--define table
testTable = {"hello", a=123456}
print("load sampe.lua");

--[[
test_global_func_void0()
test_global_func_void1("void_param1")
local r1 = test_global_func0()
local r2 = test_global_func1("param1")
print("r1:"..r1)
print("r2:"..r2)

local class = BaseClass(100)
local class1 = BaseClass(100)
print("class=class1 ? "..(class==class1 and "yes" or "no"));

class:BindTable(testTable);
print("__userdata="..type(testTable.__userdata_obj));

class:SetX(9999);
local x = class:GetX()
print("x:"..x)
print("a:"..testTable.a)
--]]