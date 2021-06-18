/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDText
*/

#ifndef HUDTEXT_HPP_
#define HUDTEXT_HPP_

#include "HUD.hpp"

namespace Component {
    class HUDText : public HUD {
        public:
        /**
             * @brief Construct a new HUDText object
             * 
             * @param attatchedEntity
             * @param playerNbr
             */
            HUDText(Component::AController &attatchedController, int playerNbr);
            /**
             * @brief Destroy the HUDText object
             * 
             */
            ~HUDText();

            /**
             * @brief Called every frame
             * To be overridden by a playercontroller or AI controller
             * @param dt 
             * @param entity 
             */
            void Update(double dt, ECS::Entity& entity);
            /**
             * @brief Called every ~0.02 seconds
             * To be overridden by a playercontroller or AI controller
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity);
            /**
             * @brief Called after update
             * To be overridden by a playercontroller or AI controller
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity);
            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
    };
}

#endif /* !HUDTEXT_HPP_ */
