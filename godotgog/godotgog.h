#ifndef GODOTGOG_H
#define GODOTGOG_H

#include "core/reference.h"
#include "sdk/Include/galaxy/GalaxyApi.h"

class GOG : public Reference,
			public galaxy::api::IAuthListener {
	GDCLASS(GOG, Reference);

protected:
	static void _bind_methods();
	static GOG *singleton;

public:
	static GOG *get_singleton();
	GOG();
	~GOG();

	//Initialization
	Error Init(String CLIENT_ID, String CLIENT_SECRET);
	void ProcessData();
	void Shutdown();

	//User
	uint64_t GetGalaxyID();
	void SignIn();
	void SignOut();
	bool SignedIn();
	bool IsLoggedOn();

	//Stats & Achievements
	void ClearAchievement(const String &achievement_id);
	String GetAchievementDescription(const String &achievement_id);
	String GetAchievementDisplayName(const String &achievement_id);
	uint32_t GetUserTimePlayed();
	bool IsAchievementVisible(const String &achievement_id);
	void SetAchievement(const String &achievement_id);

	//Friends
	String GetPersonaName();
	int GetPersonaState();

private:
	//callbacks
	void OnAuthSuccess() override;
	void OnAuthFailure(galaxy::api::IAuthListener::FailureReason failureReason) override;
	void OnAuthLost() override;
};

#endif // GODOTGOG_H