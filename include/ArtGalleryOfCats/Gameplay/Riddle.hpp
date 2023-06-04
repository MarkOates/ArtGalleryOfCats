#pragma once


#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class Riddle
      {
      private:
         std::string riddle_text;
         std::string riddle_prompt_text;
         std::string riddle_answer;

      protected:


      public:
         Riddle(std::string riddle_text="[unset-riddle_text]", std::string riddle_prompt_text="[unset-prompt_text]", std::string riddle_answer="[unset-riddle_answer]");
         ~Riddle();

         void set_riddle_text(std::string riddle_text);
         void set_riddle_prompt_text(std::string riddle_prompt_text);
         void set_riddle_answer(std::string riddle_answer);
         std::string get_riddle_text() const;
         std::string get_riddle_prompt_text() const;
         std::string get_riddle_answer() const;
         bool matches_answer(std::string answer_guess="[unset-answer_guess]");
      };
   }
}



