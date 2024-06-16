

#include <ArtGalleryOfCats/Gameplay/Screen.hpp>

#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
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
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, std::string resources_path, ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen, AllegroFlare::Screens::Storyboard* npc_conversations_screen, std::set<std::string>* solved_level_names)
   : AllegroFlare::Screens::Base(ArtGalleryOfCats::Gameplay::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , resources_path(resources_path)
   , user_text_input_screen(user_text_input_screen)
   , npc_conversations_screen(npc_conversations_screen)
   , solved_level_names(solved_level_names)
   , dialog_node_bank({})
   , riddle_is_solved(false)
   , riddle_is_showing(false)
   , inspect_hint_is_showing(false)
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
   , HACK_sysname(DEFAULT_HACK_SYSNAME)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank)
{
   this->dialog_node_bank = dialog_node_bank;
}


void Screen::set_riddle_is_solved(bool riddle_is_solved)
{
   this->riddle_is_solved = riddle_is_solved;
}


void Screen::set_riddle_is_showing(bool riddle_is_showing)
{
   this->riddle_is_showing = riddle_is_showing;
}


void Screen::set_inspect_hint_is_showing(bool inspect_hint_is_showing)
{
   this->inspect_hint_is_showing = inspect_hint_is_showing;
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


AllegroFlare::DialogTree::NodeBank Screen::get_dialog_node_bank() const
{
   return dialog_node_bank;
}


bool Screen::get_riddle_is_solved() const
{
   return riddle_is_solved;
}


bool Screen::get_riddle_is_showing() const
{
   return riddle_is_showing;
}


bool Screen::get_inspect_hint_is_showing() const
{
   return inspect_hint_is_showing;
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


std::string Screen::get_HACK_sysname() const
{
   return HACK_sysname;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_model_bin]: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void Screen::set_resources_path(std::string resources_path)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_resources_path]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_resources_path]: error: guard \"(!initialized)\" not met");
   }
   this->resources_path = resources_path;
   return;
}

void Screen::set_user_text_input_screen(ArtGalleryOfCats::Screens::UserTextInput* user_text_input_screen)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_user_text_input_screen]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_user_text_input_screen]: error: guard \"(!initialized)\" not met");
   }
   this->user_text_input_screen = user_text_input_screen;
   return;
}

void Screen::set_npc_conversations_screen(AllegroFlare::Screens::Storyboard* npc_conversations_screen)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_npc_conversations_screen]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_npc_conversations_screen]: error: guard \"(!initialized)\" not met");
   }
   this->npc_conversations_screen = npc_conversations_screen;
   return;
}

void Screen::set_solved_level_names(std::set<std::string>* solved_level_names)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_solved_level_names]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_solved_level_names]: error: guard \"(!initialized)\" not met");
   }
   this->solved_level_names = solved_level_names;
   return;
}

