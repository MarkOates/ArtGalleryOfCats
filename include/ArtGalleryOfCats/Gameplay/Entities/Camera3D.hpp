#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <ArtGalleryOfCats/Gameplay/Entities/Base.hpp>


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

         protected:


         public:
            Camera3D();
            ~Camera3D();

         };
      }
   }
}



