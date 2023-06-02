#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class LevelFactory
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::SceneGraph::EntityPool* entity_pool;

      protected:


      public:
         LevelFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::SceneGraph::EntityPool* entity_pool={});
         ~LevelFactory();

         void load_primary_map();
      };
   }
}



