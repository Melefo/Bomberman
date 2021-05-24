/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** hello
*/

#include <criterion/criterion.h>
#include <string>

Test(HelloWorld, HelloWorld)
{
    std::string hello = "Hello World";

    cr_assert_eq(hello, "Hello World");
}