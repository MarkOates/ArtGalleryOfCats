

#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFlags.hpp>
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


void LevelFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void LevelFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


void LevelFactory::set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


AllegroFlare::BitmapBin* LevelFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* LevelFactory::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::SceneGraph::EntityPool* LevelFactory::get_entity_pool() const
{
   return entity_pool;
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
   ArtGalleryOfCats::Gameplay::Entities::Base* environment_mesh = entity_factory.create_environment_mesh(
      "gallery-map-05.obj",
      "gallery-map-05.png"
   );
   entity_pool->add(environment_mesh);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* collision_tile_map =
      entity_factory.create_collision_tile_map("tests/fixtures/maps/gallery-map-05.tmj");
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

   // Create a collectable
   ArtGalleryOfCats::Gameplay::Entities::Base* collectable_object = entity_factory.create_collectable_object(
      AllegroFlare::Vec3D(24.0, 0.5, 17.0),
      "rounded_unit_cube-01.obj"
   );
   entity_pool->add(collectable_object);

   // Create an art
   ArtGalleryOfCats::Gameplay::Entities::Base* art = entity_factory.create_art(
      "art-01",
      "art-01.obj",
      "art-01.png",
      { 14, 0, 12 },
      0.0f,
      {}
   );
   entity_pool->add(art);

   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