void Screen::set_HACK_sysname(std::string HACK_sysname)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::set_HACK_sysname]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::set_HACK_sysname]: error: guard \"(!initialized)\" not met");
   }
   this->HACK_sysname = HACK_sysname;
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
   // TODO: Pass new level class properties into factory

   ArtGalleryOfCats::Gameplay::LevelFactory level_factory;
   level_factory.set_model_bin(model_bin);
   level_factory.set_bitmap_bin(bitmap_bin);
   level_factory.set_entity_pool(get_entity_pool());
   level_factory.set_riddle(get_current_riddle());
   level_factory.set_level(current_level);
   level_factory.set_resources_path(resources_path);


   std::map<std::string, std::function<void()>> items_map = {
      { "gallery_01", [&level_factory](){
         level_factory.load_gallery_01();
      }},
      { "gallery_02", [&level_factory](){
         // TODO: Replace this with new map
         level_factory.load_gallery_02();
      }},
      { "gallery_03", [&level_factory](){
         // TODO: Replace this with new map
         level_factory.load_gallery_03();
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


   // TODO: Show gallery name (as "gallery_title")
   // TODO: Set the "riddle text"

   start_level_music();


   return;
}

void Screen::start_level_music()
{

   if (current_level->has_custom_music())
   {
      std::string custom_music_identifier = current_level->get_music_identifier();
      event_emitter->emit_play_music_track_event(custom_music_identifier);
   }
   else
   {
      std::string default_music_identifier = "main_music";
      event_emitter->emit_play_music_track_event(default_music_identifier);
   }
   return;
}

void Screen::emit_event_to_set_input_hints_bar_to_room_controls()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::emit_event_to_set_input_hints_bar_to_room_controls]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::emit_event_to_set_input_hints_bar_to_room_controls]: error: guard \"initialized\" not met");
   }
   event_emitter->emit_set_input_hints_bar_event({
      "UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move pointer",
      "%SEPARATOR",
      "ENTER", "%SPACER", "LABEL>>", "Inspect object",
      "%SEPARATOR",
      "I", "%SPACER", "LABEL>>", "Toggle Chronicle",
      "%SEPARATOR",
      "P", "%SPACER", "LABEL>>", "Toggle pause",
      "%SEPARATOR",
      "E", "%SPACER", "LABEL>>", "Exit",
   });
   return;
}

void Screen::emit_event_to_set_input_hints()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::emit_event_to_set_input_hints]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::emit_event_to_set_input_hints]: error: guard \"initialized\" not met");
   }
   //if (fixed_room_2d.inventory_is_open()) emit_event_to_set_input_hints_bar_to_inventory_controls();
   else emit_event_to_set_input_hints_bar_to_room_controls();
   event_emitter->emit_set_input_hints_bar_text_opacity_event(0.265);
   return;
}

AllegroFlare::SceneGraph::EntityPool* Screen::get_entity_pool()
{
   if (!(current_level))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::get_entity_pool]: error: guard \"current_level\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::get_entity_pool]: error: guard \"current_level\" not met");
   }
   // TODO: Add "guards: [ current_level ]"
   //return &entity_pool; // TODO: Swap this out with the current level entity_pool (comment below)
   return &current_level->get_entity_pool_ref();
}

ArtGalleryOfCats::Gameplay::Riddle* Screen::get_current_riddle()
{
   if (!(current_level))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::get_current_riddle]: error: guard \"current_level\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::get_current_riddle]: error: guard \"current_level\" not met");
   }
   //return &current_riddle; // TODO: Swap this out with the current level entity_pool (comment below)
   return &current_level->get_current_riddle_ref();
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met");
   }
   if (!(solved_level_names))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"solved_level_names\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"solved_level_names\" not met");
   }
   if (!((resources_path != DEFAULT_RESOURCES_PATH)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(resources_path != DEFAULT_RESOURCES_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(resources_path != DEFAULT_RESOURCES_PATH)\" not met");
   }
   if (!((HACK_sysname != DEFAULT_HACK_SYSNAME)))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(HACK_sysname != DEFAULT_HACK_SYSNAME)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::initialize]: error: guard \"(HACK_sysname != DEFAULT_HACK_SYSNAME)\" not met");
   }
   // TODO: Fix this section
   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = resources_path + "bitmaps/iridescent_prism_1-01.png";
   //std::string cube_map_texture_filename = "fixtures/bitmaps/black_prism_1-01.png"; // TODO: set the correct location
   cubemap = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   load_dialog_node_bank();

   initialized = true;
   return;
}

