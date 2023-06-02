
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/SceneRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <ArtGalleryOfCats/Gameplay/EntityFactory.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>


class ArtGalleryOfCats_Gameplay_SceneRendererTest : public ::testing::Test {};
class ArtGalleryOfCats_Gameplay_SceneRendererTestWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
}


TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTestWithAllegroRenderingFixtureTest,
   VISUAL__render__renders_the_scene)
{
   AllegroFlare::Shaders::Cubemap cubemap_shader;
   AllegroFlare::Cubemap* cubemap = nullptr;
   AllegroFlare::SceneGraph::EntityPool entity_pool;
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   entity_pool.add(camera);

   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.set_entity_pool(&entity_pool);
    
   scene_renderer.render();

   al_flip_display();
   al_rest(1);
}


