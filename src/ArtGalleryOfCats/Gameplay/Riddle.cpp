

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
   std::string filtered_answer_guess = answer_guess;
   std::string filtered_riddle_answer = riddle_answer;

   bool case_sensitive = false; // TODO: Consider making this a flag
   if (!case_sensitive)
   {
      for (char &c : filtered_answer_guess) { c = std::tolower(c); }
      for (char &c : filtered_riddle_answer) { c = std::tolower(c); }
   }

   // TODO: Account for additional rules (case insensitive, etc)
   if (filtered_answer_guess == filtered_riddle_answer) return true;
   return false;
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


