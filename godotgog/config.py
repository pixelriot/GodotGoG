def can_build(env, platform):
    return platform=="windows" or platform=="osx" or platform=="x11"


def configure(env):
    env.Append( CPPPATH=["#modules/godotgog/sdk/Include/galaxy/"] )
    env.Append( LIBPATH=["#modules/godotgog/sdk/Libraries"] )

    if env["platform"] == "windows":
        if env["bits"]=="32":
            env.Append(LINKFLAGS=["Galaxy.lib"])
        else:
            env.Append(LINKFLAGS=["Galaxy64.lib"])
    elif env["platform"] == "osx":
        env.Append(LIBS=["libGalaxy.dylib"])
    elif env["platform"] == "x11":
        if env["bits"]=="32":
            env.Append(LINKFLAGS=["libGalaxy.so"])
        else:
            env.Append(LINKFLAGS=["libGalaxy64.so"])
