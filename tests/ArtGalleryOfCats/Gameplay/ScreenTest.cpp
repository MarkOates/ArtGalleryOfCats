
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/SystemInfo.hpp>


class ArtGalleryOfCats_Gameplay_ScreenTest : public ::testing::Test {};
class ArtGalleryOfCats_Gameplay_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class ArtGalleryOfCats_Gameplay_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(ArtGalleryOfCats_Gameplay_ScreenTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::Screen screen;
}


TEST_F(ArtGalleryOfCats_Gameplay_ScreenTest, TYPE__has_the_expected_value)
{
   ArtGalleryOfCats::Gameplay::Screen screen;
   EXPECT_EQ("ArtGalleryOfCats/Gameplay/Screen", screen.get_type());
}


TEST_F(ArtGalleryOfCats_Gameplay_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   ArtGalleryOfCats::Gameplay::Screen screen;
   EXPECT_EQ(ArtGalleryOfCats::Gameplay::Screen::TYPE, screen.get_type());
}


TEST_F(ArtGalleryOfCats_Gameplay_ScreenTestWithAllegroFrameworksFullFixture,
   DISABLED__will_run_as_expected)
{
   AllegroFlare::SystemInfo HACK_system_info;
   std::string HACK_sysname = HACK_system_info.get_sysname();

   ArtGalleryOfCats::Gameplay::Screen screen;
   std::set<std::string> solved_level_names;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_solved_level_names(&solved_level_names);
   screen.set_model_bin(get_framework_model_bin());
   screen.set_HACK_sysname(HACK_sysname);
   screen.initialize();

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(0.001);
}


TEST_F(ArtGalleryOfCats_Gameplay_ScreenTestWithAllegroFrameworksFullFixture,
   with_level_loaded__will_run_as_expected)
{
   AllegroFlare::SystemInfo HACK_system_info;
   std::string HACK_sysname = HACK_system_info.get_sysname();

   ArtGalleryOfCats::Gameplay::Screen screen;
   std::set<std::string> solved_level_names;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_solved_level_names(&solved_level_names);
   screen.set_model_bin(get_framework_model_bin());
   screen.set_resources_path(get_framework_data_folder_path());
   screen.set_HACK_sysname(HACK_sysname);
   screen.initialize();

   screen.load_level_by_identifier("gallery_01");

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(60);
}


