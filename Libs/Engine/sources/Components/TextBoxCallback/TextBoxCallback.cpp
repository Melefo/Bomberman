/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextBoxCallback
*/

#include "TextBoxCallback.hpp"
#include "Mouse.hpp"
#include "Window.hpp"
#include "Physics2D.hpp"

namespace Component
{
	TextBoxCallback::TextBoxCallback(ECS::Entity& entity) :
		_entity(entity), _textBox(entity.GetComponent<TextBox>()), _input()
	{
	}

	void TextBoxCallback::Update(double, ECS::Entity&)
	{
		if (!this->IsMouseOver())
			return;
		int key = this->_input.GetCharPressed();
		if ((key >= '0' && key <= '9' && this->_textBox.GetIsNum()) ||
			(((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) && this->_textBox.GetIsAlpha()))
			this->_textBox.AppendChar(static_cast<char>(key));
		if (this->_input.IsKeyPressed(KeyboardKey::KEY_BACKSPACE))
			this->_textBox.RemoveChar();
	}

	void TextBoxCallback::LateUpdate(double, ECS::Entity&)
	{
	}

	void TextBoxCallback::FixedUpdate(ECS::Entity&)
	{
	}


	bool TextBoxCallback::IsMouseOver(void)
	{
		RayLib::Vector2<float> mousePos = RayLib::Mouse::GetPosition();
		std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
		RayLib::Vector2<float> winSize = RayLib::Vector2<float>(static_cast<float>(window->GetSize().x),
			static_cast<float>(window->GetSize().y));
		RayLib::Vector2<float> scale = window->GetScale();
		RayLib::Rectangle rectangle = this->_textBox.GetRectangle();
		rectangle.width *= scale.x;
		rectangle.height *= scale.y;

		return RayLib::Physics2D::CheckCollision(mousePos, rectangle);
	}
}
