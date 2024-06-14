

#include <ArtGalleryOfCats/Screens/UserTextInput.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Screens
{


UserTextInput::UserTextInput(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard, AllegroFlare::Elements::Backgrounds::Base* background)
   : AllegroFlare::Screens::Base(ArtGalleryOfCats::Screens::UserTextInput::TYPE)
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , software_keyboard(software_keyboard)
   , background(background)
   , mode(MODE_USING_VIRTUAL_CONTROLS)
   , initialized(false)
{
}


UserTextInput::~UserTextInput()
{
}


void UserTextInput::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void UserTextInput::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void UserTextInput::set_background(AllegroFlare::Elements::Backgrounds::Base* background)
{
   this->background = background;
}


AllegroFlare::Elements::Backgrounds::Base* UserTextInput::get_background() const
{
   return background;
}


void UserTextInput::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::initialize]: error: guard \"font_bin\" not met");
   }
   software_keyboard.set_event_emitter(event_emitter);
   software_keyboard.set_font_bin(font_bin);
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   software_keyboard.set_prompt_text("What is the answer to the riddle?");
   initialized = true;
   return;
}

void UserTextInput::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::on_activate]: error: guard \"initialized\" not met");
   }
   if (background) background->activate();
   software_keyboard.reset();
   return;
}

void UserTextInput::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::on_deactivate]: error: guard \"initialized\" not met");
   }
   if (background) background->deactivate();
   return;
}

void UserTextInput::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::primary_timer_func]: error: guard \"initialized\" not met");
   }
   if (background) background->update();
   if (background) background->render();
   render();
   return;
}

void UserTextInput::set_font_name(std::string font_name)
{
   // TODO: guards, cannot be blank (or maybe this should be a guard in the bin if it is not)
   software_keyboard.set_font_name(font_name);
   return;
}

void UserTextInput::set_font_size(int font_size)
{
   // TODO: guards, cannot be zero (or maybe this should be a guard in the bin if it is not)
   software_keyboard.set_font_size(font_size);
   return;
}

void UserTextInput::set_prompt_text(std::string prompt_text)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::set_prompt_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::set_prompt_text]: error: guard \"initialized\" not met");
   }
   // TODO: guards, cannot be zero (or maybe this should be a guard in the bin if it is not)
   software_keyboard.set_prompt_text(prompt_text);
   return;
}

std::string UserTextInput::get_result_string_value()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::get_result_string_value]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::get_result_string_value]: error: guard \"initialized\" not met");
   }
   return software_keyboard.get_result_string();
}

void UserTextInput::set_event_to_emit_on_pressing_submit_key(std::string event_to_emit_on_pressing_submit_key)
{
   software_keyboard.set_event_to_emit_on_pressing_submit_key(event_to_emit_on_pressing_submit_key);
   return;
}

bool UserTextInput::mode_is_using_keyboard()
{
   return mode == MODE_USING_KEYBOARD;
}

bool UserTextInput::mode_is_using_virtual_controls()
{
   return mode == MODE_USING_VIRTUAL_CONTROLS;
}

void UserTextInput::set_mode_to_using_keyboard()
{
   mode = MODE_USING_KEYBOARD;
   return;
}

void UserTextInput::set_mode_to_using_virtual_controls()
{
   mode = MODE_USING_VIRTUAL_CONTROLS;
   return;
}

void UserTextInput::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   if (mode != MODE_USING_VIRTUAL_CONTROLS) return;

   // TODO: validate VirtualControllers::GenericController type

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         software_keyboard.move_cursor_up();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         software_keyboard.move_cursor_down();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT:
         software_keyboard.decrement_cursor_pos();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT:
         software_keyboard.increment_cursor_pos();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_A:
         software_keyboard.press_key_under_cursor();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_X:
         software_keyboard.press_key_by_name("BACKSPACE");
      break;
   }

   return;
}

void UserTextInput::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::key_char_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::key_char_func]: error: guard \"event\" not met");
   }
   if (mode != MODE_USING_KEYBOARD) return;

   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         software_keyboard.move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         software_keyboard.move_cursor_down();
      break;

      case ALLEGRO_KEY_RIGHT:
         software_keyboard.increment_cursor_pos();
      break;

      case ALLEGRO_KEY_LEFT:
         software_keyboard.decrement_cursor_pos();
      break;

      case ALLEGRO_KEY_ENTER:
         {
            bool shift = (event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
            if (shift) { software_keyboard.press_key_by_name("SUBMIT"); }
            else { software_keyboard.press_key_under_cursor(); }
         }
      break;

      case ALLEGRO_KEY_BACKSPACE:
         software_keyboard.press_key_by_name("BACKSPACE");
      break;

      case ALLEGRO_KEY_SPACE:
         software_keyboard.press_key_by_name("SPACE");
      break;

      default:
         std::string s(1, event->keyboard.unichar);
         software_keyboard.press_key_by_name(s);
      break;
   }
   return;
}

void UserTextInput::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Screens::UserTextInput::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Screens::UserTextInput::render]: error: guard \"initialized\" not met");
   }
   software_keyboard.render();
   return;
}


} // namespace Screens
} // namespace ArtGalleryOfCats


