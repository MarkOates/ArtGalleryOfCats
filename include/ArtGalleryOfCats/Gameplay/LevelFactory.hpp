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

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         void set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::ModelBin* get_model_bin() const;
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool() const;
         void load_primary_map();
      };
   }
}



