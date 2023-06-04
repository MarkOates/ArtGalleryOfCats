#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Shaders/Cubemap.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap.hpp>
#include <ArtGalleryOfCats/Gameplay/Level.hpp>
#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>
#include <ArtGalleryOfCats/Gameplay/Screen.hpp>
#include <ArtGalleryOfCats/Screens/UserTextInput.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
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
         ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen;
         bool riddle_is_solved;
         bool riddle_is_showing;
         bool inspect_hint_is_showing;
         std::string last_user_text_input_value;
         std::string current_level_identifier;
         ArtGalleryOfCats::Gameplay::Level* current_level;
         AllegroFlare::Vec2D player_velocity;
         bool player_right_pressed;
         bool player_left_pressed;
         bool player_up_pressed;
         bool player_down_pressed;
         AllegroFlare::SceneGraph::Entities::Base* entity_player_is_currently_colliding_with;
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         AllegroFlare::Shaders::Cubemap cubemap_shader;
         AllegroFlare::Cubemap* cubemap;
         bool initialized;
         void scene_physics_updater();
         void scene_renderer_render();
         void render_hud();

      protected:


      public:
         Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, std::string resources_path=DEFAULT_RESOURCES_PATH, ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen=nullptr);
         virtual ~Screen();

         void set_riddle_is_solved(bool riddle_is_solved);
         void set_riddle_is_showing(bool riddle_is_showing);
         void set_inspect_hint_is_showing(bool inspect_hint_is_showing);
         void set_last_user_text_input_value(std::string last_user_text_input_value);
         void set_entity_player_is_currently_colliding_with(AllegroFlare::SceneGraph::Entities::Base* entity_player_is_currently_colliding_with);
         void set_on_finished_callback_func(std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         bool get_riddle_is_solved() const;
         bool get_riddle_is_showing() const;
         bool get_inspect_hint_is_showing() const;
         std::string get_last_user_text_input_value() const;
         AllegroFlare::SceneGraph::Entities::Base* get_entity_player_is_currently_colliding_with() const;
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void set_resources_path(std::string resources_path=DEFAULT_RESOURCES_PATH);
         void set_user_text_input_screen(ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen=nullptr);
         void load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         void start_level_music();
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool();
         ArtGalleryOfCats::Gameplay::Riddle* get_current_riddle();
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         AllegroFlare::Vec3D calculate_strafe_xy(float spin=0.0f, float displacement=0.0f);
         AllegroFlare::Vec3D calculate_forward_back_xy(float spin=0.0f, float displacement=0.0f);
         ArtGalleryOfCats::Gameplay::Entities::Camera3D* find_primary_camera();
         ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* find_collision_tile_map();
         void update_entity_player_is_currently_colliding_with();
         void render();
         void render_tile_map(AllegroFlare::TileMaps::TileMap<int>* tile_map=nullptr, float tile_width=16.0f, float tile_height=16.0f);
         void render_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d=nullptr, bool adjacent_to_top_edge=false, bool adjacent_to_right_edge=false, bool adjacent_to_bottom_edge=false, bool adjacent_to_left_edge=false);
         void call_on_finished_callback_func();
         virtual void primary_timer_func() override;
         void player_spin_change(float delta=0.0f);
         void player_tilt_change(float delta=0.0f);
         void player_stop_moving();
         AllegroFlare::Vec2D infer_player_velocity_from_keypress();
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         void trigger_npc_dialog();
         void interact_with_focused_object();
         void attempt_to_solve_riddle();
         void toggle_riddle_visibility();
         void hide_riddle();
         void show_inspect_hint();
         void hide_inspect_hint();
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         void emit_event_to_return_to_the_level_select_screen();
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void key_up_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_axes_func(ALLEGRO_EVENT* ev=nullptr) override;
         ALLEGRO_FONT* obtain_riddle_font();
         ALLEGRO_FONT* obtain_inspect_hint_icon_font();
         ALLEGRO_FONT* obtain_inspect_hint_text_font();
      };
   }
}



