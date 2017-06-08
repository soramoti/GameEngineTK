//
// Game.h
//

#pragma once

#include "StepTimer.h"

#include <Keyboard.h>

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>

#include <Model.h>

#include "DebugCamera.h"
#include "FollowCamera.h"

#include "Obj3D.h"
#include "Player.h"
#include "Enemy.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	//�@�L�[�{�[�h�̕ϐ�
	std::unique_ptr <DirectX::Keyboard> m_keyboard;

	// �e�N�X�`���֘A�̕ϐ�
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	//std::unique_ptr<DirectX::BasicEffect> m_effect;
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//std::unique_ptr<DirectX::CommonStates> m_states;

	// �s����W
	//DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	// �f�o�b�N�J����
	//std::unique_ptr<DebugCamera> m_debugCamera;

	// ���f���֘A�̕ϐ�
	//std::unique_ptr<DirectX::EffectFactory> m_factory;

    Obj3D m_objSkyDome;
	Obj3D m_objGround;
	//Obj3D m_objTeapot[20];

	std::unique_ptr<Player> m_player;	// �v���C��
	std::vector<std::unique_ptr<Enemy>> m_enemy;

	float m_angle;
	int x[20], z[20];

	std::unique_ptr<FollowCamera> m_camera;
};