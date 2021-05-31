/*
** EPITECH PROJECT, 2021
** OSRedirector
** File description:
** OSRedirector
*/

#ifndef __OSREDIRECTOR_HPP__
#define __OSREDIRECTOR_HPP__

#include <iostream>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

class OSRedirector {
private:
    std::ostringstream _oss;
    std::streambuf *_backup;
    std::ostream &_c;

public:
OSRedirector(std::ostream &c) : _c(c) {
        _backup = _c.rdbuf();
        _c.rdbuf(_oss.rdbuf());
    }

    ~OSRedirector() {
        _c.rdbuf(_backup);
    }

    const std::string getContent() {
        _oss << std::flush;
        return _oss.str();
    }
};

#endif /*__OSREDIRECTOR_HPP__*/