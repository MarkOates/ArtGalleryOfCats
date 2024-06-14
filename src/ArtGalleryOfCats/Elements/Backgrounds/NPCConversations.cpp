

#include <ArtGalleryOfCats/Elements/Backgrounds/NPCConversations.hpp>

#include <AllegroFlare/ScreenCapture.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Elements
{
namespace Backgrounds
{


NPCConversations::NPCConversations(AllegroFlare::BitmapBin* bitmap_bin, std::string dialog_bubble_bitmap_identifier)
   : AllegroFlare::Elements::Backgrounds::Base(ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::TYPE)
   , bitmap_bin(bitmap_bin)
   , dialog_bubble_bitmap_identifier(dialog_bubble_bitmap_identifier)
   , inv_scale(DEFAULT_INV_SCALE)
   , capture(nullptr)
   , initialized(false)
{
}


NPCConversations::~NPCConversations()
{
}


void NPCConversations::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void NPCConversations::set_dialog_bubble_bitmap_identifier(std::string dialog_bubble_bitmap_identifier)
{
   this->dialog_bubble_bitmap_identifier = dialog_bubble_bitmap_identifier;
}


AllegroFlare::BitmapBin* NPCConversations::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string NPCConversations::get_dialog_bubble_bitmap_identifier() const
{
   return dialog_bubble_bitmap_identifier;
}


int NPCConversations::get_inv_scale() const
{
   return inv_scale;
}


void NPCConversations::set_inv_scale(int inv_scale)
{
   if (!((inv_scale >= 1)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::set_inv_scale]: error: guard \"(inv_scale >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::set_inv_scale]: error: guard \"(inv_scale >= 1)\" not met");
   }
   if (!((inv_scale <= 20)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::set_inv_scale]: error: guard \"(inv_scale <= 20)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::set_inv_scale]: error: guard \"(inv_scale <= 20)\" not met");
   }
   this->inv_scale = inv_scale;
   if (initialized) refresh_capture();
   return;
}

void NPCConversations::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::initialize]: error: guard \"bitmap_bin\" not met");
   }
   refresh_capture();
   bitmap_bin->preload(dialog_bubble_bitmap_identifier); // TODO: this may need to be after init
   initialized = true;
   return;
}

void NPCConversations::destroy()
{
   if (capture) al_destroy_bitmap(capture);
   return;
}

void NPCConversations::refresh_capture()
{
   if (capture) al_destroy_bitmap(capture);
   capture = AllegroFlare::ScreenCapture::create_backbuffer_capture_as_scaled_bitmap(
      1920/inv_scale,
      1080/inv_scale
   );
   return;
}

void NPCConversations::activate()
{
   refresh_capture();
   return;
}

void NPCConversations::render()
{
   if (capture)
   {
      al_draw_scaled_bitmap(
         capture,
         0,
         0,
         al_get_bitmap_width(capture),
         al_get_bitmap_height(capture),
         0,
         0,
         1920,
         1080,
         0
      );
   }

   ALLEGRO_BITMAP *dialog_bubble_bitmap = bitmap_bin->auto_get(dialog_bubble_bitmap_identifier);
   if (dialog_bubble_bitmap)
   {
      al_draw_bitmap(dialog_bubble_bitmap, 0, 0, 0);
   }
}


} // namespace Backgrounds
} // namespace Elements
} // namespace ArtGalleryOfCats


