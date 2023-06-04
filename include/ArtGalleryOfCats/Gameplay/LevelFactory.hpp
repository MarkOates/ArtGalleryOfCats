#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>
#include <string>
#include <utility>
#include <vector>


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
         ArtGalleryOfCats::Gameplay::Riddle* riddle;

      protected:


      public:
         LevelFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::SceneGraph::EntityPool* entity_pool={}, ArtGalleryOfCats::Gameplay::Riddle* riddle=nullptr);
         ~LevelFactory();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         void set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool);
         void set_riddle(ArtGalleryOfCats::Gameplay::Riddle* riddle);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::ModelBin* get_model_bin() const;
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool() const;
         ArtGalleryOfCats::Gameplay::Riddle* get_riddle() const;
         static void object_parsed_callback(std::string name_property="[unset-name_property]", std::string class_property="[unset-class_property]", float x_property=0.0f, float y_property=0.0f, float width_property=0.0f, float height_property=0.0f, std::vector<std::pair<std::string, std::string>> custom_properties={}, void* user_data=nullptr);
         void load_primary_map();
      };
   }
}



