#ifndef ConfigManagerYaml_h__
#define ConfigManagerYaml_h__

#include "ConfigManager.h"

class ConfigManagerYaml : public ConfigManager
{
public:
    static ConfigManager* get();
    
protected:
    ConfigManagerYaml();
    virtual ~ConfigManagerYaml() {};
    
    void saveConfigMap(const std::string& filePath, const FB::VariantMap& map);
    FB::VariantMap loadConfigMap(const std::string& filePath);
};

#endif // ConfigManagerYaml_h__
