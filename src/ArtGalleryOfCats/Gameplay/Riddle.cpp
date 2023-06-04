

#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{


Riddle::Riddle(std::string riddle_text, std::string riddle_prompt_text, std::string riddle_answer)
   : riddle_text(riddle_text)
   , riddle_prompt_text(riddle_prompt_text)
   , riddle_answer(riddle_answer)
{
}


Riddle::~Riddle()
{
}


void Riddle::set_riddle_text(std::string riddle_text)
{
   this->riddle_text = riddle_text;
}


void Riddle::set_riddle_prompt_text(std::string riddle_prompt_text)
{
   this->riddle_prompt_text = riddle_prompt_text;
}


void Riddle::set_riddle_answer(std::string riddle_answer)
{
   this->riddle_answer = riddle_answer;
}


std::string Riddle::get_riddle_text() const
{
   return riddle_text;
}


std::string Riddle::get_riddle_prompt_text() const
{
   return riddle_prompt_text;
}


std::string Riddle::get_riddle_answer() const
{
   return riddle_answer;
}


bool Riddle::matches_answer(std::string answer_guess)
{
   // TODO: Account for additional rules (case insensitive, etc)
   if (answer_guess == riddle_answer) return true;
   return false;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


