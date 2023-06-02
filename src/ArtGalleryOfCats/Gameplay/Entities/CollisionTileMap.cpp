

#include <ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


CollisionTileMap::CollisionTileMap()
   : ArtGalleryOfCats::Gameplay::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap::TYPE)
   , collision_tile_map({})
{
}


CollisionTileMap::~CollisionTileMap()
{
}


void CollisionTileMap::set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int> collision_tile_map)
{
   this->collision_tile_map = collision_tile_map;
}


AllegroFlare::TileMaps::TileMap<int> CollisionTileMap::get_collision_tile_map() const
{
   return collision_tile_map;
}


AllegroFlare::TileMaps::TileMap<int> &CollisionTileMap::get_collision_tile_map_ref()
{
   return collision_tile_map;
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


