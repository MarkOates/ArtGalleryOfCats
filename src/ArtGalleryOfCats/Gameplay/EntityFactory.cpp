

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFlags.hpp>
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


ArtGalleryOfCats::Gameplay::Entities::Base* EntityFactory::create_environment_mesh(std::string model_filename, std::string texture_filename)
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

   //std::string model_filename = "gallery-map-02.obj";
   //std::string model_filename = "agc-map-04.obj";
   //model_bin->preload(model_filename);
   AllegroFlare::Model3D* model = model_bin->auto_get(model_filename);

   //std::string model_filename = "gallery-map-02.obj";
   //std::string texture_filename = "gallery-map-02.png";
   //std::string texture_filename = "agc-map-04.png";
   //bitmap_bin->preload(texture_filename);
   ALLEGRO_BITMAP *texture = bitmap_bin->auto_get(texture_filename);

   result->set_model(model);
   result->set_texture(texture);

   return result;
}

ArtGalleryOfCats::Gameplay::Entities::Base* EntityFactory::create_collectable_object(AllegroFlare::Vec3D position, std::string model_filename)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_collectable_object]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_collectable_object: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_collectable_object]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_collectable_object: error: guard \"model_bin\" not met");
   }
   ArtGalleryOfCats::Gameplay::Entities::Base* result = new ArtGalleryOfCats::Gameplay::Entities::Base();

   AllegroFlare::Model3D* model = model_bin->auto_get(model_filename);
   //ALLEGRO_BITMAP *texture = bitmap_bin->auto_get(texture_filename);

   result->set_model(model);
   //result->set_texture(texture);

   result->set(ArtGalleryOfCats::Gameplay::EntityFlags::RENDERS_WITH_IRIDESCENT);

   //object_placement.rotation.y += 0.001;
   //object_placement.rotation.x += 0.00073;
   result->get_velocity_ref().rotation.x = 0.001;
   result->get_velocity_ref().rotation.y = 0.00073;

   result->get_placement_ref().position = position;
   //result->get_placement_ref().position.y = 0.5; // so that the item is right at eye level
   result->get_placement_ref().scale = { 0.8, 0.8, 0.8 };

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

ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* EntityFactory::create_collision_tile_map(std::string tmj_filename)
{
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* result =
      new ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap();

   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = result->get_collision_tile_map_ref();
   collision_tile_map.initialize();

   //std::string tmj_filename = "tests/fixtures/maps/gallery-map-03.tmj"; // TODO: Fix this path
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();

   // Fill our map with the data loaded from the TMJ file
   int num_columns = tmj_data_loader.get_num_columns();
   int num_rows = tmj_data_loader.get_num_columns();
   collision_tile_map.resize(num_columns, num_rows);

   std::vector<int> contiguous_collision_layer_tile_data = tmj_data_loader.get_collision_layer_tile_data();
   // Gut check:
   if (contiguous_collision_layer_tile_data.size() != collision_tile_map.infer_num_tiles())
   {
      throw std::runtime_error("Maps are of unequal dimensions");
   }

   for (int i=0; i<contiguous_collision_layer_tile_data.size(); i++)
   {
      collision_tile_map.set_contiguous_tile(i, contiguous_collision_layer_tile_data[i]);
   }

   return result;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


