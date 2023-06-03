#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <allegro5/allegro.h>


namespace ArtGalleryOfCats
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class NPCConversations : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr int DEFAULT_INV_SCALE = 10;
            static constexpr char* TYPE = (char*)"ArtGalleryOfCats/Elements/Backgrounds/NPCConversations";

         private:
            int inv_scale;
            ALLEGRO_BITMAP* capture;
            bool initialized;

         protected:


         public:
            NPCConversations();
            virtual ~NPCConversations();

            int get_inv_scale() const;
            void set_inv_scale(int inv_scale=DEFAULT_INV_SCALE);
            void initialize();
            void destroy();
            void refresh_capture();
            virtual void activate() override;
            virtual void render() override;
         };
      }
   }
}