void Screen::load_dialog_node_bank()
{
   dialog_node_bank.set_nodes({

      // Riddle responses

      { "correct_riddle_answer", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "CORRECT!",
              "You got it right! You are very attentive!",
              "Nice sleuthing skills.",
              "If you'd like, we can still look around this gallery.",
              "Otherwise, we can move on to another gallery?",
              //"If you'd like, you can still look around this gallery.",
              "To go to another gallery, press the ESCAPE key while you're walking around.",
              //"Or, just return to the Galary Select Screen by pressing the ESCAPE key.",
              //"
           }
        )
      },
      { "incorrect_riddle_answer", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Hmm, that's not the correct answer to the riddle.", "That's ok! You can try as many times as you like." }
        )
      },

      // Default and fallback dialog

      { "fallback_dialog", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "That's interesting." }
         )
      },
      { "default_inspect_1", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "The artist has such a good sense of form and balance!" }
         )
      },
      { "default_inspect_2", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "I really like this art!" }
         )
      },
      { "default_inspect_3", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "This art is fantastic! It nourishes the spirit!" }
         )
      },
      { "default_inspect_4", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Works like this one are always a favorite of mine!" }
         )
      },
      { "default_inspect_5", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Such striking composition!" }
         )
      },
      { "default_inspect_6", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Hmm, an interesting work!" }
         )
      },

      // Special inspections (colorful cats)

      { "inspect_on_black_and_white_cats_art", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "This one is quite striking!", "The black and white creates such a strong contrast." }
         )
      },

      // Special inspections (humans exhibit)

      { "inspect_medium_statue", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
               "You know, the actual, proper pronunciation is quite different than how we say it.",
               "It's true!  I actually studied pronunciation at Cat University.",
               "The word is pronounced...",
               "hheee... heeeeuu.... heeewwww",
               "...eeewmons.",
               "Yes! That's it! Hiewmons.",
               "Anyway, the hoomans exibit is one of my favs.  What mystical creatures they are!"
           }
         )
      },
      { "inspect_feature_statue", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "Wow! This is our most special exhibit. The Exhibit of the Mystical Creature!",
              "In this gallery, there's art featuring the most mythical creature of all, the human.",
              "Unlike cats, their ears are on the side of their heads.",
              "Weird!"
           }
         )
      },
      { "inspect_small_statues", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Since we don't have any hard evidence, we can only imagine what color their furr might be." }
         )
      },
      { "inspect_human_01", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "This depiction is just incredible. Stunning detail.",
              "But... without furr... it's just so... naked-looking!",
              "Eek!"
           }
         )
      },
      { "inspect_human_02", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "Here they are, depicted with their ears on the side of their head." }
         )
      },
      { "inspect_human_03", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           { "The hooman myths go back centuries!  All the way back to ancient times." }
         )
      },
      { "inspect_human_04", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "This one is brilliant.  We can only imagine what the mystical hooman creature is like.",
              "And here's a cat, looking in the mirror, imagining a human...",
              "... and WE'RE here... looking at this art...",
              "Maybe there's a hooman, looking at us right now!",
              "Haha! What a crazy notion!",
           }
         )
      },
      { "inspect_human_05", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "Of course our gallery would not be complete without this famous work,",
              "The \"Vitruvian Hooman\" by Leonardo Meow Vinci."
           }
         )
      },
      { "inspect_cat_years_to_human_years", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "Interesting fact! Hoomans are said to live much longer than us cats.",
              "Up to almost 10 times longer!",
              "Hmm...",
              "I guess if I were a human, I'd be 25 years old."
           }
         )
      },


      { "inspect_iridescent_sculpture_a", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "As a hint to solving the riddle to this gallery, you might inspect these iridescent sculptures."
           }
         )
      },
      { "inspect_iridescent_sculpture_b", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "This first gallery, our Welcome Hall, features these inviting sculptures.",
              "These are quite a prized collection, if you ask me!",
              "I, Mittens, will be your guide through all of our galleries at the Art Gallery of Cats."
              //"
              //"I, ahem... Mittens, will help... ahem... guide you through 
              //"The first gallery, our welcome hall, features these inviting sculptures."
              //"Interesting fact! Hoomans are said to live much longer than us cats.",
              //"Up to almost 10 times longer!",
              //"Hmm...",
              //"I guess if I were a human, I'd be 25 years old."
           }
         )
      },
      { "inspect_iridescent_sculpture_c", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
           "Mittens",
           {
              "Yup! These sculptures are really shiny! Just like me, Mittens!",
              "...",
              "Did I mention my name was Mittens?",
              "OK! Just want to be sure."
              //"Interesting fact! Hoomans are said to live much longer than us cats.",
              //"Up to almost 10 times longer!",
              //"Hmm...",
              //"I guess if I were a human, I'd be 25 years old."
           }
         )
      },

   });
   return;
}

