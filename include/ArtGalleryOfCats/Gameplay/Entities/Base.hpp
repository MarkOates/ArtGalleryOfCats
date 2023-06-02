#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <allegro5/allegro.h>
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
            ALLEGRO_BITMAP* texture;

         protected:


         public:
            Base(std::string type=ArtGalleryOfCats::Gameplay::Entities::Base::TYPE, AllegroFlare::Model3D* model=nullptr, ALLEGRO_BITMAP* texture=nullptr);
            ~Base();

            void set_type(std::string type);
            void set_model(AllegroFlare::Model3D* model);
            void set_texture(ALLEGRO_BITMAP* texture);
            std::string get_type() const;
            AllegroFlare::Model3D* get_model() const;
            ALLEGRO_BITMAP* get_texture() const;
         };
      }
   }
}



