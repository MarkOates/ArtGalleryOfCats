

#include <ArtGalleryOfCats/Gameplay/Screen.hpp>

#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFlags.hpp>
#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>
#include <ArtGalleryOfCats/Gameplay/SceneRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, std::string resources_path, AllegroFlare::SceneGraph::EntityPool entity_pool, ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen)
   : AllegroFlare::Screens::Base(ArtGalleryOfCats::Gameplay::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , resources_path(resources_path)
   , entity_pool(entity_pool)
   , user_text_input_screen(user_text_input_screen)
   , current_riddle()
   , riddle_is_solved(false)
   , last_user_text_input_value("")
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , player_velocity({})
   , player_right_pressed(false)
   , player_left_pressed(false)
   , player_up_pressed(false)
   , player_down_pressed(false)
   , entity_player_is_currently_colliding_with(nullptr)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , cubemap_shader({})
   , cubemap(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle)
{
   this->current_riddle = current_riddle;
}


void Screen::set_riddle_is_solved(bool riddle_is_solved)
{
   this->riddle_is_solved = riddle_is_solved;
}


void Screen::set_last_user_text_input_value(std::string last_user_text_input_value)
{
   this->last_user_text_input_value = last_user_text_input_value;
}


void Screen::set_entity_player_is_currently_colliding_with(AllegroFlare::SceneGraph::Entities::Base* entity_player_is_currently_colliding_with)
{
   this->entity_player_is_currently_colliding_with = entity_player_is_currently_colliding_with;
}


void Screen::set_on_finished_callback_func(std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Screen::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


ArtGalleryOfCats::Gameplay::Riddle Screen::get_current_riddle() const
{
   return current_riddle;
}


bool Screen::get_riddle_is_solved() const
{
   return riddle_is_solved;
}


std::string Screen::get_last_user_text_input_value() const
{
   return last_user_text_input_value;
}


AllegroFlare::SceneGraph::Entities::Base* Screen::get_entity_player_is_currently_colliding_with() const
{
   return entity_player_is_currently_colliding_with;
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
}

void Screen::set_resources_path(std::string resources_path)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_resources_path]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_resources_path: error: guard \"(!initialized)\" not met");
   }
   this->resources_path = resources_path;
   return;
}

void Screen::set_user_text_input_screen(ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_user_text_input_screen]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_user_text_input_screen: error: guard \"(!initialized)\" not met");
   }
   this->user_text_input_screen = user_text_input_screen;
   return;
}

void Screen::load_level_by_identifier(std::string level_identifier)
{
   // Destroy the current level (if one exists)
   if (current_level)
   {
      std::cout << "INFO: Destroying current level" << std::endl;
      current_level->destroy(); // TODO: Make sure this is implemented
      delete (int*)(current_level);
      current_level = nullptr;
      current_level_identifier = "[no-current_level_identifier]";
   }

   // Create a new Level object, and make it the "current_level"
   current_level = new ArtGalleryOfCats::Gameplay::Level;
   current_level_identifier = level_identifier;

   // Load the level
   // TODO: Destroy current level
   // TODO: Create new level class
   // TODO: Pass new level class properties into factory

   ArtGalleryOfCats::Gameplay::LevelFactory level_factory;
   level_factory.set_model_bin(model_bin);
   level_factory.set_bitmap_bin(bitmap_bin);
   level_factory.set_entity_pool(&entity_pool);
   level_factory.set_riddle(&current_riddle);


   std::map<std::string, std::function<void()>> items_map = {
      { "gallery_01", [this, &level_factory](){
         level_factory.load_gallery_01();
      }},
      { "gallery_02", [this, &level_factory](){
         // TODO: Replace this with new map
         level_factory.load_gallery_02();
      }},
   };


   // locate and call the function to handle the item
   if (items_map.count(level_identifier) == 0)
   {
      // item not found
      std::stringstream error_message;
      error_message << "[CubeShooter::LevelFactory::load_level_by_identifier]: error: Cannot find item with the level_identifier\""
                    << level_identifier << "\", it does not exist.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      // call the item
      items_map[level_identifier]();
   }


   // TODO: Show gallery name


   return;
}

