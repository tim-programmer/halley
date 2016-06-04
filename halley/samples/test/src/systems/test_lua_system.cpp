#include "systems/test_lua_system.h"
#include <lua.hpp>
#include <luajit.h>

using namespace Halley;

#ifdef _MSC_VER
#pragma comment(lib, "lua51.lib")
#endif

class TestLuaSystem final : public TestLuaSystemBase<TestLuaSystem> {
public:
	TestLuaSystem()
	{
		constexpr bool jit = false;
		state = lua_open();
		luaJIT_setmode(state, 0, LUAJIT_MODE_ENGINE | (jit ? LUAJIT_MODE_ON : LUAJIT_MODE_OFF));
		luaL_openlibs(state);
	}

	~TestLuaSystem()
	{
		lua_close(state);
		state = nullptr;
	}

	void update(Time t)
	{
		lua_getglobal(state, "_VERSION");
		lua_tolstring(state, -1, nullptr);
		lua_pop(state, 1);
		//std::cout << versionStr << std::endl;
	}

private:
	lua_State* state = nullptr;
};

REGISTER_SYSTEM(TestLuaSystem)
