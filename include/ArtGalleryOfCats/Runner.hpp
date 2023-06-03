#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/GameOverScreen.hpp>
#include <AllegroFlare/Screens/GameWonScreen.hpp>
#include <AllegroFlare/Screens/LevelSelectScreen.hpp>
#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/Screens/TitleScreen.hpp>
#include <AllegroFlare/Screens/Version.hpp>
#include <ArtGalleryOfCats/Elements/Backgrounds/NPCConversations.hpp>
#include <ArtGalleryOfCats/Gameplay/Screen.hpp>
#include <ReleaseInfo.hpp>
#include <string>


namespace ArtGalleryOfCats
{
   class Runner : public AllegroFlare::Screens::Base
   {
   public:
      static constexpr char* NPC_CONVERSATIONS_SCREEN = (char*)"npc_conversations_screen";
      static constexpr char* EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN = (char*)"activate_primary_gameplay_screen";
      static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Runner";

   private:
      AllegroFlare::Frameworks::Full* framework;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::ModelBin* model_bin;
      std::string resources_path;
      AllegroFlare::Routers::Standard router;
      AllegroFlare::Screens::Storyboard intro_logos_screen;
      AllegroFlare::Screens::Storyboard intro_storyboard_screen;
      AllegroFlare::Screens::TitleScreen title_screen;
      AllegroFlare::Screens::Achievements achievements_screen;
      AllegroFlare::Screens::Version version_screen;
      AllegroFlare::Screens::Storyboard new_game_intro_storyboard_screen;
      AllegroFlare::Screens::LevelSelectScreen level_select_screen;
      AllegroFlare::Screens::GameOverScreen game_over_screen;
      AllegroFlare::Screens::GameWonScreen game_won_screen;
      AllegroFlare::Screens::Storyboard npc_conversations_screen;
      AllegroFlare::Screens::Storyboard game_won_outro_storyboard_screen;
      AllegroFlare::Screens::RollingCredits rolling_credits_screen;
      ArtGalleryOfCats::Gameplay::Screen primary_gameplay_screen;
      AllegroFlare::Elements::Backgrounds::ClearToColor solid_black_background;
      ArtGalleryOfCats::Elements::Backgrounds::NPCConversations npc_conversations_background;
      ReleaseInfo release_info;
      bool initialized;

   protected:


   public:
      Runner(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, std::string resources_path="[unset-resources_path]");
      ~Runner();

      void initialize();
      void setup_router();
      static void run(std::string deployment_environment_mode="[unset-deployment_environment_mode]");
   };
}



