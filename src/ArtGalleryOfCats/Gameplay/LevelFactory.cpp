

#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFlags.hpp>
#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>
#include <ArtGalleryOfCats/Gameplay/TMJObjectLoader.hpp>
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


void LevelFactory::object_parsed_callback(std::string name_property, std::string class_property, float x_property, float y_property, float width_property, float height_property, std::vector<std::pair<std::string, std::string>> custom_properties, void* user_data)
{
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[LevelFactory::object_parsed_callback]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelFactory::object_parsed_callback: error: guard \"user_data\" not met");
   }
   ArtGalleryOfCats::Gameplay::LevelFactory *this_factory =
      static_cast<ArtGalleryOfCats::Gameplay::LevelFactory*>(user_data);
   AllegroFlare::SceneGraph::EntityPool &entity_pool = *(this_factory->entity_pool);
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   entity_factory.set_model_bin(this_factory->model_bin);
   entity_factory.set_bitmap_bin(this_factory->bitmap_bin);

   if (class_property == "sculpture")
   {
      AllegroFlare::Physics::AABB2D hit_box_2d(x_property, y_property, width_property, height_property);

      ArtGalleryOfCats::Gameplay::Entities::Base* art = entity_factory.create_sculpture_art(
         name_property, //"art-01",
         "art-02.obj",
         "art-01.png",
         { x_property + width_property * 0.5f, 0, y_property + height_property * 0.5f },
         0.0f,
         hit_box_2d,
         {}
      );
      entity_pool.add(art);
   }
   else if (class_property == "wall_art")
   {
      float rotation = 0.0f;
      float wall_art_scale = ArtGalleryOfCats::Gameplay::EntityFactory::DEFAULT_WALL_ART_SCALE;
      std::string image_identifier = "storyboard-2-01-1165x500.png";

      AllegroFlare::Physics::AABB2D hit_box_2d(x_property, y_property, width_property, height_property);

      // extract custom properties
      std::cout << "-- num_custom_properties: " << custom_properties.size() << std::endl;
      for (auto &custom_property : custom_properties)
      {
         std::cout << "  - first: " << custom_property.first << std::endl;
         std::cout << "    second: " << custom_property.second << std::endl;
         if (custom_property.first == "facing")
         {
            std::string facing_direction = custom_property.second;
            if (facing_direction == "down") rotation = 0.0f;
            else if (facing_direction == "right") rotation = 0.25f;
            else if (facing_direction == "left") rotation = -0.25f;
            else if (facing_direction == "up") rotation = 0.5f;
            else
            {
               throw std::runtime_error("Gameplay::LevelFactory: unrecognized \"facing\" value.");
            }
         }
         if (custom_property.first == "image_identifier")
         {
            image_identifier = custom_property.second;
         }
      }

      std::cout << "   rotation: " << rotation << std::endl;

      ArtGalleryOfCats::Gameplay::Entities::Base* art = entity_factory.create_wall_art(
         name_property, //"art1",
         image_identifier,
         { x_property + width_property * 0.5f, 1.0, y_property + height_property * 0.5f },
         rotation,
         wall_art_scale,
         hit_box_2d,
         {}
      );
      entity_pool.add(art);
   }
   else
   {
      // TODO: Thrown on unknonw type
   }

   //if (custom_properties.size()

   // TODO: This function
   return;
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

   // Define our source TMJ filename
   std::string tmj_source_filename = "tests/fixtures/maps/gallery-map-08.tmj";

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::Base* environment_mesh = entity_factory.create_environment_mesh(
      "gallery-map-05.obj",
      "gallery-map-05.png"
   );
   entity_pool->add(environment_mesh);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* collision_tile_map =
      entity_factory.create_collision_tile_map(tmj_source_filename);
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

   // Load objects from the TMJ file
   ArtGalleryOfCats::Gameplay::TMJObjectLoader tmj_object_loader(tmj_source_filename);
   tmj_object_loader.set_object_parsed_callback(object_parsed_callback);
   tmj_object_loader.set_object_parsed_callback_user_data(this);
   tmj_object_loader.load();

   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


