/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDBonusBar
*/

#ifndef HUDBONUSBAR_HPP_
#define HUDBONUSBAR_HPP_

#include "HUD.hpp"

namespace Component {
    class HUDBonusBar : public HUD {
        public:
        /**
             * @brief Construct a new HUDBonusBar object
             * 
             * @param attatchedEntity
             * @param playerNbr
             */
            HUDBonusBar(Component::AController &attatchedController, int playerNbr, float &timer, bool isBg, const std::string &tag);
            /**
             * @brief Destroy the HUDBonusBar object
             * 
             */
            ~HUDBonusBar();
            /**
             * @brief Construct a new HUDBonusBar object
             * 
             * @param other 
             */
            HUDBonusBar(const HUDBonusBar& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return HUDBonusBar& 
             */
            HUDBonusBar& operator=(const HUDBonusBar& other) = default;

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
            float _maxTimer;
            std::string _entityTag;
            bool _isBg;
    };
}

#endif /* !HUDBONUSBAR_HPP_ */
