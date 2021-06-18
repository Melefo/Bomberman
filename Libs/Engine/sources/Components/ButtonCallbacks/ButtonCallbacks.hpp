/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#ifndef BUTTONCALLBACKS_HPP_
#define BUTTONCALLBACKS_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"
#include "IBehaviour.hpp"
#include "Button.hpp"
#include <iostream>
#include "Coordinator.hpp"

namespace Component
{
    /**
     * @brief Button wrapper class
     * 
     */
    class ButtonCallbacks : public IBehaviour {
        public:
            /**
             * @brief Construct a new Button Callbacks object
             * 
             * @param attatchedEntity get the attatched button from the entity
             */
            ButtonCallbacks(ECS::Entity& attatchedEntity);
            /**
             * @brief Destroy the Button Callbacks object
             * 
             */
            ~ButtonCallbacks() override = default;
            /**
             * @brief Construct a new Button Callbacks object
             * 
             * @param other 
             */
            ButtonCallbacks(const ButtonCallbacks& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return ButtonCallbacks& 
             */
            ButtonCallbacks& operator=(const ButtonCallbacks& other) = default;

            /**
             * @brief Update function, used to check if the mouse is over/clicking the button
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief FixedUpdate
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief LateUpdate
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            /**
             * @brief Increment the nbr of users
             * 
             */
            static void IncrementPlayerNbr(void);

            /**
             * @brief Decrement the nbr of users
             * 
             */
            static void DecrementPlayerNbr(void);

            /**
             * @brief Increment the map of Height
             * 
             */
            static void IncrementMapHeight();

            /**
             * @brief Decrement the map of Height
             * 
             */
            static void DecrementMapHeight();

            /**
             * @brief Increment the map of Width
             * 
             */
            static void IncrementMapWidth();

            /**
             * @brief Decrement the map of Width
             * 
             */
            static void DecrementMapWidth();

            /**
             * @brief Generate a map in the background
             * 
             */
            static void GenerateBackgroundMap(void);

            static void StartGame(void);
            static void StartEditorMenu(void);
            static void ExitGameToMainMenu(void);

            static void Replay(void);
            static void QuitWindow(void);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            /**
             * @brief Reference to the entity
             * 
             */
            ECS::Entity& _entity;
            /**
             * @brief Reference to button component
             * 
             */
            Button& _button;
            /**
             * @brief Private Method for displaying dynamic text on click
             * 
             */
            static void TextInterfaceLoader(std::string tagName, int nb);
    };
}

#endif /* !BUTTONCALLBACKS_HPP_ */
