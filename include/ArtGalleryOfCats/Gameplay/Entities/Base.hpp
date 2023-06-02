#pragma once


#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>
#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      namespace Entities
      {
         class Base : public ArtGalleryOfCats::Gameplay::Entities::Base
         {
         public:
            static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Gameplay/Entities/Base";

         private:
            std::string property;

         protected:


         public:
            Base(std::string property="[unset-property]");
            ~Base();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



