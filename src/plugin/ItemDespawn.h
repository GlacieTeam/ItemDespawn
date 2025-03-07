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
    static ItemDespawn& getInstance();

    const endstone::PluginDescription& getDescription() const override;

    void onLoad() override;

private:
    PluginInfo mPluginInfo;
    int        mItemDespawnTime;
};

} // namespace glacie_team