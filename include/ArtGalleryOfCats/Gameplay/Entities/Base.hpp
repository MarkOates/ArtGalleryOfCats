#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/SceneGraph/Entities/Base.hpp>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      namespace Entities
      {
         class Base : public AllegroFlare::SceneGraph::Entities::Base
         {
         public:
            static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Gameplay/Entities/Base";

         private:
            AllegroFlare::Model3D* model;

         protected:


         public:
            Base(AllegroFlare::Model3D* model=nullptr);
            ~Base();

            void set_model(AllegroFlare::Model3D* model);
            AllegroFlare::Model3D* get_model() const;
         };
      }
   }
}



