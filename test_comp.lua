




function OnInit(self)
	self.x = 100
	test_global(self.x)
end

function OnStart(self)
	print("test_comp:"..self.x)
	self:print()
end
