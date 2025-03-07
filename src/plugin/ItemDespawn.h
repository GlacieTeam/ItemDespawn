#pragma once
#include "endstone/plugin/plugin.h"

namespace glacie_team {

class ItemDespawn : public endstone::Plugin {
public:
    struct PluginInfo : public endstone::detail::PluginDescriptionBuilder {
        std::string name;
        std::string version;
        PluginInfo();
    };

public:
    static ItemDespawn& getInstance() {
        static auto instance = new ItemDespawn();
        return *instance;
    }

    const endstone::PluginDescription& getDescription() const override {
        static auto description = mPluginInfo.build(mPluginInfo.name, mPluginInfo.version);
        return description;
    }

    void onLoad() override;

    int getItemDespawnTime();

private:
    PluginInfo mPluginInfo;
    int        mItemDespawnTime{6000};
};

} // namespace glacie_team

extern "C" [[maybe_unused]] ENDSTONE_EXPORT endstone::Plugin* init_endstone_plugin() {
    return &glacie_team::ItemDespawn::getInstance();
}