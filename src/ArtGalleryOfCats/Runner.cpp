

#include <ArtGalleryOfCats/Runner.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/RouteEventDatas/StartLevel.hpp>
#include <AllegroFlare/StoryboardFactory.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace ArtGalleryOfCats
{


Runner::Runner(AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, std::string resources_path)
   : AllegroFlare::Screens::Base(ArtGalleryOfCats::Runner::TYPE)
   , framework(framework)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , resources_path(resources_path)
   , router()
   , intro_logos_screen()
   , intro_storyboard_screen()
   , title_screen()
   , achievements_screen()
   , version_screen()
   , new_game_intro_storyboard_screen()
   , level_select_screen()
   , game_over_screen()
   , game_won_screen()
   , npc_conversations_screen()
   , user_text_input_screen()
   , game_won_outro_storyboard_screen()
   , rolling_credits_screen()
   , primary_gameplay_screen()
   , solid_black_background(ALLEGRO_COLOR{0, 0, 0, 1})
   , light_blue_background(ALLEGRO_COLOR{148.0f/255, 191.0f/255, 226.0f/255, 1})
   , npc_conversations_background({})
   , release_info({})
   , initialized(false)
{
}


Runner::~Runner()
{
}


void Runner::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"framework\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Runner::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::initialize: error: guard \"model_bin\" not met");
   }
   // Create the resources
   AllegroFlare::Achievements &achievements = framework->get_achievements_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   // Create a storyboard factory and page factory
   AllegroFlare::StoryboardFactory storyboard_factory;
   storyboard_factory.set_font_bin(font_bin);
   storyboard_factory.set_event_emitter(event_emitter);
   AllegroFlare::StoryboardPageFactory page_factory;
   page_factory.set_font_bin(font_bin);
   page_factory.set_bitmap_bin(bitmap_bin);
   page_factory.set_model_bin(model_bin);

   // Setup our router
   setup_router();

   // Set the framework to use our router
   framework->set_router(&router);

   // TODO: Setup achievements
   achievements.set_achievements({
      { "stay_through_the_credits",
         new AllegroFlare::Achievement("Stay Through the Credits", "Watch the credits"),
         false,
         false,
      },
      { "look_at_some_art",
         new AllegroFlare::Achievement("Beauty Beholder", "Observe some art in the gallery"),
         false,
         false,
      },
      { "solve_a_riddle",
         new AllegroFlare::Achievement("Riddle Wrangler", "Solve one of the riddles"),
         false,
         false,
      },
   });

   // TODO: Setup intro logos screen
   intro_logos_screen.set_event_emitter(event_emitter);
   intro_logos_screen.set_font_bin(font_bin);
   intro_logos_screen.set_auto_advance(true);
   intro_logos_screen.set_background(&solid_black_background);
   intro_logos_screen.initialize();
   intro_logos_screen.get_storyboard_element_ref().set_pages({
      page_factory.create_clubcatt_logo_page(),
      page_factory.create_image_page(bitmap_bin->operator[]("clubcatt-website-01.jpg")),
   });

   // TODO: Setup intro storyboard screen
   intro_storyboard_screen.set_event_emitter(event_emitter);
   intro_storyboard_screen.set_font_bin(font_bin);
   intro_storyboard_screen.set_auto_advance(true);
   intro_storyboard_screen.set_background(&light_blue_background);
   intro_storyboard_screen.initialize();
   intro_storyboard_screen.get_storyboard_element_ref().set_pages({
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-1-01-1165x500.png",
         //"Once upon a time, in a magical kingdom ruled by a wise and just queen, a young hero sets out on a "
            //"journey to prove himself and save his people from a terrible curse."
      //),
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-2-01-1165x500.png",
         //"With the help of his trusty sidekick and a band of unlikely allies, he must navigate treacherous "
            //"terrain and battle fierce foes."
      //),
      //page_factory.create_advancing_text_page(
        //"And achieve his goal to save the kingdom."
      //),
   });

   // TODO: Setup title screen
   title_screen.set_event_emitter(event_emitter);
   title_screen.set_menu_options({
      //{ "Investigate", "start_new_game" },
      { "Start New Game", "start_new_game" },
                        //EVENT_ACTIVATE_PLATFORMING_2D_SCREEN }, //EVENT_ACTIVATE_NAME_YOUR_CHARACTER_SCREEN },
      //{ "Chronicle",      EVENT_OPEN_CHRONICLE_SCREEN },
      //{ "Driving",        EVENT_ACTIVATE_TILE_DRIVE_SCREEN },
      //{ "Platforming",    EVENT_ACTIVATE_PLATFORMING_2D_SCREEN },
      //{ "Investigate",    EVENT_ACTIVATE_INVESTIGATION_ROOM_SCREEN },
      { "Achievements",   "goto_achievements_screen" },
      //{ "Storyboard",     EVENT_ACTIVATE_CUT_IN_STORYBOARD_SCREEN},
      { "Version",        "goto_version_screen" },
      //{ "Credits",        EVENT_ACTIVATE_CREDITS_SCREEN },
      { "Quit",           "quit" },
   });
   title_screen.set_font_bin(font_bin);
   std::string copyright_text = "© 2023 CLUBCATT Games         clubcatt.com         version " + release_info.get_version();
   title_screen.set_copyright_text(copyright_text);
   title_screen.set_title_text("Art Gallery of Cats");
   title_screen.set_background(&solid_black_background);
   //title_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // TODO: Setup achievements screen
   achievements_screen.set_achievements(&achievements);
   achievements_screen.set_event_emitter(event_emitter);
   achievements_screen.set_font_bin(font_bin);
   achievements_screen.set_background(&solid_black_background);
   achievements_screen.initialize();

   // TODO: Setup version screen
   version_screen.set_bitmap_bin(bitmap_bin);
   version_screen.set_font_bin(font_bin);
   version_screen.set_model_bin(model_bin);
   version_screen.set_event_emitter(event_emitter);
   version_screen.set_background(&solid_black_background);
   version_screen.initialize();

   // TODO: Setup new game intro storyboard screen
   new_game_intro_storyboard_screen.set_event_emitter(event_emitter);
   new_game_intro_storyboard_screen.set_font_bin(font_bin);
   new_game_intro_storyboard_screen.set_background(&solid_black_background);
   new_game_intro_storyboard_screen.initialize();
   new_game_intro_storyboard_screen.get_storyboard_element_ref().set_pages({
       //page_factory.create_advancing_text_page(
         //"In a land beset by darkness, a young hero embarks on a perilous journey to retrieve a powerful "
            //"artifact that can restore light to the kingdom."
       //),
       //page_factory.create_advancing_text_page(
         //"With nothing but a trusty sword and his wits to guide him, he sets out to face whatever dangers "
            //"lie ahead."
       //),
   });



   // Setup the npc_conversations_screen_background
   npc_conversations_background.set_inv_scale(1);
   npc_conversations_background.set_bitmap_bin(bitmap_bin);
   npc_conversations_background.initialize();

   // Setup the npc_conversations_screen
   npc_conversations_screen.set_event_emitter(event_emitter);
   npc_conversations_screen.set_font_bin(font_bin);
   npc_conversations_screen.set_background(&npc_conversations_background);
   npc_conversations_screen.initialize();
   npc_conversations_screen.get_storyboard_element_ref().set_pages({
       create_image_page(
       //page_factory.create_advancing_text_page(
         "Hmm. There's a chart over there."
          //I guess I would be.",
         //"I really like all this art! It nourishes the spirit. It ignites the soul!"
       //),
       ),
       create_image_page(
       //page_factory.create_advancing_text_page(
          "I guess if I were a human, I'd be 25 years old."
       ),
   });


   // Setup the "user_text_input_screen"
   user_text_input_screen.set_font_bin(font_bin);
   user_text_input_screen.set_font_size(-40);
   user_text_input_screen.set_event_emitter(event_emitter);
   user_text_input_screen.initialize();
   // Use "keyboard" mode (keyboard keys will type characters)
   user_text_input_screen.set_mode_to_using_keyboard();


   // TODO: Setup level select screen
   level_select_screen.set_event_emitter(event_emitter);
   level_select_screen.set_bitmap_bin(bitmap_bin);
   level_select_screen.set_font_bin(font_bin);
   level_select_screen.set_levels_list({
      //{ "Candy Kingdom", "candy_kingdom" },
      //{ "Cherry Blossom Grove", "cherry_blossom_grove" },
      //{ "Bubble Pop Bay", "bubble_pop_bay" },
      //{ "Neon City Nights", "neon_city_nights" },
      //{ "Wonderland Woods", "wonderland_woods" },
      { "1", "candy_kingdom" },
      { "2", "cherry_blossom_grove" },
      { "3", "bubble_pop_bay" },
      { "4", "neon_city_nights" },
      { "5", "wonderland_woods" },
   });
   level_select_screen.set_background(&solid_black_background);
   level_select_screen.initialize();

   // TODO: Setup game over screen
   game_over_screen.set_background(&solid_black_background);
   game_over_screen.initialize();

   // TODO: Setup game won screen
   game_won_screen.set_background(&solid_black_background);
   game_won_screen.set_font_bin(font_bin);
   //game_won_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // TODO: Setup game won outro storyboard screen
   game_won_outro_storyboard_screen.set_event_emitter(event_emitter);
   game_won_outro_storyboard_screen.set_background(&light_blue_background);
   game_won_outro_storyboard_screen.set_font_bin(font_bin);
   game_won_outro_storyboard_screen.get_storyboard_element_ref().set_pages({
       create_image_page(
         "Well that was a wonderful adventure."
       ),
       create_image_page(
         "I hope you enjoyed your time here at the Art Gallery of Cats!"
       ),
       //page_factory.create_advancing_text_page(
         //"Well that was a wonderful adventure. I hope you enjoyed your time here at the Art Gallery of Cats.",
       //),
   });
   game_won_outro_storyboard_screen.initialize();

   // TODO: Setup rolling credits screen
   rolling_credits_screen.set_event_emitter(event_emitter); // NEEDED in startup template
   rolling_credits_screen.set_font_bin(font_bin);
   rolling_credits_screen.set_background(&solid_black_background);
   rolling_credits_screen.initialize();


   // Setup our main gameplay screen
   primary_gameplay_screen.set_event_emitter(event_emitter);
   primary_gameplay_screen.set_bitmap_bin(bitmap_bin);
   primary_gameplay_screen.set_font_bin(font_bin);
   primary_gameplay_screen.set_model_bin(model_bin);
   primary_gameplay_screen.set_resources_path(resources_path);
   primary_gameplay_screen.set_user_text_input_screen(&user_text_input_screen);
   primary_gameplay_screen.initialize();

   // TODO: Load up our sound effects
   audio_controller.set_and_load_sound_effect_elements({
      // { "menu_move", { "menu_move_tink-02.ogg", false, "restart" } }, // TODO: Throw on an unknown replay type
   });

   // TODO: Load up our music tracks
   audio_controller.set_and_load_music_track_elements({
      // An example of how to load a music track:
      //{ "intro_music", { "wanderer-01.ogg", true, "ignore" } },
   });

   // An example of how to play a music track:
   // event_emitter->emit_play_music_track_event("intro_music");

   return;
}

