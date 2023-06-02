

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


EntityFactory::EntityFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void EntityFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void EntityFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::BitmapBin* EntityFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* EntityFactory::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::ModelBin* EntityFactory::get_model_bin() const
{
   return model_bin;
}


ArtGalleryOfCats::Gameplay::Entities::Base* EntityFactory::create_environment_mesh()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_environment_mesh]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_environment_mesh: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_environment_mesh]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_environment_mesh: error: guard \"model_bin\" not met");
   }
   ArtGalleryOfCats::Gameplay::Entities::Base* result = new ArtGalleryOfCats::Gameplay::Entities::Base();

   std::string model_filename = "agc-map-02.obj";
   model_bin->preload(model_filename);
   AllegroFlare::Model3D* model = model_bin->auto_get(model_filename);

   std::string texture_filename = "agc-map-02.png";
   bitmap_bin->preload(texture_filename);
   ALLEGRO_BITMAP *texture = bitmap_bin->auto_get(texture_filename);

   result->set_model(model);
   result->set_texture(texture);

   return result;
}

ArtGalleryOfCats::Gameplay::Entities::Camera3D* EntityFactory::create_camera()
{
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* result = new ArtGalleryOfCats::Gameplay::Entities::Camera3D();

   result->stepout = { 0, 1.0, 0 };
   //camera.stepout = {0, 1.0, 4};  // step back from the origin
   result->tilt = 0.13;            // look up(-)/down(+)
   result->spin = 0.0;             // set a good start initial spin
   //result->spin = 0.2;             // set a good start initial spin

   return result;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


