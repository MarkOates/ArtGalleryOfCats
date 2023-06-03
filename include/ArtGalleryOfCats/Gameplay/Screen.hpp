#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Shaders/Cubemap.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <ArtGalleryOfCats/Gameplay/Screen.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class Screen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Gameplay/Screen";
         static constexpr char* DEFAULT_RESOURCES_PATH = (char*)"[unset-resources_path]";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         std::string resources_path;
         AllegroFlare::SceneGraph::EntityPool entity_pool;
         std::string current_level_identifier;
         void* current_level;
         AllegroFlare::Vec2D player_velocity;
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         AllegroFlare::Shaders::Cubemap cubemap_shader;
         AllegroFlare::Cubemap* cubemap;
         bool initialized;
         void load_level();
         void scene_physics_updater();
         void scene_renderer_render();
         void render_hud();

      protected:


      public:
         Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, std::string resources_path=DEFAULT_RESOURCES_PATH, AllegroFlare::SceneGraph::EntityPool entity_pool={});
         virtual ~Screen();

         void set_on_finished_callback_func(std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void set_resources_path(std::string resources_path=DEFAULT_RESOURCES_PATH);
         void load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         void render_tile_map(AllegroFlare::TileMaps::TileMap<int>* tile_map=nullptr, float tile_width=16.0f, float tile_height=16.0f);
         void render_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d=nullptr, bool adjacent_to_top_edge=false, bool adjacent_to_right_edge=false, bool adjacent_to_bottom_edge=false, bool adjacent_to_left_edge=false);
         void call_on_finished_callback_func();
         virtual void primary_timer_func() override;
         void player_spin_change(float delta=0.0f);
         void player_tilt_change(float delta=0.0f);
         void player_stop_moving();
         void player_strafe_right();
         void player_strafe_left();
         void player_move_forward();
         void player_move_backward();
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_axes_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



