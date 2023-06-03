#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


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
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string dialog_bubble_bitmap_identifier;
            int inv_scale;
            ALLEGRO_BITMAP* capture;
            bool initialized;

         protected:


         public:
            NPCConversations(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string dialog_bubble_bitmap_identifier="dialog_bubble-01.png");
            virtual ~NPCConversations();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_dialog_bubble_bitmap_identifier(std::string dialog_bubble_bitmap_identifier);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::string get_dialog_bubble_bitmap_identifier() const;
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



