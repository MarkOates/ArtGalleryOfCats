

#include <ArtGalleryOfCats/Gameplay/Screen.hpp>

#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::SceneGraph::EntityPool entity_pool)
   : AllegroFlare::Screens::Base(ArtGalleryOfCats::Gameplay::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , entity_pool(entity_pool)
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_on_finished_callback_func(std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Screen::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> Screen::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Screen::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
   return;
}

void Screen::load_level_by_identifier(std::string level_identifier)
{
   current_level_identifier = level_identifier;
   if (current_level) delete (int*)(current_level);
   current_level = (void*)(new int(3));

   load_level(); // TODO: replace this with name of level
   return;
}

void Screen::load_level()
{
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   entity_factory.set_model_bin(model_bin);
   entity_factory.set_bitmap_bin(bitmap_bin);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::Base* environment_mesh = entity_factory.create_environment_mesh();
   entity_pool.add(environment_mesh);

   // Create the environment visual mesh
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* collision_tile_map =
      entity_factory.create_collision_tile_map();
   collision_tile_map->set("collision_tile_map");
   entity_pool.add(collision_tile_map);

   // Create the camera, define it as the primary camera
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   entity_pool.add(camera);

   // Move our camera to the "spawn point"
   AllegroFlare::Vec2D spawn_point = { 11, 18 }; // TODO: Update this spawn point to pull from map
   camera->get_placement_ref().position.x = spawn_point.x;
   camera->get_placement_ref().position.z = spawn_point.y;

   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"model_bin\" not met");
   }
   initialized = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::update()
{
   scene_physics_updater();
   return;
}

void Screen::scene_physics_updater()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;

   // Extract out the collision map
   entity = entity_pool.find_with_attribute("collision_tile_map");
   if (!entity) throw std::runtime_error("no collision_tile_map present");
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *as_collision_tile_map =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap*>(entity);

   // Create our collision stepper
   AllegroFlare::Physics::TileMapCollisionStepper collision_stepper;
   collision_stepper.set_collision_tile_map(&as_collision_tile_map->get_collision_tile_map_ref());

   float box_h_size = 0.5;
   for (auto &entity : entity_pool.get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);
      AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
      AllegroFlare::Placement3D &velocity = as_agc_entity->get_velocity_ref();

      AllegroFlare::Physics::AABB2D aabb2d(
         placement.position.x,
         placement.position.z,
         1.0, // Our object will be a 1x1 square
         1.0,
         velocity.position.x,
         velocity.position.z
      );

      collision_stepper.set_aabb2d(&aabb2d);

      std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> stepper_step_result =
         collision_stepper.step();

      placement.position = AllegroFlare::Vec3D(aabb2d.get_x(), 0.0f, aabb2d.get_y());
      velocity.position = { aabb2d.get_velocity_x(), 0.0f, aabb2d.get_velocity_y() };
      //placement.rotation += velocity.rotation; // TODO: Uncomment this
   }

   // HACK: Extract out the camera and assign it's position
   // TODO: Create a separate entity, then assign the camera values to the live camera (or something)
   entity = entity_pool.find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("no camera present");
   ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);
   as_camera->AllegroFlare::Camera3D::position = as_camera->get_placement_ref().position;

   return;
}

void Screen::render()
{
   scene_renderer_render();
   render_hud();
   return;
}

void Screen::scene_renderer_render()
{
   // Extract out the camera and render the scene
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("no camera present");
   ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

   ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   al_clear_depth_buffer(1);
   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

   as_camera->setup_projection_on(render_surface);

   // TODO: validate the camera is of type Entities::Camera
   // TODO: here

   //std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*>
   for (auto &entity : entity_pool.get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);

      AllegroFlare::Model3D *model = as_agc_entity->get_model();
      if (model)
      {
         ALLEGRO_BITMAP *texture = as_agc_entity->get_texture();
         if (texture) model->set_texture(texture);
         model->draw();
      }
   }

   //as_camera->start_reverse_transform();
   return;
}

void Screen::render_hud()
{
   // Local vars;
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;

   AllegroFlare::Camera2D hud_camera;
   ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   hud_camera.setup_dimentional_projection(render_surface);
   //hud_camera.start_transform();

   //ALLEGRO_FONT *font = al_create_builtin_font();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, ALLEGRO_ALIGN_LEFT, ".ul");
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920-10, 1080-10, ALLEGRO_ALIGN_RIGHT, "br.");


   // Extract out the collision map
   entity = entity_pool.find_with_attribute("collision_tile_map");
   if (!entity) throw std::runtime_error("no collision_tile_map present");
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *as_collision_tile_map=
      static_cast<ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap*>(entity);
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map= as_collision_tile_map->get_collision_tile_map_ref();



   render_tile_map(&collision_tile_map, 16.0f, 16.0f);


   for (auto &entity : entity_pool.get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);
      AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
      //AllegroFlare::Placement3D &velocity = as_agc_entity->get_velocity_ref();

      AllegroFlare::Physics::AABB2D aabb2d(
         placement.position.x,
         placement.position.z,
         1.0, // Our object will be a 1x1 square
         1.0
         //velocity.position.x,
         //velocity.position.z
      );

      render_aabb2d(
               &aabb2d
            );
   }



   //render_tile_map(&collision_tile_map, 16.0f, 16.0f);
   //render_aabb2d(
               //aabb2d,
               //aabb2d_adjacent_to_top_edge,
               //aabb2d_adjacent_to_right_edge,
               //aabb2d_adjacent_to_bottom_edge,
               //aabb2d_adjacent_to_left_edge
            //);


   //hud_camera.restore_transform();

   /*
   AllegroFlare::Placement2D camera;
   camera.scale.x = 4.8;
   camera.scale.y = 4.5;


   camera.start_transform();
   render_tile_map(collision_tile_map, 16.0f, 16.0f);
   camera.restore_transform();
   */

    /*
         { // draw
            //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            camera.start_transform();
            render_tile_map(collision_tile_map, 16.0f, 16.0f);
            render_aabb2d(
               aabb2d,
               aabb2d_adjacent_to_top_edge,
               aabb2d_adjacent_to_right_edge,
               aabb2d_adjacent_to_bottom_edge,
               aabb2d_adjacent_to_left_edge
            );
            camera.restore_transform();
            al_flip_display();
   */



   return;
}