void Runner::setup_router()
{
   router.set_screen_manager(&framework->get_screen_manager_ref());
   router.set_event_emitter(event_emitter);

   // Set the "load_level" handler
   router.set_load_level_handler([this](AllegroFlare::RouteEventDatas::Base* route_event_data) -> bool {
      // TODO: Fill in the body of this function:
      // TODO: Validate route_event_data is non-void
      // TODO: Validate route_event_data is StartLevel type

      AllegroFlare::RouteEventDatas::StartLevel *as_start_level =
         static_cast<AllegroFlare::RouteEventDatas::StartLevel*>(route_event_data);

      std::string level_identifier_to_load = as_start_level->get_level_identifier();

      // TODO: Modify this design to emit a level loading event, instead of loading here explicitly.
      primary_gameplay_screen.load_level_by_identifier(level_identifier_to_load);

      // TODO: Improve design and address a "return false" if the level did not load or does not exist
      // TODO: Address concern that return type of lambda may not be the same signature of the load_level_handler
      return true;
   });

   // Set the routes
   router.register_screen(
      AllegroFlare::Routers::Standard::INTRO_LOGOS_SCREEN_IDENTIFIER,
      &intro_logos_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::INTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &intro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::TITLE_SCREEN_IDENTIFIER,
      &title_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::ACHIEVEMENTS_SCREEN_IDENTIFIER,
      &achievements_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::VERSION_SCREEN_IDENTIFIER,
      &version_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &new_game_intro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::LEVEL_SELECT_SCREEN_IDENTIFIER,
      &level_select_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_OVER_SCREEN_IDENTIFIER,
      &game_over_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_WON_SCREEN_IDENTIFIER,
      &game_won_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &game_won_outro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::CREDITS_SCREEN_IDENTIFIER,
      &rolling_credits_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER,
      &primary_gameplay_screen
   );
   router.register_screen(
      NPC_CONVERSATIONS_SCREEN,
      &npc_conversations_screen
   );
   router.register_screen(
      USER_TEXT_INPUT_SCREEN,
      &user_text_input_screen
   );

   // Set the callbacks
   intro_logos_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_INTRO_LOGOS_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   intro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_INTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   new_game_intro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   level_select_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::LevelSelectScreen* screen, void* data) {
         // TODO: validate "screen" is non-void

         std::string selected_menu_option_value = screen->infer_current_menu_option_value();

         AllegroFlare::RouteEventDatas::StartLevel *route_event_data = new AllegroFlare::RouteEventDatas::StartLevel;
         route_event_data->set_level_identifier(selected_menu_option_value);

         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_START_LEVEL,
            route_event_data,
            al_get_time()
         );
      }
   );
   primary_gameplay_screen.set_on_finished_callback_func(
      [this](ArtGalleryOfCats::Gameplay::Screen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   game_won_outro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   rolling_credits_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::RollingCredits* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_CREDITS_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   title_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::TitleScreen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_TITLE_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   title_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::TitleScreen* screen, void* data) {
         std::string menu_choice = screen->infer_current_menu_option_value();

         if (menu_choice == "start_new_game")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_START_NEW_GAME,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "quit")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_EXIT_GAME,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_achievements_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_version_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_VERSION_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else
         {
            AllegroFlare::Logger::throw_error("Foobar", "baz");
         }
      }
   );
   achievements_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::Achievements* screen, void* data) {
         // TODO: This should be a push/pop'd screen
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   version_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::Version* screen, void* data) {
         // TODO: This should be a push/pop'd screen
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   npc_conversations_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );

   return;
}

