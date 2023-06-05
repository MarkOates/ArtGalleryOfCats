#pragma once




namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class EntityFlags
      {
      public:
         static constexpr char* PLAYER_CAN_INTERACT = (char*)"player_can_interact";
         static constexpr char* IS_WALL_ART = (char*)"is_wall_art";
         static constexpr char* IS_SCULPTURE_ART = (char*)"is_sculpture_art";
         static constexpr char* RENDERS_WITH_IRIDESCENT = (char*)"renders_with_iridescent";
         static constexpr char* ART_IDENTIFIER = (char*)"art_identifier";
         static constexpr char* DO_NOT_RENDER = (char*)"do_not_render";

      private:

      protected:


      public:
         EntityFlags();
         ~EntityFlags();

      };
   }
}



