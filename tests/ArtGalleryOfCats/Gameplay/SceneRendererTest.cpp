
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
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
   AllegroFlare::Shaders::Cubemap cubemap_shader;
   AllegroFlare::Cubemap* cubemap = nullptr;
   AllegroFlare::SceneGraph::EntityPool entity_pool;
   ArtGalleryOfCats::Gameplay::EntityFactory entity_factory;
   entity_factory.set_bitmap_bin(&get_bitmap_bin_ref());
   entity_factory.set_model_bin(&model_bin);

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   // Create the camera

   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   camera->stepout = { 0, 1.0, 3.0 };
   entity_pool.add(camera);

   ArtGalleryOfCats::Gameplay::SceneRenderer scene_renderer;
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.set_entity_pool(&entity_pool);

   // Add some items to our scene

   ArtGalleryOfCats::Gameplay::Entities::Base* collectable = entity_factory.create_collectable_object(
      { 0, 0.5, 0 },
      "rounded_unit_cube-01.obj"
   );
   collectable->get_placement_ref().rotation.x = 0.05;
   collectable->get_placement_ref().rotation.z = 0.03547;
   entity_pool.add(collectable);

   // Render the scene
   scene_renderer.render();

   al_flip_display();
   al_rest(1);
}