void Runner::run(std::string deployment_environment_mode)
{
   // setup the framework
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment(deployment_environment_mode);
   //if (disable_escape_key_will_shutdown) framework.disable_escape_key_will_shutdown();
   framework.initialize();

   // instantiate our actual game runner
   Runner runner(
      &framework,
      &framework.get_event_emitter_ref(),
      &framework.get_bitmap_bin_ref(),
      &framework.get_font_bin_ref(),
      &framework.get_model_bin_ref(),
      framework.get_data_folder_path()
   );
   runner.initialize();
   framework.register_screen("runner", &runner);

   framework.run_loop();
   return;
}

void Runner::game_event_func(AllegroFlare::GameEvent* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[Runner::game_event_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::game_event_func: error: guard \"ev\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Runner::game_event_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Runner::game_event_func: error: guard \"event_emitter\" not met");
   }
   // NOTE: This is an older way to handle this signal flow, specifically for submitting the user input text. For
   // now, for this hackathon, it should work fine.
   if (ev->is_type(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_EVENT_TO_EMIT_ON_PRESSING_OK_KEY))
   {
      // Extract the user's input string
      std::string text_input_value = user_text_input_screen.get_result_string_value();

      // Assign the user input string into the "primary_gameplay_screen" for usage
      primary_gameplay_screen.set_last_user_text_input_value(text_input_value);

      // Activate the primary gameplay screen
      // TODO: test this
      this->router.emit_route_event(
         AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
         nullptr,
         al_get_time()
      );
   }
   else if (ev->is_type("riddle_is_solved"))
   {
      // TODO: Figure out what to do here, probably load the next level, or, if there are no more levels show
      // game won screen
      bool this_was_the_last_level = true;
      if (this_was_the_last_level)
      {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   }

   return;
}

AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText* Runner::create_image_page(std::string text)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText *result =
      new AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText();
   result->set_bitmap_bin(bitmap_bin);
   result->set_font_bin(font_bin);
   result->set_text(text);
   result->set_font_size(-50);
   result->set_line_height_multiplier(1.25f);
   result->set_image_fade_in_duration_sec(0.0f);
   result->set_text_color(ALLEGRO_COLOR{0, 0, 0, 1});
   result->set_image_identifier("character-avatar-01.png");
   //"storyboard-1-01-1165x500.png");
   result->set_top_padding(650);
   result->set_left_padding(600);
   result->set_right_padding(600);
   return result;
}


} // namespace ArtGalleryOfCats


