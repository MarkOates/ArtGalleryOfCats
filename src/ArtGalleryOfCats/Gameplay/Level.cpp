

#include <ArtGalleryOfCats/Gameplay/Level.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{


Level::Level(AllegroFlare::SceneGraph::EntityPool entity_pool)
   : entity_pool(entity_pool)
   , current_riddle()
   , riddle_is_solved(false)
{
}


Level::~Level()
{
}


void Level::set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle)
{
   this->current_riddle = current_riddle;
}


void Level::set_riddle_is_solved(bool riddle_is_solved)
{
   this->riddle_is_solved = riddle_is_solved;
}


ArtGalleryOfCats::Gameplay::Riddle Level::get_current_riddle() const
{
   return current_riddle;
}


bool Level::get_riddle_is_solved() const
{
   return riddle_is_solved;
}




} // namespace Gameplay
} // namespace ArtGalleryOfCats


