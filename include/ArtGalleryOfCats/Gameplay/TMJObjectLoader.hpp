#pragma once


#include <functional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace ArtGalleryOfCats
{
   namespace Gameplay
   {
      class TMJObjectLoader
      {
      private:
         std::string filename;
         bool loaded;
         std::function<void(std::string, std::string, float, float, float, float, std::vector<std::pair<std::string, std::string>>, void*)> object_parsed_callback;
         void* object_parsed_callback_user_data;
         std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)> map_properties_parsed_callback;
         void* map_properties_parsed_callback_user_data;
         static bool file_exists(std::string filename="[unset-filename]");

      protected:


      public:
         TMJObjectLoader(std::string filename="filename-not-set.tmj");
         ~TMJObjectLoader();

         void set_object_parsed_callback(std::function<void(std::string, std::string, float, float, float, float, std::vector<std::pair<std::string, std::string>>, void*)> object_parsed_callback);
         void set_object_parsed_callback_user_data(void* object_parsed_callback_user_data);
         void set_map_properties_parsed_callback(std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)> map_properties_parsed_callback);
         void set_map_properties_parsed_callback_user_data(void* map_properties_parsed_callback_user_data);
         std::function<void(std::string, std::string, float, float, float, float, std::vector<std::pair<std::string, std::string>>, void*)> get_object_parsed_callback() const;
         void* get_object_parsed_callback_user_data() const;
         std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)> get_map_properties_parsed_callback() const;
         void* get_map_properties_parsed_callback_user_data() const;
         void load();
      };
   }
}



