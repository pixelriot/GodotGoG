#include "register_types.h"
#include "core/class_db.h"
#include "core/engine.h"
#include "godotgog.h"

static GOG* GOGPtr = NULL;

void register_godotgog_types() {
    ClassDB::register_class<GOG>();
    GOGPtr = memnew(GOG);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GOG",GOG::get_singleton()));
}

void unregister_godotgog_types() {
    memdelete(GOGPtr);
}