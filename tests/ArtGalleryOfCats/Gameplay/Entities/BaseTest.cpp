
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>


TEST(ArtGalleryOfCats_Gameplay_Entities_BaseTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::Entities::Base base;
}


TEST(ArtGalleryOfCats_Gameplay_Entities_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "ArtGalleryOfCats/Gameplay/Entities/Base",
     ArtGalleryOfCats::Gameplay::Entities::Base::TYPE
   );
}


TEST(ArtGalleryOfCats_Gameplay_Entities_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   ArtGalleryOfCats::Gameplay::Entities::Base base;
   EXPECT_EQ(ArtGalleryOfCats::Gameplay::Entities::Base::TYPE, base.get_type());
}


