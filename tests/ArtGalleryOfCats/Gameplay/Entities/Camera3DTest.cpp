
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/Entities/Camera3D.hpp>


TEST(ArtGalleryOfCats_Gameplay_Entities_Camera3DTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::Entities::Camera3D camera3d;
}


TEST(ArtGalleryOfCats_Gameplay_Entities_Camera3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "ArtGalleryOfCats/Gameplay/Entities/Camera3D",
     ArtGalleryOfCats::Gameplay::Entities::Camera3D::TYPE
   );
}


TEST(ArtGalleryOfCats_Gameplay_Entities_Camera3DTest, type__has_the_expected_value_matching_TYPE)
{
   ArtGalleryOfCats::Gameplay::Entities::Camera3D camera3d;
   EXPECT_EQ(ArtGalleryOfCats::Gameplay::Entities::Camera3D::TYPE, camera3d.get_type());
}


