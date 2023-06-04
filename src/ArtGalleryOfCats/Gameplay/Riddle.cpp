

#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>




namespace ArtGalleryOfCats
{
namespace Gameplay
{


Riddle::Riddle(std::string riddle_text, std::string user_input_prompt_text, std::string correct_answer_text)
   : riddle_text(riddle_text)
   , user_input_prompt_text(user_input_prompt_text)
   , correct_answer_text(correct_answer_text)
{
}


Riddle::~Riddle()
{
}


void Riddle::set_riddle_text(std::string riddle_text)
{
   this->riddle_text = riddle_text;
}


void Riddle::set_user_input_prompt_text(std::string user_input_prompt_text)
{
   this->user_input_prompt_text = user_input_prompt_text;
}


void Riddle::set_correct_answer_text(std::string correct_answer_text)
{
   this->correct_answer_text = correct_answer_text;
}


std::string Riddle::get_riddle_text() const
{
   return riddle_text;
}


std::string Riddle::get_user_input_prompt_text() const
{
   return user_input_prompt_text;
}


std::string Riddle::get_correct_answer_text() const
{
   return correct_answer_text;
}




} // namespace Gameplay
} // namespace ArtGalleryOfCats


