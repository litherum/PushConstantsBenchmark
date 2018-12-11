﻿#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace RootConstantPerformance
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~Sample3DSceneRenderer();
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void Update(DX::StepTimer const& timer);
		bool Render();
		void SaveState();

		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

	private:
		void LoadState();
		void Rotate(float radians);

	private:
		// Constant buffers must be 256-byte aligned.
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;
		static const UINT c_totalFrames = 10 * 60;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignatureRootConstants;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignatureBufferConstants;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineStateRootConstants;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineStateBufferConstants;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		Microsoft::WRL::ComPtr<ID3D12QueryHeap>				m_queryHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_queryReadbackBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_fakeConstantBuffer;
		ModelViewProjectionConstantBuffer					m_constantBufferData;
		UINT8*												m_mappedConstantBuffer;
		UINT8*												m_mappedFakeConstantBuffer;
		UINT												m_cbvDescriptorSize;
		D3D12_RECT											m_scissorRect;
		std::vector<byte>									m_vertexShader;
		std::vector<byte>									m_pixelShader;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_radiansPerSecond;
		float	m_angle;
		bool	m_tracking;
		UINT	m_renderCount{ 0 };
		float	m_color[4] = {};
		UINT	m_drawCount{ 1000 };
		UINT	m_instanceCount{ 1 };
		LARGE_INTEGER cpuRootConstantTotal = { 0 };
		LARGE_INTEGER cpuBufferConstantTotal = { 0 };
	};
}

