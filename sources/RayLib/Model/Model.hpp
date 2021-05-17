/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <raylib.h>
#include <string>

namespace RayLib
{
    class Model {
        public:
            Model(const std::string& fileName);
            ~Model();

            ::Model model;
        protected:
        private:
    };
}

#endif /* !MODEL_HPP_ */
