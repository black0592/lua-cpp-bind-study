
function test_global(x)
	print("test_global:"..x)
end

local Login = class("Login", BaseClass)
  
function Login:ctor()
	print("Login ctor")
	self.a = "a"
end
function Login:test()  
    print("Login test") 
end 
function Login:foo()
	return 1
end

function Login:GetX()
	return Login.super.GetX(self) + 1
end

local LoginEx = class("LoginEx", Login)  
function LoginEx:ctor()
	print("LoginEx ctor")
	self.a = self.a.."b"
end
function LoginEx:fooex()
	return 1
end

function LoginEx:GetX()
	print("LoginEx:GetX "..self.super.classname)
	return  LoginEx.super.GetX(self) + 1
end
  

local LoginExEx = class("LoginExEx", LoginEx)
function LoginExEx:ctor()
	print("LoginExEx ctor")
	self.a = self.a.."c"
end
function LoginExEx:fooexex()
	return 1
end

------------------------------------------------------------

local Regist = class("Regist")
function Regist:ctor()
	print("Regist ctor")
end
function Regist:GetX()
	return 1
end
function Regist:test()
    print("Regist test")
end

local RegistEx = class("RegistEx", Regist)
function RegistEx:ctor()
	print("RegistEx ctor")
end
function RegistEx:GetX()
	return RegistEx.super.GetX(self) + 2
end
function RegistEx:test()
    print("RegistEx test")
end

-- print("----------------begin run script----------------")

-- BaseClass.Print()
-- DerivedClass.Print()

-- local class = DerivedClass.new()
-- class:SetX(9999);
-- print("x:"..class:GetX())

-- local refector = Reflector.GetInstance()
-- local meta_class = refector:GetMetaClass("class BaseClass")
-- print("meta_class name:"..meta_class:GetName())

-- test_table = {x=10, y=11, name="test_table", sub={z=100000}}

-- function test_func(x)
-- 	print("test_func:"..x)
-- end

-- function test_global(x)
-- 	print("test_global:"..x)
-- end

-- test_table.func = test_func


-- local tmp = LoginExEx.new()
-- tmp:SetX(100)
-- print("tmp.x:"..tmp:GetX()..", a:"..tmp.a)
-- tmp:test()
-- tmp:fooex()


-- local t = RegistEx.new()
-- t.b = "b"
-- print("t.x:"..t:GetX()..", b:"..t.b)
-- t:test()

-- print("----------------end run script----------------")



