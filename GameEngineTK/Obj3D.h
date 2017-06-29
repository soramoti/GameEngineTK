//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　3Dオブジェクトクラス
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <windows.h>
#include <wrl/client.h>
#include <memory.h>
#include <Effects.h>
#include <CommonStates.h>
#include <Model.h>
#include <map>

#include "Camera.h"

class Obj3D
{
	// 静的メンバ
public:
	// 設定
	struct Defs
	{
		Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
		Camera* pCamera;

		Defs()
		{
			pDevice = nullptr;
			pDeviceContext = nullptr;
			pCamera = nullptr;
		}
	};
	// 静的メンバ関数
	// 静的初期化
	static void StaticInitialize(const Defs& def);
	// デバイスのsetter
	static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> pDevice) { m_d3dDevice = pDevice; }
	// デバイスコンテキストのsetter
	static void SetDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext) { m_d3dContext = pDeviceContext; }
	// カメラのsetter
	static void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_d3dContext; }
	// 減算描画設定をセット
	static void SetSubtractive();
private:
	// カメラ
	static Camera* m_pCamera;
	// 汎用ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	// コンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	// エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	// 読み込み済みモデルコンテナ
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelarray;
	
	static ID3D11BlendState* s_pBlendStateSubtract;
public:
	Obj3D();

	// モデルの読み込み
	void LoadModel(const wchar_t* fileName);

	void Update();
	void Render();

	// オブジェクトのライティングを無効にする
	void DisableLighting();

	// setter(スケーリング用、回転(オイラー角)用、回転(クォータニオン)用、平行移動用、親オブジェクト用)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation;  m_useQuate = false; }
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotationQ = rotation; m_useQuate = true; };
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation){ m_translation = translation; }
	void SetObjParent(Obj3D* objParent) { m_objParent = objParent; }
	// getter(スケーリング用、回転用、平行移動用、ワールド行列、親オブジェクト用)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	Obj3D* GetObjParent() { return m_objParent; }
private:
	// モデルデータへのポインタ
	const DirectX::Model* m_model;	
	// スケーリング
	DirectX::SimpleMath::Vector3 m_scale;
	// 回転(オイラー角)
	DirectX::SimpleMath::Vector3 m_rotation;
	// 回転角（クォータニオン）
	DirectX::SimpleMath::Quaternion m_rotationQ;
	// 平行移動
	DirectX::SimpleMath::Vector3 m_translation;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 親となる3Dオブジェクトクラスのポインタ
	Obj3D* m_objParent;

	// 回転をクォータにをンで持っているフラグ
	bool m_useQuate;
};