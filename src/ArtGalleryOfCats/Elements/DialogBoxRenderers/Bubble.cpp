

#include <ArtGalleryOfCats/Elements/DialogBoxRenderers/Bubble.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogButton.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Elements
{
namespace DialogBoxRenderers
{


Bubble::Bubble(AllegroFlare::FontBin* font_bin, std::string current_page_text, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, int num_revealed_characters, bool is_finished, bool page_is_finished, float page_finished_at, bool at_last_page, float age)
   : font_bin(font_bin)
   , current_page_text(current_page_text)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
   , num_revealed_characters(num_revealed_characters)
   , is_finished(is_finished)
   , page_is_finished(page_is_finished)
   , page_finished_at(page_finished_at)
   , at_last_page(at_last_page)
   , age(age)
{
}


Bubble::~Bubble()
{
}


void Bubble::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Bubble::set_current_page_text(std::string current_page_text)
{
   this->current_page_text = current_page_text;
}


void Bubble::set_width(float width)
{
   this->width = width;
}


void Bubble::set_height(float height)
{
   this->height = height;
}


void Bubble::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Bubble::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Bubble::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void Bubble::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void Bubble::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void Bubble::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


void Bubble::set_page_is_finished(bool page_is_finished)
{
   this->page_is_finished = page_is_finished;
}


void Bubble::set_page_finished_at(float page_finished_at)
{
   this->page_finished_at = page_finished_at;
}


void Bubble::set_at_last_page(bool at_last_page)
{
   this->at_last_page = at_last_page;
}


void Bubble::set_age(float age)
{
   this->age = age;
}


AllegroFlare::FontBin* Bubble::get_font_bin() const
{
   return font_bin;
}


std::string Bubble::get_current_page_text() const
{
   return current_page_text;
}


float Bubble::get_width() const
{
   return width;
}


float Bubble::get_height() const
{
   return height;
}


std::string Bubble::get_font_name() const
{
   return font_name;
}


int Bubble::get_font_size() const
{
   return font_size;
}


float Bubble::get_text_padding_x() const
{
   return text_padding_x;
}


float Bubble::get_text_padding_y() const
{
   return text_padding_y;
}


int Bubble::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool Bubble::get_is_finished() const
{
   return is_finished;
}


bool Bubble::get_page_is_finished() const
{
   return page_is_finished;
}


float Bubble::get_page_finished_at() const
{
   return page_finished_at;
}


bool Bubble::get_at_last_page() const
{
   return at_last_page;
}


float Bubble::get_age() const
{
   return age;
}


void Bubble::render()
{
   float normalized_age = std::max(std::min(1.0f, age), 0.0f);
   float curved_time = AllegroFlare::interpolator::double_fast_in(normalized_age);
   float inv_curved_time = 1.0 - curved_time;

   AllegroFlare::Placement2D frame_place = { width/2, height/2, width, height, };
   frame_place.position.y += 10 * inv_curved_time;
   frame_place.start_transform();
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   dialog_box_frame.set_opacity(curved_time);
   dialog_box_frame.render();
   frame_place.restore_transform();

   if (is_finished)
   {
      draw_special_state_empty_text(width, height);
   }
   else
   {
      draw_styled_revealed_text(width, current_page_text, num_revealed_characters);

      // draw the "next" or "finished" cursor (depending on context)
      if (page_is_finished)
      {
         AllegroFlare::Elements::DialogButton dialog_button(font_bin);
         dialog_button.set_started_at(page_finished_at);
         dialog_button.set_x(width - 160);
         dialog_button.set_y(height - 60);

         if (at_last_page) dialog_button.set_at_last_advance(true);

         dialog_button.render();
      }
   }
   return;
}

void Bubble::draw_special_state_empty_text(float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_html("303030");
   float line_height = al_get_font_line_height(text_font);
   std::string text = "[dialog finished]";
   al_draw_text(
      text_font,
      text_color,
      width * 0.5,
      height * 0.5 - line_height * 0.5,
      ALLEGRO_ALIGN_CENTER,
      text.c_str()
   );
   return;
}

void Bubble::draw_action_text(std::string text, float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR text_color = al_color_html("ffffff");
   float line_height = al_get_font_line_height(text_font);
   al_draw_text(
      text_font,
      text_color,
      width-20,
      height-line_height-10,
      ALLEGRO_ALIGN_RIGHT,
      text.c_str()
   );
   return;
}

void Bubble::draw_styled_revealed_text(float max_width, std::string text, int num_revealed_characters)
{
   //float text_padding_x = 40.0f;
   //float text_padding_y = 30.0f;
   float text_box_max_width = max_width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1}; //al_color_name("skyblue");
   //int num_revealed_characters = obtain_dialog_box_num_revealed_characters();

   al_draw_multiline_text(
      text_font,
      text_color,
      text_padding_x,
      text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(text, num_revealed_characters).c_str()
   );
   return;
}

std::string Bubble::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}

ALLEGRO_FONT* Bubble::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Bubble::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bubble::obtain_dialog_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Bubble::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bubble::obtain_dialog_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Bubble::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bubble::obtain_dialog_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace ArtGalleryOfCats