void Screen::render_tile_map(AllegroFlare::TileMaps::TileMap<int>* tile_map, float tile_width, float tile_height)
{
   if (!(tile_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::render_tile_map]: error: guard \"tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::render_tile_map: error: guard \"tile_map\" not met");
   }
   if (!al_is_primitives_addon_initialized()) throw std::runtime_error("render_tile_map: primitives must be init");

   for (int y=0; y<tile_map->get_num_rows(); y++)
   {
      for (int x=0; x<tile_map->get_num_columns(); x++)
      {
         int tile_type = tile_map->get_tile(x, y);
         switch(tile_type)
         {
            case 0:
              //al_draw_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.2, 0.2, 0.21, 0.21}, 1.0);
            break;

            case 1:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.65, 0.62, 0.6, 1.0});
            break;

            default:
              //al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
   }
   return;
}

void Screen::render_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d, bool adjacent_to_top_edge, bool adjacent_to_right_edge, bool adjacent_to_bottom_edge, bool adjacent_to_left_edge)
{
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[Screen::render_aabb2d]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::render_aabb2d: error: guard \"aabb2d\" not met");
   }
   al_draw_filled_rectangle(aabb2d->get_x(), aabb2d->get_y(), aabb2d->get_right_edge(), aabb2d->get_bottom_edge(),
      ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});

   ALLEGRO_COLOR orange = ALLEGRO_COLOR{1.0, 0.5, 0.0, 1.0};

   /*
   if (adjacent_to_bottom_edge)
   {
      al_draw_line(aabb2d->get_x(), aabb2d->get_bottom_edge(), aabb2d->get_right_edge(), aabb2d->get_bottom_edge(), orange, 2.0);
   }
   if (adjacent_to_top_edge)
   {
      al_draw_line(aabb2d.get_x(), aabb2d.get_y(), aabb2d.get_right_edge(), aabb2d.get_y(), orange, 2.0);
   }
   if (adjacent_to_left_edge)
   {
      al_draw_line(aabb2d.get_x(), aabb2d.get_y(), aabb2d.get_x(), aabb2d.get_bottom_edge(), orange, 2.0);
   }
   if (adjacent_to_right_edge)
   {
      al_draw_line(aabb2d.get_right_edge(), aabb2d.get_y(), aabb2d.get_right_edge(), aabb2d.get_bottom_edge(), orange, 2.0);
   }
   */
   return;
}

void Screen::call_on_finished_callback_func()
{
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void Screen::player_spin_change(float delta)
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->spin += delta;
   return;
}

void Screen::player_stop_moving()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->get_velocity_ref().position.x = 0.0;
         as_camera->get_velocity_ref().position.z = 0.0;
   return;
}

void Screen::player_strafe_right()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->get_velocity_ref().position.x = 0.1;
   return;
}

void Screen::player_strafe_left()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->get_velocity_ref().position.x = -0.1;
   return;
}

void Screen::player_move_forward()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->get_velocity_ref().position.z = -0.1;
   return;
}

void Screen::player_move_backward()
{
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
         if (!entity) throw std::runtime_error("virtual_controls: no camera present");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

         as_camera->get_velocity_ref().position.z = 0.1;
   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   player_stop_moving(); // TODO: Improve this movement
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: validate virtual controller type

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT: {
         player_strafe_left();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         player_strafe_right();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         player_move_forward();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         player_move_backward();
      } break;

      default: {
         // TODO: IMPORTANT: There is currently no escape from gameplay/screen
         //call_on_finished_callback_func();
      } break;
   };

   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   //if (ev->mouse
   //result->tilt = 0.13;            // look up(-)/down(+)
   //result->spin = 0.2;             // set a good start initial spin
   // TODO: this function
   return;
}

void Screen::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::mouse_axes_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::mouse_axes_func: error: guard \"initialized\" not met");
   }
   // TODO: Validate spin change
   float spin_delta = ev->mouse.dx;
   float spin_multiplier = 0.001;
   player_spin_change(spin_delta * spin_multiplier);
   //float x_delta = ev->mouse->dx;
   //result->tilt = 0.13;            // look up(-)/down(+)
   //result->spin = 0.2;             // set a good start initial spin
   // TODO: this function
   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


