

#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Camera3D::Camera3D(std::string type)
   : ArtGalleryOfCats::Gameplay::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Camera3D::TYPE)
   , AllegroFlare::Camera3D({})
   , type(type)
{
}


Camera3D::~Camera3D()
{
}


void Camera3D::set_type(std::string type)
{
   this->type = type;
}


std::string Camera3D::get_type() const
{
   return type;
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


