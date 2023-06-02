#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
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
            AllegroFlare::Placement3D placement;
            AllegroFlare::Placement3D velocity;

         protected:


         public:
            Base(std::string type=ArtGalleryOfCats::Gameplay::Entities::Base::TYPE, AllegroFlare::Model3D* model=nullptr, ALLEGRO_BITMAP* texture=nullptr, AllegroFlare::Placement3D placement={}, AllegroFlare::Placement3D velocity={});
            ~Base();

            void set_type(std::string type);
            void set_model(AllegroFlare::Model3D* model);
            void set_texture(ALLEGRO_BITMAP* texture);
            void set_placement(AllegroFlare::Placement3D placement);
            void set_velocity(AllegroFlare::Placement3D velocity);
            std::string get_type() const;
            AllegroFlare::Model3D* get_model() const;
            ALLEGRO_BITMAP* get_texture() const;
            AllegroFlare::Placement3D get_placement() const;
            AllegroFlare::Placement3D get_velocity() const;
            AllegroFlare::Placement3D &get_placement_ref();
            AllegroFlare::Placement3D &get_velocity_ref();
         };
      }
   }
}