AllegroFlare::SceneGraph::EntityPool* Screen::get_entity_pool()
{
   // TODO: Add "guards: [ current_level ]"
   return &entity_pool; // TODO: Swap this out with the current level entity_pool (comment below)
   //return &current_level->get_entity_pool_ref();
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
   if (!((resources_path != DEFAULT_RESOURCES_PATH)))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"(resources_path != DEFAULT_RESOURCES_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"(resources_path != DEFAULT_RESOURCES_PATH)\" not met");
   }
   // TODO: Fix this section
   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = resources_path + "bitmaps/black_prism_1-01.png";
   //std::string cube_map_texture_filename = "fixtures/bitmaps/black_prism_1-01.png"; // TODO: set the correct location
   cubemap = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

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
   if (riddle_is_solved)
   {
      // Note: NPC dialog, after solving the riddle, will return back to this screen.
      // TODO: Progress to the next level
      event_emitter->emit_game_event(AllegroFlare::GameEvent("riddle_is_solved"));
         //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER,
         //new AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier("user_text_input_screen")
      //);
   }

   bool need_to_handle_user_text_input = !last_user_text_input_value.empty();
   if (need_to_handle_user_text_input)
   {
      bool answer_is_correct = false;
      //std::cout << "*** Handle user input text \"" << last_user_text_input_value << "\"" << std::endl;

      // Evaluate if answer is correct, depending on the current riddle, and the player's last input
      answer_is_correct = current_riddle.matches_answer(last_user_text_input_value);

      // Clear our copy of the user input
      last_user_text_input_value.clear();

      if (!answer_is_correct)
      {
         // TODO: Sort out what reaction should be when answer is incorrect
         // TODO: Set npc dialog to say "hmm, that's not correct"
         trigger_npc_dialog(); // DEVELOPMENT
      }
      else
      {
         // TODO: Sort out what reaction should be when answer is correct
         // TODO: Set npc dialog to say "That's correct! Nice job!"

         event_emitter->emit_event(
            ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT,
            intptr_t(new std::string("solve_a_riddle"))
         );

         riddle_is_solved = true;

         trigger_npc_dialog(); // DEVELOPMENT
      }
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

AllegroFlare::Vec3D Screen::calculate_strafe_xy(float spin, float displacement)
{
   type: AllegroFlare::Vec3D result;
   AllegroFlare::Vec2D move_vec(cos(spin), sin(spin));
   result.x = move_vec.x * displacement;
   result.y = 0;
   result.z = move_vec.y * displacement;
   return result;
     
}

AllegroFlare::Vec3D Screen::calculate_forward_back_xy(float spin, float displacement)
{
   type: AllegroFlare::Vec3D result;
   AllegroFlare::Vec2D move_vec(-sin(spin), cos(spin));
   result.x = move_vec.x * displacement;
   result.y = 0;
   result.z = move_vec.y * displacement;
   return result;
}

ArtGalleryOfCats::Gameplay::Entities::Camera3D* Screen::find_primary_camera()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::find_primary_camera]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::find_primary_camera: error: guard \"get_entity_pool()\" not met");
   }
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;
   // Extract our out camera
   entity = get_entity_pool()->find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("find_primary_camera: no camera present");
   ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

   return as_camera;
}

ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* Screen::find_collision_tile_map()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::find_collision_tile_map]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::find_collision_tile_map: error: guard \"get_entity_pool()\" not met");
   }
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;
   // Extract our out collision_tile_map
   entity = get_entity_pool()->find_with_attribute("collision_tile_map");
   if (!entity) throw std::runtime_error("no collision_tile_map present");
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *as_collision_tile_map =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap*>(entity);

   return as_collision_tile_map;
}

