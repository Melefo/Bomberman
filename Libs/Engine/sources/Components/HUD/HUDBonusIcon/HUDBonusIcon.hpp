/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDBonusIcon
*/

#ifndef HUDBONUSICON_HPP_
#define HUDBONUSICON_HPP_

#include "HUD.hpp"

namespace Component {
    class HUDBonusIcon : public HUD {
        public:
        /**
             * @brief Construct a new HUDBonusIcon object
             * 
             * @param attatchedEntity
             * @param playerNbr
             */
            HUDBonusIcon(Component::AController &attatchedController, int playerNbr, float &timer, const std::string &tag);
            /**
             * @brief Destroy the HUDBonusIcon object
             * 
             */
            ~HUDBonusIcon();
            /**
             * @brief Construct a new HUDBonusIcon object
             * 
             * @param other 
             */
            HUDBonusIcon(const HUDBonusIcon& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return HUDBonusIcon& 
             */
            HUDBonusIcon& operator=(const HUDBonusIcon& other) = default;

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
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            float &_timer;
            std::string _entityTag;
    };
}

#endif /* !HUDBONUSICON_HPP_ */
