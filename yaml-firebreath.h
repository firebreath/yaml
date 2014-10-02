/**********************************************************\
 Original Author: Richard Bateman
 
 Created:    Sep 29, 2014
 License:    Dual license model; choose one of two:
             New BSD License
             http://www.opensource.org/licenses/bsd-license.php
             - or -
             GNU Lesser General Public License, version 2.1
             http://www.gnu.org/licenses/lgpl-2.1.html
 
 Copyright 2014 GradeCam, Inc
 \**********************************************************/

#include <APITypes.h>

namespace YAML {
    class Emitter;
    class Node;
}

namespace FB {
    void emitVariantAsYamlFile(const FB::variant& val, const std::string& filename);
    void emitVariantAsYaml(YAML::Emitter& out, const FB::variant &val);
    FB::variant yamlNodeToVariant(const YAML::Node& node);
    FB::variant loadYamlFileToVariant(const std::string& filename);
}
