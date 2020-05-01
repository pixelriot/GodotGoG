extends Control
"""
sampe projext for GOG Galaxy - Godot - module.
"""
const CLIENT_ID = "MY_CLIENT_ID"
const CLIENT_SECRET = "MY_CLIENT_SECRET"
var SOME_ACHIEVEMENT = "MY_ACHIEVEMENT"

"""
connect the authentication signals/callbacks from GOG api.
"""
func _ready() -> void:
	set_process(false)
	GOG.connect("auth_success" , self, "onAuthSuccess")

"""
after initialization, GOG.process_data has to be called every frame to run the callbacks.
"""
func _process(delta: float) -> void:
	GOG.process_data()

"""
the GOG client is initialized with client id and secret and returns an error if anything goes wrong.
If everything is ok, sign_in can be called.
After the authentication callback the login status can be verified with signed_in and is_logged_on.
"""
func _on_Init_pressed() -> void:
	set_process(true)
	if GOG.init(CLIENT_ID, CLIENT_SECRET) == OK:
		GOG.sign_in()
		yield(GOG, "auth_success")
		print(" signed in: ", str(GOG.signed_in()))
		print(" logged on: ", str(GOG.is_logged_on()))


func _on_Test_pressed() -> void:
	print("--ACHIEVEMENTS--")
	printt(GOG.get_achievement_description(SOME_ACHIEVEMENT))
	printt(GOG.get_achievement_display_name(SOME_ACHIEVEMENT))
	
	print("--USER--")
	printt(GOG.get_galaxy_id())
	printt(GOG.get_persona_name())
	printt(GOG.get_persona_state())
	printt(GOG.get_user_time_played())


func onAuthSuccess():
	print("authentication successfull!")


func _on_RemoveAchievement_pressed() -> void:
	GOG.clear_achievement(SOME_ACHIEVEMENT)


func _on_SetAchievement_pressed() -> void:
	GOG.set_achievement(SOME_ACHIEVEMENT)
