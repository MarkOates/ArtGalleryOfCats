

#include <ArtGalleryOfCats/Gameplay/TMJObjectLoader.hpp>

#include <AllegroFlare/Errors.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{
namespace Gameplay
{


TMJObjectLoader::TMJObjectLoader(std::string filename)
   : filename(filename)
   , loaded(false)
   , object_parsed_callback({})
   , object_parsed_callback_user_data(nullptr)
   , map_properties_parsed_callback({})
   , map_property_parsed_callback_user_data(nullptr)
{
}


TMJObjectLoader::~TMJObjectLoader()
{
}


void TMJObjectLoader::set_object_parsed_callback(std::function<void(std::string, std::string, float, float, float, float, std::vector<std::pair<std::string, std::string>>, void*)> object_parsed_callback)
{
   this->object_parsed_callback = object_parsed_callback;
}


void TMJObjectLoader::set_object_parsed_callback_user_data(void* object_parsed_callback_user_data)
{
   this->object_parsed_callback_user_data = object_parsed_callback_user_data;
}


void TMJObjectLoader::set_map_properties_parsed_callback(std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)> map_properties_parsed_callback)
{
   this->map_properties_parsed_callback = map_properties_parsed_callback;
}


void TMJObjectLoader::set_map_property_parsed_callback_user_data(void* map_property_parsed_callback_user_data)
{
   this->map_property_parsed_callback_user_data = map_property_parsed_callback_user_data;
}


std::function<void(std::string, std::string, float, float, float, float, std::vector<std::pair<std::string, std::string>>, void*)> TMJObjectLoader::get_object_parsed_callback() const
{
   return object_parsed_callback;
}


void* TMJObjectLoader::get_object_parsed_callback_user_data() const
{
   return object_parsed_callback_user_data;
}


std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)> TMJObjectLoader::get_map_properties_parsed_callback() const
{
   return map_properties_parsed_callback;
}


void* TMJObjectLoader::get_map_property_parsed_callback_user_data() const
{
   return map_property_parsed_callback_user_data;
}


void TMJObjectLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJObjectLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJObjectLoader::load: error: guard \"(!loaded)\" not met");
   }
   int tile_width = 1;
   int tile_height = 1;

   if (!file_exists(filename))
   {
      std::stringstream error_message;
      error_message << "[ArtGalleryOfCats::Gameplay::TMJObjectLoader::load()]: error: The file "
                    << "\"" << filename << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json source_json;
   try
   {
      i >> source_json;
   }
   catch (const std::exception& e)
   {
      i.close();
      std::stringstream error_message;
      error_message << "The file "
                    << "\"" << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      AllegroFlare::Errors::throw_error("ArtGalleryOfCats::Gameplay::TMJObjectLoader", error_message.str());
   }
   i.close();


   // TODO: validate there is one and only "objectgroup" layer

   // get first j["layers"] that is a ["type"] == "objectgroup"
   bool object_layer_type_found = false;
   nlohmann::json object_layer_json;
   for (auto &layer : source_json["layers"].items())
   {
      if (layer.value()["type"] == "objectgroup")
      {
         object_layer_json = layer.value();
         object_layer_type_found = true;
         break;
      }
   }
   if (!object_layer_type_found)
   {
      // TODO: Swap this error message with AllegroFlare::Errors
      throw std::runtime_error("TMJObjectLoader: error: layer of type \"objectgroup\" not found.");
   }


   // TODO: Validate presence of the keys "tilewidth" and "tileheight"
   // TODO: Validate type of the keys "tilewidth" and "tileheight" as int

   tile_width = source_json["tilewidth"].get<int>();
   tile_height = source_json["tileheight"].get<int>();

   // load the objects one by one

   if (!object_layer_json.contains("objects"))
   {
      std::stringstream error_message;
      error_message << "Expecting [\"objects\"] to exist in the \"objectgoup\"-type layer, but it does not.";
      AllegroFlare::Errors::throw_error("ArtGalleryOfCats::Gameplay::TMJObjectLoader", error_message.str());
   }
   for (auto &object_json : object_layer_json["objects"].items())
   {
      // TODO: validate the presence of these keys
      std::string name_property = object_json.value()["name"].get<std::string>();
      std::string class_property = object_json.value()["class"].get<std::string>();
      float x_property = object_json.value()["x"].get<float>();
      float y_property = object_json.value()["y"].get<float>();
      float width_property = object_json.value()["width"].get<float>();
      float height_property = object_json.value()["height"].get<float>();
      std::vector<std::pair<std::string, std::string>> custom_properties;

      // Collect custom properties
      // TODO: Test this
      if (object_json.value().contains("properties"))
      {
         for (auto &custom_property : object_json.value()["properties"].items())
         {
            // TODO: validate presence of keys
            std::string custom_property_name = custom_property.value()["name"].get<std::string>();
            std::string custom_property_type = custom_property.value()["type"].get<std::string>();
            if (custom_property_type != "string") throw std::runtime_error("TMJObjectLoader, expecting type string");
            std::string custom_property_value = custom_property.value()["value"].get<std::string>();

            custom_properties.push_back({ custom_property_name, custom_property_value });
         }
      }

      // call the callback (if present)
      if (object_parsed_callback)
      {
         object_parsed_callback(
            name_property,
            class_property,
            x_property / (float)tile_width,
            y_property / (float)tile_height,
            width_property / (float)tile_width,
            height_property / (float)tile_height,
            custom_properties,
            object_parsed_callback_user_data
         );
      }
   }

   // Parse out the custom map properties ("properties" at the root level of the JSON)
   std::vector<std::tuple<std::string, std::string, std::string>> collected_map_custom_properties = {};
   if (!source_json.contains("properties"))
   {
      std::stringstream error_message;
      error_message << "Expecting [\"properties\"] to exist in the root object, but it does not.";
      AllegroFlare::Errors::throw_error("ArtGalleryOfCats::Gameplay::TMJObjectLoader", error_message.str());
   }
   for (auto &object_json : source_json["properties"].items())
   {
      for (auto &custom_map_property : object_json.value()["properties"].items())
      {
         std::string custom_map_property_name = custom_map_property.value()["name"].get<std::string>();
         std::string custom_map_property_type = custom_map_property.value()["type"].get<std::string>();
         if (custom_map_property_type != "string") throw std::runtime_error("TMJObjectLoader,(with properties) expecting type string");
         std::string custom_map_property_value = custom_map_property.value()["value"].get<std::string>();
         //map_property_parsed_callback()

         //type: std::function<void(std::vector<std::tuple<std::string, std::string, std::string>>, void*)>

         collected_map_custom_properties.push_back(
            std::tuple<std::string, std::string, std::string>(
               custom_map_property_name, custom_map_property_type, custom_map_property_value
            )
         );
      }
   }

   // TODO: Test this
   if (object_parsed_callback && !collected_map_custom_properties.empty())
   {
      // TODO: Test this
      map_properties_parsed_callback(
          collected_map_custom_properties,
          map_property_parsed_callback_user_data
       );
    }

   return;
}

bool TMJObjectLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Gameplay
} // namespace ArtGalleryOfCats


