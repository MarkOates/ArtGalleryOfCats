

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Base::Base(std::string type, AllegroFlare::Model3D* model, ALLEGRO_BITMAP* texture, AllegroFlare::Placement3D placement, AllegroFlare::Placement3D velocity)
   : AllegroFlare::SceneGraph::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE)
   , type(type)
   , model(model)
   , texture(texture)
   , placement(placement)
   , velocity(velocity)
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


AllegroFlare::Placement3D &Base::get_placement_ref()
{
   return placement;
}


AllegroFlare::Placement3D &Base::get_velocity_ref()
{
   return velocity;
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


