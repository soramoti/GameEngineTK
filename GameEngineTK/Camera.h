//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　カメラを制御するクラス
//
//日付　2017/05/11
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:	// メンバ関数
	Camera(int width, int height);
	virtual ~Camera();
	// 更新処理
	void Update();

	// ビュー行列を取得
	DirectX::SimpleMath::Matrix GetVeiwMatrix();
	// 射影行列を取得
	DirectX::SimpleMath::Matrix GetProjMatrix();

	// 視点座標をセット
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);
	// 注視点/参照点をセット
	void SetRefPos(DirectX::SimpleMath::Vector3 refpos);
	// 上方向ベクトルをセット
	void SetUpVec(DirectX::SimpleMath::Vector3 upvec);
	//　垂直方向視野角をセット
	void SetFovY(float fovY);
	// アスペクト比をセット
	void SetAspect(float aspect);
	// 手前の表示限界をセット
	void SetNearClip(float nearclip);
	// 奥の表示限界をセット
	void SetFarClip(float farclip);

protected:	// メンバ変数
	DirectX::SimpleMath::Matrix m_view;		// ビュー行列
	DirectX::SimpleMath::Matrix m_proj;		// 射影行列
	
	DirectX::SimpleMath::Vector3 m_eyepos;	//視点座標(カメラの位置)
	DirectX::SimpleMath::Vector3 m_refpos;	//注視点/参照点(どこをみているか)
	DirectX::SimpleMath::Vector3 m_upvec;	//上方向ベクトル

	float m_fovY;		// 垂直方向視野角
	float m_aspect;		// 画面横幅と縦幅の比率(アスペクト比)
	float m_nearclip;	// 画面手前の表示限界
	float m_farclip;	// 画面奥の表示限界

};