void Screen::update_entity_player_is_currently_colliding_with()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_entity_player_is_currently_colliding_with]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_entity_player_is_currently_colliding_with: error: guard \"get_entity_pool()\" not met");
   }
   // TODO: Implement this function
   //entity_player_is_currently_colliding_with

   // Select all the entities that the player can collide with
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> entities_player_can_interact_with =
      get_entity_pool()->select_A(ArtGalleryOfCats::Gameplay::EntityFlags::PLAYER_CAN_INTERACT);


   float player_hit_box_size = 1.6;
   float player_h_hit_box_size = player_hit_box_size * 0.5;
   AllegroFlare::Vec3D player_position = find_primary_camera()->get_placement_ref().position;
   AllegroFlare::Physics::AABB2D player_hit_box_2d(
      player_position.x - player_h_hit_box_size,
      player_position.z - player_h_hit_box_size,
      player_hit_box_size,
      player_hit_box_size,
      0,
      0
   );

   // Find the entity that the player, in this frame, is colliding with (find the first one)
   ArtGalleryOfCats::Gameplay::Entities::Base *found_colliding_entity = nullptr;
   for (auto &entity_player_can_interact_with : entities_player_can_interact_with)
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity_player_can_interact_with);

      // TODO: do AABB2D collision against the player
      bool player_collides_with_this_entity = player_hit_box_2d.collides(&as_agc_entity->get_hit_box_2d_ref());
      //AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
      if (player_collides_with_this_entity)
      {
         found_colliding_entity = as_agc_entity;
         break;
      }
   }

   if (found_colliding_entity != entity_player_is_currently_colliding_with)
   {
      // Assign the found entity to be the colliding one
      entity_player_is_currently_colliding_with = found_colliding_entity;

      // TODO: Some feedback that a new collision occurred
      if (entity_player_is_currently_colliding_with != nullptr) interact_with_focused_object(); // DEVELOPMENT
   }

   return;
}

void Screen::scene_physics_updater()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::scene_physics_updater]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::scene_physics_updater: error: guard \"get_entity_pool()\" not met");
   }
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;

   // Extract our out camera
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* as_camera = find_primary_camera();

   // Update our camera velocity to match the "player_velocity"
   player_velocity = infer_player_velocity_from_keypress();
   AllegroFlare::Vec3D camera_strafe_speed = calculate_strafe_xy(as_camera->spin, player_velocity.x);
   AllegroFlare::Vec3D camera_forward_back_speed = calculate_forward_back_xy(as_camera->spin, player_velocity.y);
   as_camera->get_velocity_ref().position = camera_strafe_speed + camera_forward_back_speed;

   // Extract out the collision map
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* as_collision_tile_map = find_collision_tile_map();

   // Create our collision stepper
   AllegroFlare::Physics::TileMapCollisionStepper collision_stepper;
   collision_stepper.set_collision_tile_map(&as_collision_tile_map->get_collision_tile_map_ref());
   collision_stepper.set_tile_width(1);
   collision_stepper.set_tile_height(1);

   float box_size = 1.4;
   float box_h_size = box_size * 0.5f;
   for (auto &entity : get_entity_pool()->get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);
      AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
      AllegroFlare::Placement3D &velocity = as_agc_entity->get_velocity_ref();

      AllegroFlare::Physics::AABB2D aabb2d(
         placement.position.x - box_h_size,
         placement.position.z - box_h_size,
         box_size, // Each object will have the size of the "box_size"
         box_size,
         velocity.position.x,
         velocity.position.z
      );

      collision_stepper.set_aabb2d(&aabb2d);

      std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> stepper_step_result =
         collision_stepper.step();

      placement.position = AllegroFlare::Vec3D(
         aabb2d.get_x() + box_h_size,
         placement.position.y,
         aabb2d.get_y() + box_h_size
      );
      velocity.position = { aabb2d.get_velocity_x(), 0.0f, aabb2d.get_velocity_y() };
      placement.rotation += velocity.rotation;
   }

   update_entity_player_is_currently_colliding_with();

   // HACK: Extract out the camera and assign it's position
   // TODO: Create a separate entity, then assign the camera values to the live camera (or something)
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
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::scene_renderer_render]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::scene_renderer_render: error: guard \"get_entity_pool()\" not met");
   }
   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
   scene_renderer.set_entity_pool(get_entity_pool());
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.render();
   return;
}

