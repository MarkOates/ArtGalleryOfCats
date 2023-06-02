#pragma once


#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      namespace Entities
      {
         class CollisionTileMap : public ArtGalleryOfCats::Gameplay::Entities::Base
         {
         public:
            static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap";

         private:
            AllegroFlare::TileMaps::TileMap<int> collision_tile_map;

         protected:


         public:
            CollisionTileMap();
            ~CollisionTileMap();

            void set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int> collision_tile_map);
            AllegroFlare::TileMaps::TileMap<int> get_collision_tile_map() const;
            AllegroFlare::TileMaps::TileMap<int> &get_collision_tile_map_ref();
         };
      }
   }
}



