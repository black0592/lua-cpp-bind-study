local dt = 0.01

-- Cause a script to wait a certain amount of seconds before resuming again.
function WaitSeconds(seconds)
    local t = 0
    coroutine.yield()
    while true do
        t = t + dt
        if t > seconds then
            return
        else
            coroutine.yield()
        end
    end
end


local loaded_env = { }
function LoadComponentFile( path, classname )
  local env = loaded_env[path]
  if env == nil then
    env = {}
	  loaded_env[path] = env
	  setmetatable( env, {__index = _G} )
    loadfile(path, "bt", env)( )
  end
    
  local comp_class = get_class(classname)
  if comp_class == nil then
    comp_class = class(classname, ScriptComponent)
    for k,v in pairs(env) do
      comp_class[k] = v
    end
  end

  return comp_class
end