void Screen::render_hud()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[Screen::render_hud]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::render_hud: error: guard \"get_entity_pool()\" not met");
   }
   // Local vars;
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;

   AllegroFlare::Camera2D hud_camera;
   ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   hud_camera.setup_dimentional_projection(render_surface);

   hud_camera.position.x = -800;
   hud_camera.position.y = -400;

   hud_camera.start_reverse_transform();
   //hud_camera.start_transform();

   //ALLEGRO_FONT *font = al_create_builtin_font();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, ALLEGRO_ALIGN_LEFT, ".ul");
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920-10, 1080-10, ALLEGRO_ALIGN_RIGHT, "br.");


   // Render the mini-map
   bool render_mini_map = false;

   if (render_mini_map)
   {
      // Extract out the collision map
      ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* as_collision_tile_map = find_collision_tile_map();
      AllegroFlare::TileMaps::TileMap<int> &collision_tile_map= as_collision_tile_map->get_collision_tile_map_ref();



      render_tile_map(&collision_tile_map, 16.0f, 16.0f);


      for (auto &entity : get_entity_pool()->get_entity_pool_ref())
      {
         ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
            static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);
         AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
         //AllegroFlare::Placement3D &velocity = as_agc_entity->get_velocity_ref();

         AllegroFlare::Physics::AABB2D aabb2d(
            placement.position.x * 16 - (16 * 0.5),
            placement.position.z * 16 - (16 * 0.5),
            16.0, // Our object will be a 1x1 square
            16.0
            //velocity.position.x,
            //velocity.position.z
         );

         render_aabb2d(
                  &aabb2d
               );

         al_draw_filled_circle(placement.position.x * 16, placement.position.z * 16, 8, ALLEGRO_COLOR{0, 1, 0.8, 1.0});
      }
   }

   hud_camera.restore_transform();

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
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* as_camera = find_primary_camera();

   as_camera->spin += delta;
   return;
}

void Screen::player_tilt_change(float delta)
{
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* as_camera = find_primary_camera();

   //as_camera->tilt += delta;
   float tilt = as_camera->tilt;

   tilt += delta;
   float max_tilt = 3.14 / 2;
   if (tilt < -max_tilt) tilt = -max_tilt;
   if (tilt > max_tilt) tilt = max_tilt;
   as_camera->tilt = tilt;
   return;
}

void Screen::player_stop_moving()
{
   player_up_pressed = false;
   player_down_pressed = false;
   player_left_pressed = false;
   player_right_pressed = false;
   player_velocity.x = 0;
   player_velocity.y = 0;
   return;
}

AllegroFlare::Vec2D Screen::infer_player_velocity_from_keypress()
{
   AllegroFlare::Vec2D result = { 0, 0 };
   float speed = 0.1;

   if (player_left_pressed && player_right_pressed) result.x = 0.0f;
   else if (player_left_pressed) result.x = -speed;
   else if (player_right_pressed) result.x = speed;

   if (player_up_pressed && player_down_pressed) result.y = 0.0f;
   else if (player_up_pressed) result.y = -speed;
   else if (player_down_pressed) result.y = speed;

   return result;
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

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT: {
         player_left_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         player_right_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         player_up_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         player_down_pressed = false;
      } break;

      default: {
         // TODO: IMPORTANT: There is currently no escape from gameplay/screen
         //call_on_finished_callback_func();
      } break;
   };

   //player_stop_moving(); // TODO: Improve this movement
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
         player_left_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         player_right_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         player_up_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         player_down_pressed = true;
      } break;

      default: {
         // TODO: IMPORTANT: There is currently no escape from gameplay/screen
         //call_on_finished_callback_func();
      } break;
   };

   return;
}

