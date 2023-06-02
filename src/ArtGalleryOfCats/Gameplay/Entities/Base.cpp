

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Base::Base(std::string type, AllegroFlare::Model3D* model, ALLEGRO_BITMAP* texture)
   : AllegroFlare::SceneGraph::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE)
   , type(type)
   , model(model)
   , texture(texture)
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




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


