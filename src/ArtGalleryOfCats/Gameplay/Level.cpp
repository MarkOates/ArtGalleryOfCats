

#include <ArtGalleryOfCats/Gameplay/Level.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{


Level::Level(std::string name, std::string title, std::string music_identifier)
   : name(name)
   , title(title)
   , entity_pool({})
   , current_riddle()
   , music_identifier(music_identifier)
   , riddle_is_solved(false)
{
}


Level::~Level()
{
}


void Level::set_name(std::string name)
{
   this->name = name;
}


void Level::set_title(std::string title)
{
   this->title = title;
}


void Level::set_current_riddle(ArtGalleryOfCats::Gameplay::Riddle current_riddle)
{
   this->current_riddle = current_riddle;
}


void Level::set_music_identifier(std::string music_identifier)
{
   this->music_identifier = music_identifier;
}


void Level::set_riddle_is_solved(bool riddle_is_solved)
{
   this->riddle_is_solved = riddle_is_solved;
}


std::string Level::get_name() const
{
   return name;
}


std::string Level::get_title() const
{
   return title;
}


ArtGalleryOfCats::Gameplay::Riddle Level::get_current_riddle() const
{
   return current_riddle;
}


std::string Level::get_music_identifier() const
{
   return music_identifier;
}


bool Level::get_riddle_is_solved() const
{
   return riddle_is_solved;
}


AllegroFlare::SceneGraph::EntityPool &Level::get_entity_pool_ref()
{
   return entity_pool;
}


ArtGalleryOfCats::Gameplay::Riddle &Level::get_current_riddle_ref()
{
   return current_riddle;
}


bool Level::has_custom_music()
{
   return (music_identifier != DEFAULT_MUSIC_IDENTIFIER);
}

void Level::destroy()
{
   // TODO: Clear entity pool
   return;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


