#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap.hpp>
#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class EntityFactory
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;

      protected:


      public:
         EntityFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
         ~EntityFactory();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::ModelBin* get_model_bin() const;
         ArtGalleryOfCats::Gameplay::Entities::Base* create_environment_mesh(std::string model_filename="[unset-model_filename]", std::string texture_filename="[unset-texture_filename]");
         ArtGalleryOfCats::Gameplay::Entities::Base* create_collectable_object(AllegroFlare::Vec3D position={}, std::string model_filename="[unset-model_filename]", std::string texture_filename="[unset-texture_filename]");
         ArtGalleryOfCats::Gameplay::Entities::Camera3D* create_camera();
         ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap* create_collision_tile_map(std::string tmj_filename="[unset-tmj_filename]");
      };
   }
}



