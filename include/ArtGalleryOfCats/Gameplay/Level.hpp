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
      private:
         std::string title;
         AllegroFlare::SceneGraph::EntityPool entity_pool;
         ArtGalleryOfCats::Gameplay::Riddle current_riddle;
         bool riddle_is_solved;

      protected:


      public:
         Level(std::string title="[unset-title");
         ~Level();

         void set_title(std::string title);
         void set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle);
         void set_riddle_is_solved(bool riddle_is_solved);
         std::string get_title() const;
         ArtGalleryOfCats::Gameplay::Riddle get_current_riddle() const;
         bool get_riddle_is_solved() const;
         AllegroFlare::SceneGraph::EntityPool &get_entity_pool_ref();
         ArtGalleryOfCats::Gameplay::Riddle &get_current_riddle_ref();
      };
   }
}



