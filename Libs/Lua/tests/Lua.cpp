/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Lua
*/

#include <iostream>
#include <vector>
#include <criterion/criterion.h>
#include "Vector2.hpp"
#include "State.hpp"

Test(lua, open)
{
    Lua::State state;

    cr_assert_eq(state.RunScript("../Libs/Lua/tests/test.lua"), 0);
}

Test(lua, getglobalvar)
{
    Lua::State state;

    state.RunScript("../Libs/Lua/tests/test.lua");
    cr_assert_eq(state.GetGlobal<std::string>("Hello"), "Hello World!");
    state.SetGlobal("Testing", 123456);
    cr_assert_eq(state.GetGlobal<int>("Testing"), 123456);
}

Test(lua, callFunction)
{
    Lua::State state;

    state.RunScript("../Libs/Lua/tests/test.lua");
    cr_assert_eq(state.Call<int>("Add", 42, 69), 111);
}

Test(lua, vector)
{
    Lua::State state;
    std::vector<int> vector = {10, 20, 30, 40, 50};

    state.SetGlobal("Vector", vector);
    cr_assert_eq(state.RunScript("../Libs/Lua/tests/test.lua"), 0);

    std::map<std::string, int> test = {
        {"x", 123},
        {"y", 456}
    };

    state.Call("dumpTest", test);
    RayLib::Vector2 vec(12, 34);
    std::map<std::string, int> result = state.Call<std::map<std::string, int>>("mapTest");
    RayLib::Vector2<int> rayvec = state.Call<RayLib::Vector2<int>>("mapTest");
    /*for (auto& pair : result)
        std::cout << pair.first << " " << pair.second << std::endl;
    std::cout << "RayLib::Vector2\tx: " << rayvec.x << "\ty: " << rayvec.y << std::endl;
    //cr_assert_eq(state.GetGlobal<int>("Testing"), 123456);*/
}