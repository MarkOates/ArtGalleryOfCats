
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>


TEST(ArtGalleryOfCats_Gameplay_EntityFactoryTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
}


TEST(ArtGalleryOfCats_Gameplay_EntityFactoryTest, create_collision_tile_map__will_load_the_map)
{
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *actual_map = entity_factory.create_collision_tile_map();
}


