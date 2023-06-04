
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/Riddle.hpp>


TEST(ArtGalleryOfCats_Gameplay_RiddleTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::Riddle riddle;
}


TEST(ArtGalleryOfCats_Gameplay_RiddleTest, matches_answer__when_the_answer_is_correct__returns_true)
{
   ArtGalleryOfCats::Gameplay::Riddle riddle("5 and 4, surely no more.", "What 5 and 4?", "9");
   std::string guess = "9";
   EXPECT_EQ(true, riddle.matches_answer(guess));
}


TEST(ArtGalleryOfCats_Gameplay_RiddleTest, matches_answer__when_the_answer_is_not_correct__returns_false)
{
   ArtGalleryOfCats::Gameplay::Riddle riddle("5 and 4, surely no more.", "What 5 and 4?", "9");
   std::string guess = "42";
   EXPECT_EQ(false, riddle.matches_answer(guess));
}


TEST(ArtGalleryOfCats_Gameplay_RiddleTest, matches_answer__will_match_case_insensitive)
{
   ArtGalleryOfCats::Gameplay::Riddle riddle("5 and 4, surely no more.", "What 5 and 4?", "Happy");
   std::string guess = "hApPy";
   EXPECT_EQ(true, riddle.matches_answer(guess));
}


