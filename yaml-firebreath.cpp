/**********************************************************\
 Original Author: Richard Bateman
 
 Created:    Jun 28, 2011
 License:    Dual license model; choose one of two:
 New BSD License
 http://www.opensource.org/licenses/bsd-license.php
 - or -
 GNU Lesser General Public License, version 2.1
 http://www.gnu.org/licenses/lgpl-2.1.html
 
 Copyright 2011 Facebook, Inc
 \**********************************************************/

#include "yaml-firebreath.h"

#include "APITypes.h"
#include "variant.h"


#include "yaml-cpp/yaml.h"

namespace FB {
    
    void emitVariantAsYamlFile(const variant& val, const std::string& filename) {
        ofstream myfile;
        myfile.open(filename.c_str());
        if (outfile.fail()) {
            throw new std::runtime_error("Could not open config file");
        }
        YAML::Emitter emitter(myfile);
        emitVariantAsYaml(emitter, val);
        myfile.close();
    }
    
    void emitVariantAsYaml(YAML::Emitter& out, const variant &val);
    {
        if (val.is_of_type<std::string>()) {
            out << val.convert_cast<std::string>();
        } else if (val.is_of_type<VariantMap>()) {
            out << YAML::BeginMap;
            VariantMap map = val.cast<VariantMap>();
            for (VariantMap::iterator it = map.begin(); it != map.end(); ++it) {
                out << YAML::Key << it->first;
                out << YAML::Value;
                emitVariantAsYaml(out, it->second);
                out << YAML::EndMap;
            }
        } else if (val.is_of_type<VariantList>()) {
            out << YAML::BeginSeq;
            VariantList list = val.cast<VariantList>();
            for (VariantList::iterator it = list.begin(); it != list.end(); ++it) {
                emitVariantValue(out, *it);
            }
        } else if (val.is_of_type<int>()
                   || val.is_of_type<char>()
                   || val.is_of_type<short>()
                   || val.is_of_type<long>()) {
            out << val.convert_cast<long>();
        } else if (val.is_of_type<unsigned int>()
                   || val.is_of_type<unsigned short>()
                   || val.is_of_type<unsigned char>()
                   || val.is_of_type<unsigned long>()) {
            out << val.convert_cast<unsigned long>();
        } else if (val.is_of_type<double>() || val.is_of_type<float>()) {
            out << val.convert_cast<double>();
        } else if (val.is_of_type<bool>()) {
            out << val.convert_cast<bool>();
        } else {
            out << YAML::Null;
        }
    }
    
    variant loadYamlFileToVariant(const std::string& filename) {
        YAML::Node doc = YAML::LoadFile(filename);
        return yamlNodeToVariant(doc);
    }
    variant yamlNodeToVariant(const YAML::Node& node) {
        // recursive depth first
        YAML::CONTENT_TYPE type = node.GetType();
        std::string outStr;
        switch (type)
        {
            case YAML::CT_SCALAR:
                node >> outStr;
                return outStr;
            case YAML::CT_SEQUENCE:
                VariantList list;
                for (unsigned int i = 0; i < node.size(); i++) {
                    const YAML::Node & subnode = node[i];
                    list.push_back(yamlNodeToVariant(subnode));
                }
                return list;
            case YAML::CT_MAP:
                VariantMap map;
                for (YAML::Iterator i = node.begin(); i != node.end(); ++i) {
                    const YAML::Node & key   = i.first();
                    const YAML::Node & value = i.second();
                    key >> outStr;
                    map[key] = yamlNodeToVariant(value);
                }
                return map;
            case YAML::CT_NONE:
                return FBNull;
                break;
            default:
                return FBVoid;
        }
    }
    
};
