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
         std::string user_input_prompt_text;
         std::string correct_answer_text;

      protected:


      public:
         Riddle(std::string riddle_text="[unset-riddle_text]", std::string user_input_prompt_text="[unset-user_input_prompt_text]", std::string correct_answer_text="[unset-user_input_prompt_text]");
         ~Riddle();

         void set_riddle_text(std::string riddle_text);
         void set_user_input_prompt_text(std::string user_input_prompt_text);
         void set_correct_answer_text(std::string correct_answer_text);
         std::string get_riddle_text() const;
         std::string get_user_input_prompt_text() const;
         std::string get_correct_answer_text() const;
      };
   }
}



