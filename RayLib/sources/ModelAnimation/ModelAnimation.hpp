/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ModelAnimation
*/

#ifndef MODELANIMATION_HPP_
#define MODELANIMATION_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include "Model.hpp"

namespace RayLib
{
    /**
     * @brief Encapsulation for ModelAnimation struct
     * 
     */
    class ModelAnimation {
        public:
            /**
             * @brief Construct a new Model Animation object
             * 
             * @param fileName 
             */
            ModelAnimation(const std::string& fileName);
            /**
             * @brief Destroy the Model Animation object
             * 
             */
            ~ModelAnimation();
            /**
             * @brief Construct a new Model Animation object
             * 
             * @param other 
             */
            ModelAnimation(const ModelAnimation& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return ModelAnimation& 
             */
            ModelAnimation& operator=(const ModelAnimation& other) = default;

            /**
             * @brief Play the animation at index
             * 
             * @param model 
             * @param animIndex 
             */
            void Play(Model& model, int animIndex=0);

        protected:
        private:
            /**
             * @brief Vector of modelAnimations, converted from C array
             * 
             */
            //std::vector<::ModelAnimation> _modelAnimations;
            ::ModelAnimation *_modelAnimations;
            /**
             * @brief Total animations
             * 
             */
            int _animsCount;
            /**
             * @brief Current frame
             * 
             */
            int _frame;
    };
}

#endif /* !MODELANIMATION_HPP_ */
