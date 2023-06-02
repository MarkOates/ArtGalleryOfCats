
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap.hpp>


TEST(ArtGalleryOfCats_Gameplay_Entities_CollisionTileMapTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap collision_tile_map;
}


TEST(ArtGalleryOfCats_Gameplay_Entities_CollisionTileMapTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "ArtGalleryOfCats/Gameplay/Entities/CollisionTileMap",
     ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap::TYPE
   );
}


TEST(ArtGalleryOfCats_Gameplay_Entities_CollisionTileMapTest, type__has_the_expected_value_matching_TYPE)
{
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap collision_tile_map;
   EXPECT_EQ(ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap::TYPE, collision_tile_map.get_type());
}


