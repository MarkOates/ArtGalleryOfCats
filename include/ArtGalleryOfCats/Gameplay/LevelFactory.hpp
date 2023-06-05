#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <ArtGalleryOfCats/Gameplay/Level.hpp>
#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class LevelFactory
      {
      public:
         static constexpr char* DEFAULT_RESOURCES_PATH = (char*)"[unset-resources_path]";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::SceneGraph::EntityPool* entity_pool;
         ArtGalleryOfCats::Gameplay::Riddle* riddle;
         ArtGalleryOfCats::Gameplay::Level* level;
         std::string resources_path;

      protected:


      public:
         LevelFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::SceneGraph::EntityPool* entity_pool={}, ArtGalleryOfCats::Gameplay::Riddle* riddle=nullptr, ArtGalleryOfCats::Gameplay::Level* level=nullptr, std::string resources_path=DEFAULT_RESOURCES_PATH);
         ~LevelFactory();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         void set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool);
         void set_riddle(ArtGalleryOfCats::Gameplay::Riddle* riddle);
         void set_level(ArtGalleryOfCats::Gameplay::Level* level);
         void set_resources_path(std::string resources_path);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::ModelBin* get_model_bin() const;
         AllegroFlare::SceneGraph::EntityPool* get_entity_pool() const;
         ArtGalleryOfCats::Gameplay::Riddle* get_riddle() const;
         ArtGalleryOfCats::Gameplay::Level* get_level() const;
         std::string get_resources_path() const;
         bool has_non_default_resources_path();
         static void object_parsed_callback(std::string name_property="[unset-name_property]", std::string class_property="[unset-class_property]", float x_property=0.0f, float y_property=0.0f, float width_property=0.0f, float height_property=0.0f, std::vector<std::pair<std::string, std::string>> custom_properties={}, void* user_data=nullptr);
         static void map_properties_parsed_callback(std::vector<std::tuple<std::string, std::string, std::string>> map_custom_properties={}, void* user_data=nullptr);
         void load_gallery_01();
         void load_gallery_02();
         void load_gallery_03();
         void load_primary_map();
      };
   }
}



