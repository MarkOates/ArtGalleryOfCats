#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <string>


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
            std::string type;
            AllegroFlare::Model3D* model;

         protected:


         public:
            Base(std::string type=ArtGalleryOfCats::Gameplay::Entities::Base::TYPE, AllegroFlare::Model3D* model=nullptr);
            ~Base();

            void set_type(std::string type);
            void set_model(AllegroFlare::Model3D* model);
            std::string get_type() const;
            AllegroFlare::Model3D* get_model() const;
         };
      }
   }
}



