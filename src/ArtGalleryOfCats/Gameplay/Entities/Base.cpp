

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Base::Base(std::string type, AllegroFlare::Model3D* model, ALLEGRO_BITMAP* texture, AllegroFlare::Placement3D placement, AllegroFlare::Placement3D velocity, AllegroFlare::Physics::AABB2D hit_box_2d)
   : AllegroFlare::SceneGraph::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE)
   , type(type)
   , model(model)
   , texture(texture)
   , placement(placement)
   , velocity(velocity)
   , hit_box_2d(hit_box_2d)
{
}


Base::~Base()
{
}


void Base::set_type(std::string type)
{
   this->type = type;
}


void Base::set_model(AllegroFlare::Model3D* model)
{
   this->model = model;
}


void Base::set_texture(ALLEGRO_BITMAP* texture)
{
   this->texture = texture;
}


void Base::set_placement(AllegroFlare::Placement3D placement)
{
   this->placement = placement;
}


void Base::set_velocity(AllegroFlare::Placement3D velocity)
{
   this->velocity = velocity;
}


void Base::set_hit_box_2d(AllegroFlare::Physics::AABB2D hit_box_2d)
{
   this->hit_box_2d = hit_box_2d;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::Model3D* Base::get_model() const
{
   return model;
}


ALLEGRO_BITMAP* Base::get_texture() const
{
   return texture;
}


AllegroFlare::Placement3D Base::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D Base::get_velocity() const
{
   return velocity;
}


AllegroFlare::Physics::AABB2D Base::get_hit_box_2d() const
{
   return hit_box_2d;
}


AllegroFlare::Placement3D &Base::get_placement_ref()
{
   return placement;
}


AllegroFlare::Placement3D &Base::get_velocity_ref()
{
   return velocity;
}


AllegroFlare::Physics::AABB2D &Base::get_hit_box_2d_ref()
{
   return hit_box_2d;
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


