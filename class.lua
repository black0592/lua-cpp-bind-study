local classes = {}


local function __is_system_key(k)
    return (string.len(k)>2 and string.sub(k, 1, 2) == "__")
end

local function __call_ctor(instance, cls, ...)
    if cls==nil then return end
    __call_ctor(instance, cls.super, ...)
    if cls.ctor then cls.ctor(instance, ...) end
end

function get_class(classname)
    return classes[classname]
end

function class(classname, super)
    local cls = get_class(classname)
    if cls then return cls end

    local superType = type(super)
    if super~=nil and superType ~= "table" then return nil end 
    cls = {}

    if super and super.__is_native_class then
    	local is_native_super = (super.__nativeclass == null)
        local super_meta = is_native_super and getmetatable(super) or super
        -- copy super class function to meta
        for k,v in pairs(super_meta) do
        	if not __is_system_key(k) then cls[k] = v end
        end

        cls.classname  				= classname
        cls.__nativeclass 			= is_native_super and super or super.__nativeclass
        cls.__is_native_class		= true
        cls.super 					= super

        function cls.new(...)
            local instance = cls.__nativeclass.new(...)
            local meta = {}
            meta.__index = function (t, k)
            	local v = rawget(meta, k)
            	if v then return v end
            	return cls[k]
            end
            meta.__newindex = meta
            lua_setuserdata_metatable(instance, meta)
            -- constructor
            __call_ctor(instance, cls, ...)
            return instance
        end

    else
        if super then
            for k,v in pairs(super) do
                if not __is_system_key(k) then cls[k] = v end
            end
        end

        cls.classname  = classname
        cls.super      = super

        function cls.new(...)
            local instance = {}
            local meta = {__index = cls}
            setmetatable(instance, meta)
            -- constructor
            __call_ctor(instance, cls, ...)
            return instance
        end
    end

    if cls then
        classes[classname] = cls
    end

    return cls
end