
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/LevelFactory.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class ArtGalleryOfCats_Gameplay_LevelFactoryTest : public ::testing::Test {};
class ArtGalleryOfCats_Gameplay_LevelFactoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(ArtGalleryOfCats_Gameplay_LevelFactoryTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::LevelFactory level_factory;
}


TEST_F(ArtGalleryOfCats_Gameplay_LevelFactoryTestWithAllegroRenderingFixture, load_primary_map__will_not_crash)
{
   AllegroFlare::ModelBin model_bin;
   AllegroFlare::SceneGraph::EntityPool entity_pool;
   model_bin.set_full_path(get_fixtures_path() + "models");
   ArtGalleryOfCats::Gameplay::LevelFactory level_factory;
   level_factory.set_bitmap_bin(&get_bitmap_bin_ref());
   level_factory.set_model_bin(&model_bin);
   level_factory.set_entity_pool(&entity_pool);

   level_factory.load_primary_map();

   EXPECT_EQ(11, entity_pool.num_elements());
}


