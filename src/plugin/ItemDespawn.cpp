#include "ItemDespawn.h"
#include "glacie/memory/Hook.h"

namespace glacie_team {

ItemDespawn& ItemDespawn::getInstance() {
    static auto instance = new ItemDespawn();
    return *instance;
}

const endstone::PluginDescription& ItemDespawn::getDescription() const {
    static auto description = mPluginInfo.build(mPluginInfo.name, mPluginInfo.version);
    return description;
}

ItemDespawn::PluginInfo::PluginInfo() {
    name        = "itemdespawn";
    version     = "1.0.0";
    prefix      = "ItemDespawn";
    description = "C++ Example Plugin";
    website     = "https://github.com/GlacieTeam/ItemDespawn";
    authors     = {"GlacieTeam"};
}

void ItemDespawn::onLoad() {
    // Code for loading the mod goes here.
}

} // namespace glacie_team

extern "C" [[maybe_unused]] ENDSTONE_EXPORT endstone::Plugin* init_endstone_plugin() {
    return &glacie_team::ItemDespawn::getInstance();
}

GLACIE_AUTO_INSTANCE_HOOK(
    ItemSpawnHook,
    "48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 B0 48 81 EC 50 01 00 00 48 8B 05 0D 7D 26 02 48 33 C4 "
    "48 89 45 40 49 8B F1 4C 89 44",
    void*,
    void* region,
    void* itemStack,
    void* spawner,
    void* pos,
    int   throwTime
) {
    auto itemActor = origin(region, itemStack, spawner, pos, throwTime);
    // ItemActor::mLifeTime this+1108
    glacie::memory::dAccess<int>(itemActor, 1108) = 200;
    return itemActor;
}