
#include "ConfigManagerYaml.h"
#include "yaml-firebreath.h"
#include "logging.h"

ConfigManager* ConfigManagerYaml::get() {
    static ConfigManagerYaml inst;
    
    return &inst;
}

FB::VariantMap ConfigManagerYaml::loadConfigMap(const std::string& filePath) {
    FB::VariantMap loaded;
    FB::variant doc = FB::loadYamlFileToVariant(filePath);
    return doc.convert_cast<FB::VariantMap>();
}

void ConfigManagerYaml::saveConfigMap(const std::string& filePath, const FB::VariantMap& map) {
    FB::emitVariantAsYamlFile(map, filePath);
}

ConfigManagerYaml::ConfigManagerYaml() {
    initConfig();
}