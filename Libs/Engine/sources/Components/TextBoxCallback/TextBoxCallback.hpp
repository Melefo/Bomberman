/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextBoxCallback
*/

#ifndef TEXTBOXCALLBACK_HPP_
#define TEXTBOXCALLBACK_HPP_

#include "TextBox.hpp"
#include "IBehaviour.hpp"
#include "Input.hpp"

namespace Component
{
	/**
	 * @brief Behaviour of the TextBox
	 * 
	 */
	class TextBoxCallback : public IBehaviour
	{
		public:
			/**
			 * @brief Construct a new Text Box Callback object
			 * 
			 * @param entity 
			 */
			TextBoxCallback(ECS::Entity& entity);
			/**
			 * @brief Destroy the Text Box Callback object
			 * 
			 */
			~TextBoxCallback() override = default;
			/**
			 * @brief Construct a new copy Text Box Callback object
			 * 
			 * @param other 
			 */
			TextBoxCallback(const TextBoxCallback& other) = default;
			/**
			 * @brief Construct a new assigned Text Box Callback object
			 * 
			 * @param other 
			 * @return TextBoxCallback& 
			 */
			TextBoxCallback& operator=(const TextBoxCallback& other) = default;

			/**
			 * @brief Checking if a key is pressed to set its value inside the TextBox
			 * 
			 * @param dt 
			 * @param entity 
			 */
			void Update(double dt, ECS::Entity& entity) override;
			void LateUpdate(double dt, ECS::Entity& entity) override;
			void FixedUpdate(ECS::Entity& entity) override;

			std::ostream& operator<<(std::ostream& os) override { return os; };
			boost::property_tree::ptree& operator<<(boost::property_tree::ptree& ptree) override { return ptree; };
		private:
			/**
			 * @brief Check if the mouse is over the TextBox to get keys pressed
			 * 
			 * @return true 
			 * @return false 
			 */
			bool IsMouseOver(void);

			/**
			 * @brief Associated entity
			 * 
			 */
			ECS::Entity& _entity;
			/**
			 * @brief Associated TextBox
			 * 
			 */
			TextBox& _textBox;
			/**
			 * @brief Intput Manager
			 * 
			 */
			RayLib::Input _input;
	};
}

#endif // !TEXTBOXCALLBACK_HPP_
