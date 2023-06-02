

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Base::Base(AllegroFlare::Model3D* model)
   : AllegroFlare::SceneGraph::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE)
   , model(model)
{
}


Base::~Base()
{
}


void Base::set_model(AllegroFlare::Model3D* model)
{
   this->model = model;
}


AllegroFlare::Model3D* Base::get_model() const
{
   return model;
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


