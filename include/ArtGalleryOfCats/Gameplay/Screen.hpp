#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
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

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         std::string current_level_identifier;
         void* current_level;
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         bool initialized;

      protected:


      public:
         Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
         virtual ~Screen();

         void set_on_finished_callback_func(std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         std::function<void(ArtGalleryOfCats::Gameplay::Screen*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         void call_on_finished_callback_func();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



