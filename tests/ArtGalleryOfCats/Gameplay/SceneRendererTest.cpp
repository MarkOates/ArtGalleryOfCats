
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


TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTestWithAllegroRenderingFixtureTest, render__renders_the_scene)
{
   AllegroFlare::Shaders::Cubemap cubemap_shader;
   AllegroFlare::Cubemap* cubemap = nullptr;

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;

   //scene_renderer.render();
}