void Screen::activate_npc_dialog_by_identifier(std::string dialog_node_identifier)
{
   if (!dialog_node_bank.node_exists_by_name(dialog_node_identifier))
   {
      std::cout << "!!!!!!!! missing dialog for node \"" << dialog_node_identifier << "\"." << std::endl;
      return;
   }

   // TODO: Erase the current npc dialog pages (delete them)

   // Get dialog pages from node
   AllegroFlare::DialogTree::Nodes::Base* dialog_node_base = dialog_node_bank.find_node_by_name(dialog_node_identifier);
   auto dialog_node = static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(dialog_node_base);
   // TODO: Confirm dialog type

   std::vector<std::string> dialog_pages = dialog_node->get_pages();

   // Create storyboard pages from the dialog pages
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> storyboard_pages = {};
   storyboard_pages.reserve(dialog_pages.size());
   for (auto &dialog_page : dialog_pages)
   {
      storyboard_pages.push_back(create_image_page(dialog_page));
   }

   // Assign our new dialog pages to the npc_coversations storyboard
   npc_conversations_screen->get_storyboard_element_ref().set_pages(storyboard_pages);

   // Activate the npc_conversations_screen
   activate_npc_conversations_screen(); // DEVELOPMENT

   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   if (!(current_level))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::on_activate]: error: guard \"current_level\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::on_activate]: error: guard \"current_level\" not met");
   }
   hide_riddle();
   hide_inspect_hint();

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
      answer_is_correct = get_current_riddle()->matches_answer(last_user_text_input_value);

      // Clear our copy of the user input
      last_user_text_input_value.clear();

      if (!answer_is_correct)
      {
         // TODO: Sort out what reaction should be when answer is incorrect
         // TODO: Set npc dialog to say "hmm, that's not correct"

         event_emitter->emit_play_sound_effect_event("wrong_answer");
         activate_npc_dialog_by_identifier("incorrect_riddle_answer");
      }
      else
      {
         // TODO: Sort out what reaction should be when answer is correct
         // TODO: Set npc dialog to say "That's correct! Nice job!"

         //activate_npc_dialog_by_identifier("correct_riddle_answer");

         event_emitter->emit_event(
            ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT,
            intptr_t(new std::string("solve_a_riddle"))
         );


         event_emitter->emit_play_sound_effect_event("right_answer");

         riddle_is_solved = true; // TODO: modify this on a master list

         solved_level_names->insert(current_level->get_name()); // HERE
         std::cout << "- Solved level names are now:" << std::endl;
         for (auto &solved_level_name : (*solved_level_names))
         {
            std::cout << "   - " << solved_level_name << std::endl;
         }


         activate_npc_dialog_by_identifier("correct_riddle_answer");

         //activate_npc_conversations_screen(); // DEVELOPMENT
      }
   }


   // Show our input hints
   show_input_hints();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   hide_input_hints();
   return;
}

void Screen::hide_input_hints()
{
   event_emitter->emit_hide_input_hints_bar_event();
   return;
}

