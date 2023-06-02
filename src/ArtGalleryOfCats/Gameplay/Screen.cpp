

#include <ArtGalleryOfCats/Gameplay/Screen.hpp>

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

   // Create the environment
   ArtGalleryOfCats::Gameplay::Entities::Base* environment_mesh = entity_factory.create_environment_mesh();
   entity_pool.add(environment_mesh);

   // Create the camera, define it as the primary camera
   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   entity_pool.add(camera);

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
   for (auto &entity : entity_pool.get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);

      AllegroFlare::Placement3D &placement = as_agc_entity->get_placement_ref();
      AllegroFlare::Placement3D &velocity = as_agc_entity->get_velocity_ref();

      placement.position += velocity.position;
      placement.rotation += velocity.rotation;
   }

   // HACK: Extract out the camera and assign it's position
   // TODO: Create a separate entity, then assign the camera values to the live camera (or something)
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool.find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("no camera present");
   ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);
   as_camera->AllegroFlare::Camera3D::position = as_camera->get_placement_ref().position;

   return;
}

void Screen::render()
{
   scene_renderer_render();
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


} // namespace Gameplay
} // namespace ArtGalleryOfCats


