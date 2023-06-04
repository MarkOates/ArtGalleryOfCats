#pragma once


#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class Level
      {
      private:
         AllegroFlare::SceneGraph::EntityPool entity_pool;
         ArtGalleryOfCats::Gameplay::Riddle current_riddle;
         bool riddle_is_solved;

      protected:


      public:
         Level(AllegroFlare::SceneGraph::EntityPool entity_pool={});
         ~Level();

         void set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle);
         void set_riddle_is_solved(bool riddle_is_solved);
         ArtGalleryOfCats::Gameplay::Riddle get_current_riddle() const;
         bool get_riddle_is_solved() const;
      };
   }
}



