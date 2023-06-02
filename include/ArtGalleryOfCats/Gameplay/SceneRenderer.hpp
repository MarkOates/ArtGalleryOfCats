#pragma once


#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <AllegroFlare/Shaders/Cubemap.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class SceneRenderer
      {
      private:
         AllegroFlare::Shaders::Cubemap* cubemap_shader;
         AllegroFlare::SceneGraph::EntityPool* entity_pool;

      protected:


      public:
         SceneRenderer(AllegroFlare::Shaders::Cubemap* cubemap_shader=nullptr, AllegroFlare::SceneGraph::EntityPool* entity_pool=nullptr);
         ~SceneRenderer();

         void set_cubemap_shader(AllegroFlare::Shaders::Cubemap* cubemap_shader);
         void set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool);
         AllegroFlare::Shaders::Cubemap* get_cubemap_shader() const;
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool() const;
         void render();
      };
   }
}



