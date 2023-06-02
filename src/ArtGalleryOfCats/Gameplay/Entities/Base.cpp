

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{
namespace Entities
{


Base::Base(std::string property)
   : ArtGalleryOfCats::Gameplay::Entities::Base(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE)
   , property(property)
{
}


Base::~Base()
{
}


std::string Base::get_property() const
{
   return property;
}


bool Base::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Entities
} // namespace Gameplay
} // namespace ArtGalleryOfCats