void Screen::show_input_hints()
{
   event_emitter->emit_set_input_hints_bar_event({
      "UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move",
      "%SEPARATOR",
      "MOUSE", "%SPACER", "LABEL>>", "Look",
      "%SEPARATOR",
      "T", "%SPACER", "LABEL>>", "Toggle the Riddle",
      "%SEPARATOR",
      "R", "%SPACER", "LABEL>>", "Solve the Riddle",
      "%SEPARATOR",
      "I", "%SPACER", "LABEL>>", "Inspect",
      "%SEPARATOR",
      "ESC", "%SPACER", "LABEL>>", "Return to Gallery Select",
   });
   //if (fixed_room_2d.inventory_is_open()) emit_event_to_set_input_hints_bar_to_inventory_controls();
   //else emit_event_to_set_input_hints_bar_to_room_controls();
   event_emitter->emit_set_input_hints_bar_text_opacity_event(0.265);
   //emit_event_to_set_input_hints();
   //event_emitter->emit_set_input_hints_bar_backfill_opacity_event(0.3);
   event_emitter->emit_set_input_hints_bar_text_opacity_event(1.0);
   event_emitter->emit_show_input_hints_bar_event();
}

void Screen::update()
{
   // HACK
   static int grabber_caller_HACK = 0;
   grabber_caller_HACK--;
   if (grabber_caller_HACK < 0)
   {
      ALLEGRO_DISPLAY *current_display = al_get_current_display();
      al_grab_mouse(current_display);
      grabber_caller_HACK = 99;
   }

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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::find_primary_camera]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::find_primary_camera]: error: guard \"get_entity_pool()\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::find_collision_tile_map]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::find_collision_tile_map]: error: guard \"get_entity_pool()\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::update_entity_player_is_currently_colliding_with]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::update_entity_player_is_currently_colliding_with]: error: guard \"get_entity_pool()\" not met");
   }
   // TODO: Implement this function
   //entity_player_is_currently_colliding_with

   // Select all the entities that the player can collide with
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> entities_player_can_interact_with =
      get_entity_pool()->select_A(ArtGalleryOfCats::Gameplay::EntityFlags::PLAYER_CAN_INTERACT);


   float player_hit_box_size = 2.75;
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

      // TODO: Some feedback that a new collision occurred (a sound effect for example)
      if (entity_player_is_currently_colliding_with == nullptr)
      {
         hide_inspect_hint();
      }
      else
      {
         show_inspect_hint();
         //interact_with_focused_object(); // DEVELOPMENT
      }
   }

   return;
}

void Screen::scene_physics_updater()
{
   if (!(get_entity_pool()))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::scene_physics_updater]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::scene_physics_updater]: error: guard \"get_entity_pool()\" not met");
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

      if (entity->exists("primary_camera"))
      {
         //std::cout << "   position.y: " << placement.position.y << std::endl;
      }

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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::scene_renderer_render]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::scene_renderer_render]: error: guard \"get_entity_pool()\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::render_hud]: error: guard \"get_entity_pool()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::render_hud]: error: guard \"get_entity_pool()\" not met");
   }
   // Local vars;
   AllegroFlare::SceneGraph::Entities::Base *entity = nullptr;

   AllegroFlare::Camera2D hud_camera;
   //ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   ALLEGRO_BITMAP *render_surface = al_get_target_bitmap();
   hud_camera.setup_dimensional_projection(render_surface);

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
      AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = as_collision_tile_map->get_collision_tile_map_ref();



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

   if (riddle_is_showing)
   {
      // TODO: Draw the riddle text;
      ALLEGRO_FONT* riddle_font = obtain_riddle_font();
      std::string riddle_text = get_current_riddle()->get_riddle_text();
      ALLEGRO_COLOR riddle_color = ALLEGRO_COLOR{1, 1, 1, 1};
      al_draw_multiline_text(
         riddle_font,
         riddle_color,
         -500,
         -200,
         1000,
         al_get_font_line_height(riddle_font) * 1.65,
         0,
         riddle_text.c_str()
      );
   }

   if (inspect_hint_is_showing)
   {
      float inspect_hint_x = 1920*0.5 - 170; // TODO: make this not-hard-coded dimension
      float inspect_hint_y = 1080*0.5 - 50; // TODO: make this not-hard-coded dimension
      float inspect_hint_radius = 30.0f;
      ALLEGRO_COLOR inspect_hint_backfill_color = al_color_html("024d83");
      ALLEGRO_COLOR inspect_hint_text_color = al_color_html("ffffff");
      ALLEGRO_FONT* inspect_hint_icon_font = obtain_inspect_hint_icon_font();
      ALLEGRO_FONT* inspect_hint_text_font = obtain_inspect_hint_text_font();

      // Draw the circle
      al_draw_filled_circle(inspect_hint_x, inspect_hint_y, inspect_hint_radius, inspect_hint_backfill_color);

      // Draw the "i" character
      al_draw_text(
         inspect_hint_icon_font,
         inspect_hint_text_color,
         inspect_hint_x,
         inspect_hint_y - al_get_font_line_height(inspect_hint_icon_font) * 0.5,
         ALLEGRO_ALIGN_CENTER,
         "i"
      );

      // Draw the "[I] Inspect key help text" character
      al_draw_text(
         inspect_hint_text_font,
         inspect_hint_text_color,
         inspect_hint_x + inspect_hint_radius * 1.3,
         inspect_hint_y - al_get_font_line_height(inspect_hint_text_font) * 0.5,
         ALLEGRO_ALIGN_LEFT,
         "Inspect"
      );
   }


   hud_camera.restore_transform();

   return;
}

