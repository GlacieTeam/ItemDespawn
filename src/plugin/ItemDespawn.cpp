#include "ItemDespawn.h"
#include "glacie/memory/Hook.h"
#include <fstream>

namespace glacie_team {

ItemDespawn::PluginInfo::PluginInfo() {
    name        = "itemdespawn";
    version     = "1.0.0";
    prefix      = "ItemDespawn";
    description = "C++ Example Plugin";
    website     = "https://github.com/GlacieTeam/ItemDespawn";
    authors     = {"GlacieTeam"};
}

int ItemDespawn::getItemDespawnTime() { return mItemDespawnTime; }

void ItemDespawn::onLoad() {
    if (!std::filesystem::exists("./plugins/ItemDespawn/")) {
        std::filesystem::create_directories("./plugins/ItemDespawn/");
    }
    std::ifstream inputFile("./plugins/ItemDespawn/ItemDespawnTime.txt");
    if (inputFile) {
        std::string content((std::istreambuf_iterator<char>(inputFile)), {});
        inputFile.close();
        try {
            mItemDespawnTime = std::stoi(content);
        } catch (...) {
            getLogger().error("The configuration file is broken, resetting...");
        }
    } else {
        getLogger().warning("The configuration file does not exist, generating...");
    }
    std::ofstream outputFile("./plugins/ItemDespawn/ItemDespawnTime.txt");
    if (outputFile) {
        outputFile << std::to_string(mItemDespawnTime);
        outputFile.close();
    }
}

GLACIE_AUTO_INSTANCE_HOOK(
    ItemSpawnHook,
    "48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 B0 48 81 EC 50 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 "
    "48 89 45 40 49 8B F1",
    void*,
    void* region,
    void* itemStack,
    void* spawner,
    void* pos,
    int   throwTime
) {
    auto itemActor = origin(region, itemStack, spawner, pos, throwTime);
    // ItemActor::mLifeTime this+1108
    glacie::memory::dAccess<int>(itemActor, 1108) = ItemDespawn::getInstance().getItemDespawnTime();
    return itemActor;
}

} // namespace glacie_team