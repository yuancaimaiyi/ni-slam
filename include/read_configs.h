#ifndef READ_CONFIGS_H_
#define READ_CONFIGS_H_

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "utils.h"

struct DatasetConfig{
  std::string dataroot;
  std::string camera_file;
};

struct CFConfig{
  int width;
  int height;
  float sigma;
  float lambda;
  int rotation_divisor;
};

struct MapConfig{
  double grid_scale;
};

struct LoopClosureConfig{
  double position_response_thr;
  double angle_response_thr;
};

struct Configs{
  DatasetConfig dataset_config;
  CFConfig cf_config;
  MapConfig map_config;
  LoopClosureConfig loop_closure_config;

  Configs(const std::string& config_file){
    if(!FileExists(config_file)){
      std::cout << "config file: " << config_file << " doesn't exist" << std::endl;
      return;
    }

    YAML::Node file_node = YAML::LoadFile(config_file);
    YAML::Node dataset_node = file_node["dataset"];
    dataset_config.dataroot = dataset_node["dataroot"].as<std::string>();
    dataset_config.camera_file = dataset_node["camera_config"].as<std::string>();

    YAML::Node cf_node = file_node["correlation_flow"];
    cf_config.width = cf_node["width"].as<int>();
    cf_config.height = cf_node["height"].as<int>();
    cf_config.sigma = cf_node["sigma"].as<float>();
    cf_config.lambda = cf_node["lambda"].as<float>();
    cf_config.rotation_divisor = cf_node["rotation_divisor"].as<int>();

    YAML::Node map_node = file_node["map"];
    map_config.grid_scale = map_node["grid_scale"].as<double>();

    YAML::Node loop_closure_node = file_node["loop_closure"];
    loop_closure_config.position_response_thr = 
        loop_closure_node["position_response_thr"].as<double>();
    loop_closure_config.angle_response_thr = 
        loop_closure_node["angle_response_thr"].as<double>();

  }
};



#endif  // READ_CONFIGS_H_