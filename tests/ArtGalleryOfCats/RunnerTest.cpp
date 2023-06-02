
#include <gtest/gtest.h>

#include <ArtGalleryOfCats/Runner.hpp>


TEST(ArtGalleryOfCats_RunnerTest, can_be_created_without_blowing_up)
{
   ArtGalleryOfCats::Runner runner;
}


TEST(ArtGalleryOfCats_RunnerTest, INTERACTIVE__run__will_work_as_expected)
{
   ArtGalleryOfCats::Runner runner;
   runner.run("test");
}