void Screen::render_tile_map(AllegroFlare::TileMaps::TileMap<int>* tile_map, float tile_width, float tile_height)
{
   if (!(tile_map))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::render_tile_map]: error: guard \"tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::render_tile_map]: error: guard \"tile_map\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::render_aabb2d]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::render_aabb2d]: error: guard \"aabb2d\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::primary_timer_func]: error: guard \"initialized\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
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

void Screen::activate_npc_conversations_screen()
{
   event_emitter->emit_router_event(
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER,
      new AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier("npc_conversations_screen")
   );
   return;
}

std::string Screen::find_custom_dialog_for_this_inspect(AllegroFlare::SceneGraph::Entities::Base* entity_inspecting_on)
{
   if (!entity_inspecting_on) return "";

   std::string art_identifier = entity_inspecting_on->get(ArtGalleryOfCats::Gameplay::EntityFlags::ART_IDENTIFIER);

   std::string const INSPECT_PREFIX = "inspect_";

   std::cout << "Inspecting on \"" << art_identifier << "\"" << std::endl;
   if (art_identifier == "black_and_white_cats") return "inspect_on_black_and_white_cats_art";


   // These listed here will automatically return "inspect_[art_identifier]";
   std::set<std::string> special_inspect_to_return_with_inspect_prefix = {
      "medium_statue",
      "feature_statue",
      "small_statues",
      "human_01",
      "human_02",
      "human_03",
      "human_04",
      "human_05",
      "cat_years_to_human_years",
      "iridescent_sculpture_a",
      "iridescent_sculpture_b",
      "iridescent_sculpture_c"
   };

   if (special_inspect_to_return_with_inspect_prefix.count(art_identifier) != 0)
   {
      return INSPECT_PREFIX + art_identifier;
   }


   // TODO: Add special case dialog here

   return "";
}

