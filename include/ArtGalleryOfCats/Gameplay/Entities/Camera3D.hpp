#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>
#include <string>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      namespace Entities
      {
         class Camera3D : public ArtGalleryOfCats::Gameplay::Entities::Base, public AllegroFlare::Camera3D
         {
         public:
            static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Gameplay/Entities/Camera3D";

         private:
            std::string type;

         protected:


         public:
            Camera3D(std::string type="[unset-Camera3D_type]");
            ~Camera3D();

            void set_type(std::string type);
            std::string get_type() const;
         };
      }
   }
}



