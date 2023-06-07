

#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Camera3D::Camera3D()
   : ArtGalleryOfCats::Gameplay::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Camera3D::TYPE)
   , AllegroFlare::Camera3D({})
{
}


Camera3D::~Camera3D()
{
}




} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


