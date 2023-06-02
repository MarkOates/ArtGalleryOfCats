
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/SceneRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class ArtGalleryOfCats_Gameplay_SceneRendererTest : public ::testing::Test {};
class ArtGalleryOfCats_Gameplay_SceneRendererTestWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
}


TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTest, render__renders_the_scene)
{
   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
}


