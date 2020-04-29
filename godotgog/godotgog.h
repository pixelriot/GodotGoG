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
	Error init(String CLIENT_ID, String CLIENT_SECRET);
	void process_data();
	void shutdown();

	//User
	uint64_t get_galaxy_id();
	void sign_in();
	void sign_out();
	bool signed_in();
	bool is_logged_out();

	//Stats & Achievements
	void clear_achievement(const String &achievement_id);
	String get_achievement_description(const String &achievement_id);
	String get_achievement_display_name(const String &achievement_id);
	uint32_t get_user_time_played();
	bool is_achievement_visible(const String &achievement_id);
	void set_achievement(const String &achievement_id);

	//Friends
	String get_persona_name();
	int get_persona_state();

private:
	//callbacks
	void on_auth_success() override;
	void on_auth_failure(galaxy::api::IAuthListener::FailureReason failureReason) override;
	void on_auth_lost() override;
};

#endif // GODOTGOG_H