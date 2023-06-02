

#include <ArtGalleryOfCats/Gameplay/SceneRenderer.hpp>

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


SceneRenderer::SceneRenderer(AllegroFlare::SceneGraph::EntityPool* entity_pool)
   : entity_pool(entity_pool)
{
}


SceneRenderer::~SceneRenderer()
{
}


void SceneRenderer::set_entity_pool(AllegroFlare::SceneGraph::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


AllegroFlare::SceneGraph::EntityPool* SceneRenderer::get_entity_pool() const
{
   return entity_pool;
}


void SceneRenderer::render()
{
   if (!(entity_pool))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::render]: error: guard \"entity_pool\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::render: error: guard \"entity_pool\" not met");
   }
   // Extract out the camera and render the scene
   AllegroFlare::SceneGraph::Entities::Base *entity = entity_pool->find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("no camera present");
   ArtGalleryOfCats::Gameplay::Entities::Camera3D *as_camera =
      static_cast<ArtGalleryOfCats::Gameplay::Entities::Camera3D*>(entity);

   ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   al_clear_depth_buffer(1);
   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

   as_camera->setup_projection_on(render_surface);

   // TODO: validate the camera is of type Entities::Camera
   // TODO: here

   //std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*>
   for (auto &entity : entity_pool->get_entity_pool_ref())
   {
      ArtGalleryOfCats::Gameplay::Entities::Base *as_agc_entity =
         static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);

      AllegroFlare::Model3D *model = as_agc_entity->get_model();
      if (model)
      {
         ALLEGRO_BITMAP *texture = as_agc_entity->get_texture();
         if (texture) model->set_texture(texture);
         model->draw();
      }
   }

   //as_camera->start_reverse_transform();
   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


