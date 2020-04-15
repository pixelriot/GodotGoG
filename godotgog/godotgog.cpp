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
	ClassDB::bind_method(D_METHOD("Init", "CLIENT_ID", "CLIENT_SECRET"), &GOG::Init);
	ClassDB::bind_method(D_METHOD("ProcessData"), &GOG::ProcessData);
	ClassDB::bind_method(D_METHOD("Shutdown"), &GOG::Shutdown);
	//User
	ClassDB::bind_method(D_METHOD("GetGalaxyID"), &GOG::GetGalaxyID);
	ClassDB::bind_method(D_METHOD("SignIn"), &GOG::SignIn);
	ClassDB::bind_method(D_METHOD("SignOut"), &GOG::SignOut);
	ClassDB::bind_method(D_METHOD("SignedIn"), &GOG::SignedIn);
	ClassDB::bind_method(D_METHOD("IsLoggedOn"), &GOG::IsLoggedOn);
	//Stats & Achievements
	ClassDB::bind_method(D_METHOD("ClearAchievement", "achievement_id"), &GOG::ClearAchievement);
	ClassDB::bind_method(D_METHOD("GetAchievementDescription", "achievement_id"), &GOG::GetAchievementDescription);
	ClassDB::bind_method(D_METHOD("GetAchievementDisplayName", "achievement_id"), &GOG::GetAchievementDisplayName);
	ClassDB::bind_method(D_METHOD("GetUserTimePlayed"), &GOG::GetUserTimePlayed);
	ClassDB::bind_method(D_METHOD("IsAchievementVisible", "achievement_id"), &GOG::IsAchievementVisible);
	ClassDB::bind_method(D_METHOD("SetAchievement", "achievement_id"), &GOG::SetAchievement);
	//Friends
	ClassDB::bind_method(D_METHOD("GetPersonaName"), &GOG::GetPersonaName);
	ClassDB::bind_method(D_METHOD("GetPersonaState"), &GOG::GetPersonaState);
	//Signals
	ADD_SIGNAL(MethodInfo("authSuccess"));
	ADD_SIGNAL(MethodInfo("authFailure"));
	ADD_SIGNAL(MethodInfo("authLost"));
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

Error GOG::Init(String CLIENT_ID, String CLIENT_SECRET) {
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

void GOG::ProcessData() {
	galaxy::api::ProcessData();
}

void GOG::Shutdown() {
	galaxy::api::Shutdown();
}

//User
uint64_t GOG::GetGalaxyID() {
	galaxy::api::GalaxyID galaxyID = galaxy::api::User()->GetGalaxyID();
	return galaxyID.GetRealID();
}

void GOG::SignIn() {
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

void GOG::SignOut() {
	if (galaxy::api::IsFullyInitialized)
		galaxy::api::User()->SignOut();
}

bool GOG::SignedIn() {
	if (galaxy::api::IsFullyInitialized)
		return galaxy::api::User()->SignedIn();
	else
		return false;
}

bool GOG::IsLoggedOn() {
	if (galaxy::api::IsFullyInitialized)
		return galaxy::api::User()->IsLoggedOn();
	else
		return false;
}

//Stats & Achievements
void GOG::ClearAchievement(const String &achievement_id) {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	galaxy::api::Stats()->ClearAchievement(achievement_id.utf8().get_data());
	galaxy::api::Stats()->StoreStatsAndAchievements();
}

String GOG::GetAchievementDescription(const String &achievement_id) {
	return galaxy::api::Stats()->GetAchievementDescription(achievement_id.utf8().get_data());
}

String GOG::GetAchievementDisplayName(const String &achievement_id) {
	return galaxy::api::Stats()->GetAchievementDisplayName(achievement_id.utf8().get_data());
}

uint32_t GOG::GetUserTimePlayed() {
	return galaxy::api::Stats()->GetUserTimePlayed();
}

bool GOG::IsAchievementVisible(const String &achievement_id) {
	return galaxy::api::Stats()->IsAchievementVisible(achievement_id.utf8().get_data());
}

void GOG::SetAchievement(const String &achievement_id) {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	galaxy::api::Stats()->SetAchievement(achievement_id.utf8().get_data());
	galaxy::api::Stats()->StoreStatsAndAchievements();
	if (galaxy::api::GetError())
		std::cout << galaxy::api::GetError()->GetMsg();
}

//Friends
String GOG::GetPersonaName() {
	return galaxy::api::Friends()->GetPersonaName();
}

int GOG::GetPersonaState() {
	//Enum
	//PERSONA_STATE_OFFLINE User is not currently logged on.
	//PERSONA_STATE_ONLINE 	User is logged on.
	return galaxy::api::Friends()->GetPersonaState();
}

//Signals
void GOG::OnAuthSuccess() {
	galaxy::api::Stats()->RequestUserStatsAndAchievements(galaxy::api::User()->GetGalaxyID());
	emit_signal("authSuccess");
}

void GOG::OnAuthFailure(galaxy::api::IAuthListener::FailureReason) {
	emit_signal("authFailure");
}

void GOG::OnAuthLost() {
	emit_signal("authLost");
}
