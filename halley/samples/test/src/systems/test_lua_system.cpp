#include "systems/test_lua_system.h"
#include <lua.hpp>
#include <luajit.h>

using namespace Halley;

#ifdef _MSC_VER
#pragma comment(lib, "lua51.lib")
#endif

static int luaPrint(lua_State* state);
static int luaGetFamilyName(lua_State* state);
static int luaGetFamilyCount(lua_State* state);
static int luaGetFamilyEntry(lua_State* state);

class TestLuaSystem final : public TestLuaSystemBase<TestLuaSystem> {
public:
	TestLuaSystem()
	{
		state = initLua();
		loadLibrary();
		loadScript("c:/dev/projects/halley/bin/test_lua.lua");
		makeUpdate();
	}

	~TestLuaSystem()
	{
		lua_close(state);
		state = nullptr;
	}

	void update(Time t)
	{
		lua_getglobal(state, "test_lua_update");
		lua_pushnumber(state, t);

		if (lua_pcall(state, 1, 0, 0)) {
			throw Exception("Error calling test_lua_update: " + String(lua_tostring(state, -1)));
		}
	}

	String getFamilyName(size_t famIdx)
	{
		static const char* names[] = { "mainFamily" };
		return names[famIdx];
	}

	size_t getFamilyCount(size_t famIdx)
	{
		return mainFamily.count();
	}

	MainFamily& getFamilyEntry(size_t famIdx, size_t entryIdx)
	{
		return mainFamily[entryIdx];
	}

private:
	lua_State* state = nullptr;


	lua_State* initLua()
	{
		constexpr bool jit = false;
		lua_State* lua = lua_open();
		luaJIT_setmode(lua, 0, LUAJIT_MODE_ENGINE | (jit ? LUAJIT_MODE_ON : LUAJIT_MODE_OFF));
		luaL_openlibs(lua);
		return lua;
	}

	void loadLibrary()
	{
		const luaL_reg halleyLib[] = {
			{ "print", luaPrint },
			{ "getFamilyName", luaGetFamilyName },
			{ "getFamilyCount", luaGetFamilyCount },
			{ "getFamilyEntry", luaGetFamilyEntry },
			{ nullptr, nullptr }
		};
		luaL_openlib(state, "Halley", halleyLib, 0);
	}

	void loadScript(String name)
	{
		if (luaL_loadfile(state, name.c_str())) {
			throw Exception("Unable to load script: " + String(lua_tostring(state, -1)));
		}
		if (lua_pcall(state, 0, 0, 0)) {
			throw Exception("Unable to execute script");
		}
	}

	void makeUpdate()
	{
		int nFamilies = 1;

		lua_getglobal(state, "makeUpdate");
		lua_pushlightuserdata(state, this);
		lua_pushinteger(state, nFamilies);
		
		if (lua_pcall(state, 2, 1, 0)) {
			throw Exception("Error calling makeUpdate: " + String(lua_tostring(state, -1)));
		}
		
		lua_setglobal(state, "test_lua_update");
	}
};

REGISTER_SYSTEM(TestLuaSystem)

static int luaPrint(lua_State* state)
{
	String str = lua_tostring(state, -1);
	lua_pop(state, 1);
	std::cout << "[Lua] " << str << std::endl;

	return 0;
}

static int luaGetFamilyName(lua_State* state)
{
	auto system = reinterpret_cast<TestLuaSystem*>(lua_touserdata(state, -1));
	long long n = lua_tointeger(state, -2);
	lua_pop(state, 2);
	lua_pushstring(state, system->getFamilyName(int(n)).c_str());
	return 1;
}

static int luaGetFamilyCount(lua_State* state)
{
	auto system = reinterpret_cast<TestLuaSystem*>(lua_touserdata(state, -1));
	long long familyN = lua_tointeger(state, -2);
	lua_pop(state, 2);
	lua_pushinteger(state, system->getFamilyCount(familyN));
	return 1;
}

static int luaGetFamilyEntry(lua_State* state)
{
	auto system = reinterpret_cast<TestLuaSystem*>(lua_touserdata(state, -1));
	long long familyN = lua_tointeger(state, -2);
	long long memberIdx = lua_tointeger(state, -3);
	lua_pop(state, 3);

	// Fourth parameter is the destination object

	auto& entry = system->getFamilyEntry(familyN, memberIdx);

	// Return passed object

	return 1;
}
