#pragma once


#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>
#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class Level
      {
      public:
         static constexpr char* DEFAULT_MUSIC_IDENTIFIER = (char*)"[unset-music_identifier]";

      private:
         std::string name;
         std::string title;
         AllegroFlare::SceneGraph::EntityPool entity_pool;
         ArtGalleryOfCats::Gameplay::Riddle current_riddle;
         std::string music_identifier;
         bool riddle_is_solved;

      protected:


      public:
         Level(std::string name="[unset-name]", std::string title="[unset-title]", std::string music_identifier=DEFAULT_MUSIC_IDENTIFIER);
         ~Level();

         void set_name(std::string name);
         void set_title(std::string title);
         void set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle);
         void set_music_identifier(std::string music_identifier);
         void set_riddle_is_solved(bool riddle_is_solved);
         std::string get_name() const;
         std::string get_title() const;
         ArtGalleryOfCats::Gameplay::Riddle get_current_riddle() const;
         std::string get_music_identifier() const;
         bool get_riddle_is_solved() const;
         AllegroFlare::SceneGraph::EntityPool &get_entity_pool_ref();
         ArtGalleryOfCats::Gameplay::Riddle &get_current_riddle_ref();
         bool has_custom_music();
         void destroy();
      };
   }
}



