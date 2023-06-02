

#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


LevelFactory::LevelFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::SceneGraph::EntityPool* entity_pool)
   : bitmap_bin(bitmap_bin)
   , model_bin(model_bin)
   , entity_pool(entity_pool)
{
}


LevelFactory::~LevelFactory()
{
}


void LevelFactory::load_primary_map()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[LevelFactory::load_primary_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelFactory::load_primary_map: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[LevelFactory::load_primary_map]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelFactory::load_primary_map: error: guard \"model_bin\" not met");
   }
   if (!(entity_pool))
   {
      std::stringstream error_message;
      error_message << "[LevelFactory::load_primary_map]: error: guard \"entity_pool\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelFactory::load_primary_map: error: guard \"entity_pool\" not met");
   }
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   entity_factory.set_model_bin(model_bin);
   entity_factory.set_bitmap_bin(bitmap_bin);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::Base* environment_mesh = entity_factory.create_environment_mesh();
   entity_pool->add(environment_mesh);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* collision_tile_map =
      entity_factory.create_collision_tile_map();
   collision_tile_map->set("collision_tile_map");
   entity_pool->add(collision_tile_map);

   // Create the camera, define it as the primary camera
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   entity_pool->add(camera);

   // Move our camera to the "spawn point"
   AllegroFlare::Vec2D spawn_point = { 11, 18 }; // TODO: Update this spawn point to pull from map
   camera->get_placement_ref().position.x = spawn_point.x;
   camera->get_placement_ref().position.z = spawn_point.y;

   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


