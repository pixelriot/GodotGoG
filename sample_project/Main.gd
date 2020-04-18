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
	GOG.connect("authSuccess" , self, "onAuthSuccess")

"""
after initialization, GOG.ProcessData has to be called every frame to run the callbacks.
"""
func _process(delta: float) -> void:
	GOG.ProcessData()

"""
the GOG client is initialized with client id and secret and returns an error if anything goes wrong.
If everything is ok, SignIn can be called.
After the authentication callback the login status can be verified with SignedIn and IsLoggedOn.
"""
func _on_Init_pressed() -> void:
	set_process(true)
	if GOG.Init(CLIENT_ID, CLIENT_SECRET) == OK:
		GOG.SignIn()
		yield(GOG, "authSuccess")
		print(" signed in: ", str(GOG.SignedIn()))
		print(" logged on: ", str(GOG.IsLoggedOn()))


func _on_Test_pressed() -> void:
	print("--ACHIEVEMENTS--")
	printt(GOG.GetAchievementDescription(SOME_ACHIEVEMENT))
	printt(GOG.GetAchievementDisplayName(SOME_ACHIEVEMENT))
	
	print("--USER--")
	printt(GOG.GetGalaxyID())
	printt(GOG.GetPersonaName())
	printt(GOG.GetPersonaState())
	printt(GOG.GetUserTimePlayed())


func onAuthSuccess():
	print("authentication successfull!")


func _on_RemoveAchievement_pressed() -> void:
	GOG.ClearAchievement(SOME_ACHIEVEMENT)


func _on_SetAchievement_pressed() -> void:
	GOG.SetAchievement(SOME_ACHIEVEMENT)
