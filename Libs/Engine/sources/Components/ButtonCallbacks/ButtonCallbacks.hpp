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
             * @brief Increment the nbr of IA
             * 
             */
            static void IncrementIANbr(void);

            /**
             * @brief Decrement the nbr of IA
             * 
             */
            static void DecrementIANbr(void);

            /**
             * @brief Increment the map of Height
             * 
             */
            static void IncrementMapHeight(void);

            /**
             * @brief Decrement the map of Height
             * 
             */
            static void DecrementMapHeight(void);

            /**
             * @brief Increment the map of Width
             * 
             */
            static void IncrementMapWidth(void);

            /**
             * @brief Decrement the map of Width
             * 
             */
            static void DecrementMapWidth(void);

            /**
             * @brief Generate a map in the background
             * 
             */
            static void GenerateBackgroundMap(void);

            /**
             * @brief switch the IsMapBasic variable
             * 
             */
            static void SwitchMapStatus(void);

            /**
             * @brief save map in xml file
             * 
             */
            static void SaveMap(void);

            /**
             * @brief Clear the seed
             * 
             */
            static void ClearSeed(void);

            /**
             * @brief Start the Game
             * 
             */
            static void StartGame(void);
            /**
             * @brief Start the Editor menu
             * 
             */
            static void StartEditorMenu(void);
            /**
             * @brief Start the Options menu
             * 
             */
            static void StartOptionMenu(void);
            /**
             * @brief Return to the Main menu
             * 
             */
            static void ExitGameToMainMenu(void);

            /**
             * @brief Restart the current game
             * 
             */
            static void Replay(void);
            /**
             * @brief Continue the paused game
             * 
             */
            static void Continue(void);
            /**
             * @brief Quit the window
             * 
             */
            static void QuitWindow(void);

            /**
             * @brief Toggle fullscreen
             * 
             */
            static void ToggleFullScreen(void);


            /**
             * @brief Increment the volume of the music
             *
             */
            static void IncrementVolume(void);

            /**
             * @brief Decrement the value of the music
             *
             */
            static void DecrementVolume(void);

            std::ostream &operator<<(std::ostream &os) override {return os;};
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
             * @brief Private Method for displaying dynamic text on click with int
             * 
             */
            static void TextInterfaceLoader(std::string tagName, int nb);
            /**
             * @brief Private Method for displaying dynamic text on click with string
             * 
             * @param tagName 
             * @param str 
             */
            static void TextInterfaceLoader(std::string tagName, std::string str);
            /**
             * @brief Give seed value in string to int
             * 
             */
            static int GetSeed(void);
    };
}

#endif /* !BUTTONCALLBACKS_HPP_ */