void Screen::interact_with_focused_object()
{
   if (!(npc_conversations_screen))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::interact_with_focused_object]: error: guard \"npc_conversations_screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::interact_with_focused_object]: error: guard \"npc_conversations_screen\" not met");
   }
   if (!entity_player_is_currently_colliding_with)
   {
      // TODO: play a sound that indicates there is nothing to interact with
      return;
   }

   player_stop_moving();


   std::string dialog_identifier_to_use = "fallback_dialog";

   std::string custom_dialog_identifier = find_custom_dialog_for_this_inspect(
      entity_player_is_currently_colliding_with
   );

   if (custom_dialog_identifier.empty())
   {
      // There is no custom dialog, so select a fallback dialog here

      static int last_default_inspect_index = 0;
      std::vector<std::string> default_inspect_dialog_node_identifiers = {
         "default_inspect_1",
         "default_inspect_2",
         "default_inspect_3",
         "default_inspect_4",
         "default_inspect_5",
         "default_inspect_6",
      };

      dialog_identifier_to_use = default_inspect_dialog_node_identifiers[last_default_inspect_index];

      last_default_inspect_index++;
      if (last_default_inspect_index >= default_inspect_dialog_node_identifiers.size()) last_default_inspect_index = 0;
   }
   else
   {
      dialog_identifier_to_use = custom_dialog_identifier;
   }




   //std::string defaut_dialog = "That is some beautiful art!";


   // TODO: Set the npc avatar for this dialog
   // TODO: Setup an npc name, and add it to this dialog
   // TODO: Set the text pages for this character dialog

   //std::vector<std::string> dialog_pages = {
      //"Impressive",
      //"The artist has such an amazing sense of form and balance!",
   //};



   //std::vector<AllegroFlare::Elements::StoryboardPages::Base *> storyboard_pages = {};
   //dialog_node_bank.


   //this_dialog_node_to_say


   /*
   // TODO: Clear pages on the storyboard element
   npc_conversations_screen->get_storyboard_element_ref().set_pages({
       create_image_page(
       //page_factory.create_advancing_text_page(
      "default_inspect_1",
         "Impressive!"
          //I guess I would be.",
         //"I really like all this art! It nourishes the spirit. It ignites the soul!"
       //),
       ),
       create_image_page(
       //page_factory.create_advancing_text_page(
          "The artist has such an amazing sense of form and balance!"
       ),
   });
   */


   activate_npc_dialog_by_identifier(dialog_identifier_to_use);



   //activate_npc_conversations_screen(); // DEVELOPMENT

   //event_emitter->talk_to_an_npc
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT,
      intptr_t(new std::string("look_at_some_art"))
   );
   return;
}

void Screen::attempt_to_solve_riddle()
{
   if (!(user_text_input_screen))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::attempt_to_solve_riddle]: error: guard \"user_text_input_screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::attempt_to_solve_riddle]: error: guard \"user_text_input_screen\" not met");
   }
   player_stop_moving();

   // Set the prompt on the user text input screen
   // TODO: Make this value dynamic
   std::string riddle_prompt_text = get_current_riddle()->get_riddle_prompt_text();
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

void Screen::toggle_riddle_visibility()
{
   riddle_is_showing = !riddle_is_showing;
   return;
}

void Screen::hide_riddle()
{
   riddle_is_showing = false;
   return;
}

void Screen::show_inspect_hint()
{
   inspect_hint_is_showing = true;
   return;
}

void Screen::hide_inspect_hint()
{
   inspect_hint_is_showing = false;
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::key_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::key_down_func]: error: guard \"event_emitter\" not met");
   }
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_W:
      case ALLEGRO_KEY_UP: {
         player_up_pressed = true;
      } break;

      case ALLEGRO_KEY_A:
      case ALLEGRO_KEY_LEFT: {
         player_left_pressed = true;
      } break;

      case ALLEGRO_KEY_S:
      case ALLEGRO_KEY_DOWN: {
         player_down_pressed = true;
      } break;

      case ALLEGRO_KEY_D:
      case ALLEGRO_KEY_RIGHT: {
         player_right_pressed = true;
      } break;

      case ALLEGRO_KEY_SPACE:
      case ALLEGRO_KEY_ENTER:
      case ALLEGRO_KEY_I: {
         interact_with_focused_object();
      } break;

      case ALLEGRO_KEY_R: {
         //interact_with_focused_object();
         attempt_to_solve_riddle();
      } break;

      case ALLEGRO_KEY_T: {
         toggle_riddle_visibility();
      } break;

      case ALLEGRO_KEY_ESCAPE: {
         emit_event_to_return_to_the_level_select_screen();
         //prompt_user_for_text_input(); // DEVELOPMENT
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
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::key_up_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::key_up_func]: error: guard \"event_emitter\" not met");
   }
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
      case ALLEGRO_KEY_W: {
         player_up_pressed = false;
      } break;

      case ALLEGRO_KEY_LEFT:
      case ALLEGRO_KEY_A: {
         player_left_pressed = false;
      } break;

      case ALLEGRO_KEY_DOWN:
      case ALLEGRO_KEY_S: {
         player_down_pressed = false;
      } break;

      case ALLEGRO_KEY_RIGHT:
      case ALLEGRO_KEY_D: {
         player_right_pressed = false;
      } break;

      default: {
         // Nothing here
      } break;
   }

   return;
}

