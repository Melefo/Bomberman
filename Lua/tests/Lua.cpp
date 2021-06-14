/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Lua
*/

#include <iostream>
#include <vector>
#include <criterion/criterion.h>
#include "State.hpp"

Test(lua, open)
{
    Lua::State state;

    cr_assert_eq(state.RunScript("../Lua/tests/test.lua"), 0);
}

Test(lua, getglobalvar)
{
    Lua::State state;

    state.RunScript("../Lua/tests/test.lua");
    cr_assert_eq(state.GetGlobal<std::string>("Hello"), "Hello World!");
    state.SetGlobal("Testing", 123456);
    cr_assert_eq(state.GetGlobal<int>("Testing"), 123456);
}

Test(lua, callFunction)
{
    Lua::State state;

    state.RunScript("../Lua/tests/test.lua");
    cr_assert_eq(state.Call<int>("Add", 42, 69), 111);
}

Test(lua, vector)
{
    Lua::State state;
    std::vector<int> vector = {10, 20, 30, 40, 50};

    state.SetGlobal("Vector", vector);
    cr_assert_eq(state.RunScript("../Lua/tests/test.lua"), 0);
    //cr_assert_eq(state.GetGlobal<int>("Testing"), 123456);
}