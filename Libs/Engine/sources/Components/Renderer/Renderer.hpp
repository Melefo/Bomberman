/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "IComponent.hpp"
#include "Model.hpp"
#include "Texture.hpp"

namespace Component
{
    /**
     * @brief Renderer component
     * 
     */
    class Renderer : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Renderer object
             * 
             * @param assetName 
             */
            Renderer(const std::string& assetName="Default");
            /**
             * @brief Destroy the Renderer object
             * 
             */
            ~Renderer() override = default;
            /**
             * @brief Construct a new Renderer object
             * 
             * @param other 
             */
            Renderer(const Renderer& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Renderer 
             */
            Renderer& operator=(const Renderer& other) = default;

            const std::string &getName() const;

            std::ostream& operator<<(std::ostream& os) override;

            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:

            std::string _name;
    };
}

#endif /* !RENDERER_HPP_ */