void Screen::mouse_down_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::mouse_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::mouse_down_func]: error: guard \"initialized\" not met");
   }
   //interact_with_focused_object();
   return;
}

void Screen::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::Screen::mouse_axes_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[ArtGalleryOfCats::Gameplay::Screen::mouse_axes_func]: error: guard \"initialized\" not met");
   }
   // TODO: Validate spin change
   float spin_delta = ev->mouse.dx;
   float tilt_delta = ev->mouse.dy;
   float spin_multiplier = 0.001;
   float tilt_multiplier = 0.001;
   player_spin_change(spin_delta * spin_multiplier);
   player_tilt_change(tilt_delta * tilt_multiplier);


   // HACK
   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   int current_display_flags = al_get_display_flags(current_display);
   bool this_display_is_fullscreen = current_display_flags & ALLEGRO_FULLSCREEN_WINDOW;
   bool this_display_is_windowed = !this_display_is_fullscreen;

   //if (this_display_is_fullscreen)
   //{
      //throw std::runtime_error("this_display_is_fullscreen");
   //}
   //else
   //{
      //throw std::runtime_error("this_display_is_not_fullscreen");
   //}


   //ALLEGRO_FULLSCREEN_WINDOW

   bool this_system_is_a_mac = (HACK_sysname == "Darwin");

   if (this_display_is_windowed && this_system_is_a_mac)
   {
      if (current_display)
      {
         al_set_mouse_xy(
            current_display,
            al_get_display_width(current_display)*0.5,
            al_get_display_height(current_display)*0.5
         );
      }
   }

   if (!this_display_is_windowed && !this_system_is_a_mac)
   {
      // Warp on windows in fullscreen
      if (current_display)
      {
         al_set_mouse_xy(
            current_display,
            al_get_display_width(current_display)*0.5,
            al_get_display_height(current_display)*0.5
         );
      }
   }


   //float x_delta = ev->mouse->dx;
   //result->tilt = 0.13;            // look up(-)/down(+)
   //result->spin = 0.2;             // set a good start initial spin
   // TODO: this function
   return;
}

AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText* Screen::create_image_page(std::string text)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText *result =
      new AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText();
   result->set_bitmap_bin(bitmap_bin);
   result->set_font_bin(font_bin);
   result->set_text(text);
   result->set_font_size(-50);
   result->set_line_height_multiplier(1.25f);
   result->set_image_fade_in_duration_sec(0.0f);
   result->set_text_color(ALLEGRO_COLOR{0, 0, 0, 1});
   result->set_image_identifier("character-avatar-01.png");
   //"storyboard-1-01-1165x500.png");
   result->set_top_padding(650);
   result->set_left_padding(600);
   result->set_right_padding(600);
   return result;
}

ALLEGRO_FONT* Screen::obtain_riddle_font()
{
   return font_bin->auto_get("BodoniModa_9pt-SemiBold.ttf -72");
}

ALLEGRO_FONT* Screen::obtain_inspect_hint_icon_font()
{
   return font_bin->auto_get("BodoniModa_9pt-SemiBold.ttf -72");
}

ALLEGRO_FONT* Screen::obtain_inspect_hint_text_font()
{
   return font_bin->auto_get("BodoniModa_9pt-SemiBold.ttf -48");
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


