
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Gameplay/TMJObjectLoader.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


static std::vector<std::pair<std::string, std::string>> custom_properties;


static void object_parsed_callback(
      std::string name_property,
      std::string class_property,
      float x_property,
      float y_property,
      float width_property,
      float height_property,
      std::vector<std::pair<std::string, std::string>> custom_properties,
      void* user_data
   )
{
   std::cout << "- name: \"" << name_property << "\"" << std::endl;
   std::cout << "  class: \"" << class_property << "\"" << std::endl;
   std::cout << std::endl;
   return;
}


TEST(ArtGalleryOfCats_Gameplay_TMJObjectLoaderTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Gameplay::TMJObjectLoader tmjobject_loader;
}


TEST(ArtGalleryOfCats_Gameplay_TMJObjectLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   ArtGalleryOfCats::Gameplay::TMJObjectLoader loader(filename);

   std::string expected_error_message = "[ArtGalleryOfCats::Gameplay::TMJObjectLoader::load()]: error: The file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(ArtGalleryOfCats_Gameplay_TMJObjectLoaderTest, load__will_not_blow_up)
{
   std::string filename = "/Users/markoates/Repos/ArtGalleryOfCats/tests/fixtures/maps/gallery-map-07.tmj";
   ArtGalleryOfCats::Gameplay::TMJObjectLoader loader(filename);
   loader.load();
}


TEST(ArtGalleryOfCats_Gameplay_TMJObjectLoaderTest, load__will_pass_the_values_into_the_callback)
{
   std::string filename = "/Users/markoates/Repos/ArtGalleryOfCats/tests/fixtures/maps/gallery-map-07.tmj";
   ArtGalleryOfCats::Gameplay::TMJObjectLoader loader(filename);
   loader.set_object_parsed_callback(object_parsed_callback);
   loader.load();
}


