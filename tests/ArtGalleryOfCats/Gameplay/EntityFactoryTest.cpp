
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class ArtGalleryOfCats_Gameplay_EntityFactoryTest : public ::testing::Test {};
class ArtGalleryOfCats_Gameplay_EntityFactoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(ArtGalleryOfCats_Gameplay_EntityFactoryTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
}


TEST_F(ArtGalleryOfCats_Gameplay_EntityFactoryTest, create_collision_tile_map__will_load_the_map)
{
   std::string tmj_filename = "tests/fixtures/maps/gallery-map-03.tmj";
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *actual_map = entity_factory.create_collision_tile_map(
      tmj_filename
   );
}


TEST_F(ArtGalleryOfCats_Gameplay_EntityFactoryTest, create_collision_tile_map__will_initialize_the_map)
{
   std::string tmj_filename = "tests/fixtures/maps/gallery-map-03.tmj";
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   ArtGalleryOfCats::Gameplay::Entities::CollisionTileMap *actual_map = entity_factory.create_collision_tile_map(
      tmj_filename
   );
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = actual_map->get_collision_tile_map_ref();
   EXPECT_EQ(true, collision_tile_map.get_initialized());
}