void Screen::trigger_npc_dialog()
{
   // TODO: Set the npc avatar for this dialog
   // TODO: Setup an npc name, and add it to this dialog
   // TODO: Set the text pages for this dialog
   event_emitter->emit_router_event(
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER,
      new AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier("npc_conversations_screen")
   );
   return;
}

void Screen::interact_with_focused_object()
{
   if (!entity_player_is_currently_colliding_with)
   {
      // TODO: play a sound that indicates there is nothing to interact with
      return;
   }

   player_stop_moving();

   trigger_npc_dialog(); // DEVELOPMENT

   //event_emitter->talk_to_an_npc
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT,
      intptr_t(new std::string("look_at_some_art"))
   );
   return;
}

void Screen::prompt_user_for_text_input()
{
   if (!(user_text_input_screen))
   {
      std::stringstream error_message;
      error_message << "[Screen::prompt_user_for_text_input]: error: guard \"user_text_input_screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::prompt_user_for_text_input: error: guard \"user_text_input_screen\" not met");
   }
   player_stop_moving();

   // Set the prompt on the user text input screen
   // TODO: Make this value dynamic
   std::string riddle_prompt_text = current_riddle.get_riddle_prompt_text();
   user_text_input_screen->set_prompt_text(riddle_prompt_text);

   // Clear our value
   last_user_text_input_value.clear();

   // TODO: setup the prompt screen with context

   event_emitter->emit_router_event(
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER,
      new AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier("user_text_input_screen") // TODO: use constant
   );
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

void Screen::emit_event_to_return_to_the_level_select_screen()
{
   event_emitter->emit_router_event(
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_LEVEL_SELECT_SCREEN,
      nullptr,
      al_get_time()
   );
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_down_func: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_down_func: error: guard \"event_emitter\" not met");
   }
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_W: {
         player_up_pressed = true;
      } break;

      case ALLEGRO_KEY_A: {
         player_left_pressed = true;
      } break;

      case ALLEGRO_KEY_S: {
         player_down_pressed = true;
      } break;

      case ALLEGRO_KEY_D: {
         player_right_pressed = true;
      } break;

      case ALLEGRO_KEY_I: {
         prompt_user_for_text_input(); // DEVELOPMENT
      } break;

      case ALLEGRO_KEY_ESCAPE: {
         emit_event_to_return_to_the_level_select_screen();
         //prompt_user_for_text_input(); // DEVELOPMENT
      } break;

      case ALLEGRO_KEY_SPACE:
      case ALLEGRO_KEY_ENTER:
      case ALLEGRO_KEY_X: {
         interact_with_focused_object();
      } break;

      default: {
         // Nothing here
      } break;
   }

   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_up_func: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_up_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_up_func: error: guard \"event_emitter\" not met");
   }
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_W: {
         player_up_pressed = false;
      } break;

      case ALLEGRO_KEY_A: {
         player_left_pressed = false;
      } break;

      case ALLEGRO_KEY_S: {
         player_down_pressed = false;
      } break;

      case ALLEGRO_KEY_D: {
         player_right_pressed = false;
      } break;

      default: {
         // Nothing here
      } break;
   }

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
   float tilt_delta = ev->mouse.dy;
   float spin_multiplier = 0.001;
   float tilt_multiplier = 0.001;
   player_spin_change(spin_delta * spin_multiplier);
   player_tilt_change(tilt_delta * tilt_multiplier);
   //float x_delta = ev->mouse->dx;
   //result->tilt = 0.13;            // look up(-)/down(+)
   //result->spin = 0.2;             // set a good start initial spin
   // TODO: this function
   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


