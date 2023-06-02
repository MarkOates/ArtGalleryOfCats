#pragma once


#include <AllegroFlare/SceneGraph/EntityPool.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class SceneRenderer
      {
      private:
         AllegroFlare::SceneGraph::EntityPool* entity_pool;

      protected:


      public:
         SceneRenderer(AllegroFlare::SceneGraph::EntityPool* entity_pool=nullptr);
         ~SceneRenderer();

         void set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool);
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool() const;
         void render();
      };
   }
}



