
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Elements/Backgrounds/NPCConversations.hpp>


TEST(ArtGalleryOfCats_Elements_Backgrounds_NPCConversationsTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Elements::Backgrounds::NPCConversations npcconversations;
}


TEST(ArtGalleryOfCats_Elements_Backgrounds_NPCConversationsTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "ArtGalleryOfCats/Elements/Backgrounds/NPCConversations",
     ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::TYPE
   );
}


TEST(ArtGalleryOfCats_Elements_Backgrounds_NPCConversationsTest, type__has_the_expected_value_matching_TYPE)
{
   ArtGalleryOfCats::Elements::Backgrounds::NPCConversations npcconversations;
   EXPECT_EQ(ArtGalleryOfCats::Elements::Backgrounds::NPCConversations::TYPE, npcconversations.get_type());
}


