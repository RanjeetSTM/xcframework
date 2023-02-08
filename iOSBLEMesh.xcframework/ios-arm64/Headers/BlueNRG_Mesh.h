/******************** (C) COPYRIGHT 2019 STMicroelectronics **********************
 * File Name          : BlueNRG_Mesh.h
 * Author             : Systems Lab - Noida
 * Date First Issued  : 2017.12.06 :  V1.07
 * Description        : Stack unification class to simplify interaction with
                        ST BLE Mesh library and avoid API leakage
 
 ********************************************************************************
 This file may contain STMicroelectronics proprietary & confidential information
 *********************************************************************************/
#pragma once
#include "inc/stmesh_defines.h"
#include "stack/stmesh_layer_interface.h"
#include "proxy_prov/stmesh_provisioning_protocol.h"
#include "proxy_prov/stmesh_proxy.h"
#include "models/stmesh_model_config_client.h"
#include "models/stmesh_model_vendor.h"
#include "models/stmesh_model_generic_client.h"
#include "models/stmesh_model_lighting_client.h"
#include "models/stmesh_model_health_client.h"
#include "models/stmesh_model_heartbeat_client.h"
#include "stack/stmesh_layer_heartbeat.h"
#include "common/stmesh_logger.h"
#include "models/stmesh_model_sensor_client.h"
#include "stmesh_process_beacon.h"
#include "models/ConcurrentQueue.h"

namespace STMesh
{
    class BlueNrgMesh
    {
        class Impl;
		Impl* pimpl;//Hidden Implementation
    public:
        BlueNrgMesh();
        ~BlueNrgMesh();
        
		void Init(ILayerInterfaceLower* bearerLayer,
			MeshConfiguration* config, IProvisionerCallbacks* provProgressClient,
			ILayerConfigModelCallbacks* configModelClient, ILayerGenericModelCallbacks* genericModelClient,
			ILayerVendorModelCallbacks* vendorModelClient, ILayerLightingModelCallbacks* lightingModelClient,
			ILayerHealthModelCallbacks* healthModelCallbacksHandler, ILayerHeartbeatModelCallbacks* heartbeatModelClient,
			IFeatureHeartbeatCallbacks* featureHeartbeatCallbacksHandler, ILayerSensorModelCallbacks* sensorModelCallbackHandler, MeshLibraryCallbacks* libraryCallBacks, ConcurrentQueueTimerCallbacks* callBackHandler, IntermediateLowerAccesslayer* concurrentAccessLayer, ILayerProxyCallbacks * proxyCallbackhandler);
        
        void Reset();
        void Tick(uint32_t timestamp);
        void ProccessDispatchQueue();
        //To be called every 100 ms
		ModelConfigClient* GetConfigModel();
		ModelGenericClient* GetGenericModel();
		ModelVendor* GetVendorModel();
		ModelLightingClient* GetLightingModel();
		ModelHealthClient* GetHealthModel();
		ModelHeartbeatClient* GetHeartbeatModel();
		FeatureHeartbeat* GetFeatureHeartbeatControlModel();
		ProvisioningProtocol* GetProvisioner();
		ModelSensorClient* getSensorModel();
		Proxy* GetProxy();
        BeaconProcessor* GetBeaconProcessor();
        //Service data without ID type field
		bool CheckNodeIdentity(uint16_t peerAddress, uint8_t* serviceData);
		bool CheckNetworkID(uint8_t* serviceData);
    };
}
