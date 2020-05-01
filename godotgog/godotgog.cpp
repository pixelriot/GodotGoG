#include "godotgog.h"
#include "sdk/Include/galaxy/GalaxyApi.h"
#include <iostream>

namespace galaxy {
	namespace api {
		bool IsFullyInitialized = false;
	}
} // namespace galaxy

GOG *GOG::singleton = NULL;

void GOG::_bind_methods() {
	//Initialization
	ClassDB::bind_method(D_METHOD("init", "CLIENT_ID", "CLIENT_SECRET"), &GOG::Init);
	ClassDB::bind_method(D_METHOD("process_data"), &GOG::ProcessData);
	ClassDB::bind_method(D_METHOD("shutdown"), &GOG::Shutdown);
	//User
	ClassDB::bind_method(D_METHOD("get_galaxy_id"), &GOG::GetGalaxyID);
	ClassDB::bind_method(D_METHOD("sign_in"), &GOG::SignIn);
	ClassDB::bind_method(D_METHOD("sign_out"), &GOG::SignOut);
	ClassDB::bind_method(D_METHOD("signed_in"), &GOG::SignedIn);
	ClassDB::bind_method(D_METHOD("is_logged_out"), &GOG::IsLoggedOn);
	//Stats & Achievements
	ClassDB::bind_method(D_METHOD("clear_achievement", "achievement_id"), &GOG::ClearAchievement);
	ClassDB::bind_method(D_METHOD("get_achievement_description", "achievement_id"), &GOG::GetAchievementDescription);
	ClassDB::bind_method(D_METHOD("get_achievement_display_name", "achievement_id"), &GOG::GetAchievementDisplayName);
	ClassDB::bind_method(D_METHOD("get_user_time_played"), &GOG::GetUserTimePlayed);
	ClassDB::bind_method(D_METHOD("is_achievement_visible", "achievement_id"), &GOG::IsAchievementVisible);
	ClassDB::bind_method(D_METHOD("set_achievement", "achievement_id"), &GOG::SetAchievement);
	//Friends
	ClassDB::bind_method(D_METHOD("get_persona_name"), &GOG::GetPersonaName);
	ClassDB::bind_method(D_METHOD("get_persona_state"), &GOG::GetPersonaState);
	//Signals
	ADD_SIGNAL(MethodInfo("auth_success"));
	ADD_SIGNAL(MethodInfo("auth_failure"));
	ADD_SIGNAL(MethodInfo("auth_lost"));
}

//Initialization
GOG::GOG() {
	singleton = this;
}

GOG *GOG::get_singleton() {
	return singleton;
}

GOG::~GOG() {
	galaxy::api::Shutdown();
	singleton = NULL;
}

Error GOG::init(String CLIENT_ID, String CLIENT_SECRET) {
	std::cout << "\nInitializing GoG Galaxy ...\n";
	galaxy::api::Init({ CLIENT_ID.utf8().get_data(), CLIENT_SECRET.utf8().get_data() });
	if (galaxy::api::GetError()) {
		std::cout << galaxy::api::GetError()->GetMsg();
		std::cout << "\n";
		galaxy::api::IsFullyInitialized = false;
		return Error::FAILED;
	} else {
		std::cout << "... Initialization successful\n";
		galaxy::api::IsFullyInitialized = true;
		return Error::OK;
	}
}

void GOG::process_data() {
	galaxy::api::ProcessData();
}

void GOG::shutdown() {
	galaxy::api::Shutdown();
}

//User
uint64_t GOG::get_galaxy_id() {
	galaxy::api::GalaxyID galaxyID = galaxy::api::User()->GetGalaxyID();
	return galaxyID.GetRealID();
}

void GOG::sign_in() {
	if (galaxy::api::IsFullyInitialized) {
		std::cout << "\nSigning in ...\n";
		galaxy::api::User()->SignInGalaxy(false, this);
		if (galaxy::api::GetError()) {
			std::cout << galaxy::api::GetError()->GetMsg();
			std::cout << "\n";
		}
		else {
			std::cout << "... Signing in successful\n";
		}
	} else {
		std::cout << "\n... not yet initialized\n";
	}
}

void GOG::sign_out() {
	if (galaxy::api::IsFullyInitialized)
		galaxy::api::User()->SignOut();
}

bool GOG::signed_in() {
	if (galaxy::api::IsFullyInitialized)
		return galaxy::api::User()->SignedIn();
	else
		return false;
}

bool GOG::is_logged_out() {
	if (galaxy::api::IsFullyInitialized)
		return galaxy::api::User()->IsLoggedOn();
	else
		return false;
}

//Stats & Achievements
void GOG::clear_achievement(const String &achievement_id) {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	galaxy::api::Stats()->ClearAchievement(achievement_id.utf8().get_data());
	galaxy::api::Stats()->StoreStatsAndAchievements();
}

String GOG::get_achievement_description(const String &achievement_id) {
	return galaxy::api::Stats()->GetAchievementDescription(achievement_id.utf8().get_data());
}

String GOG::get_achievement_display_name(const String &achievement_id) {
	return galaxy::api::Stats()->GetAchievementDisplayName(achievement_id.utf8().get_data());
}

uint32_t GOG::get_user_time_played() {
	return galaxy::api::Stats()->GetUserTimePlayed();
}

bool GOG::is_achievement_visible(const String &achievement_id) {
	return galaxy::api::Stats()->IsAchievementVisible(achievement_id.utf8().get_data());
}

void GOG::set_achievement(const String &achievement_id) {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	galaxy::api::Stats()->SetAchievement(achievement_id.utf8().get_data());
	galaxy::api::Stats()->StoreStatsAndAchievements();
	if (galaxy::api::GetError())
		std::cout << galaxy::api::GetError()->GetMsg();
}

//Friends
String GOG::get_persona_name() {
	return galaxy::api::Friends()->GetPersonaName();
}

int GOG::get_persona_state() {
	//Enum
	//PERSONA_STATE_OFFLINE User is not currently logged on.
	//PERSONA_STATE_ONLINE 	User is logged on.
	return galaxy::api::Friends()->GetPersonaState();
}

//Signals
void GOG::on_auth_success() {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	emit_signal("auth_success");
}

void GOG::on_auth_failure(galaxy::api::IAuthListener::FailureReason) {
	emit_signal("auth_failure");
}

void GOG::on_auth_lost() {
	emit_signal("auth_lost");
}
