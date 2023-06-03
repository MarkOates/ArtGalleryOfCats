
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


