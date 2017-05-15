//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　
//
//日付　
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//==================================
//*関数の概要　コンストラクタ
//*引数[int,int] 画面の縦、横のサイズ
//*戻り値
//==================================
Camera::Camera(int width,int height)
{
	// メンバ変数の初期化
	m_eyepos = Vector3(0.0f, 0.0f, 5.0f);	//視点座標(カメラの位置)
	m_refpos = Vector3(0.0f, 0.0f, 0.0f);	//注視点/参照点(どこをみているか)
	m_upvec = Vector3(0.0f, 1.0f, 0.0f);	//上方向ベクトル
	m_upvec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);		// 垂直方向視野角
	m_aspect = float(width) / height;		// 画面横幅と縦幅の比率(アスペクト比)
	m_nearclip = 0.1f;						// 画面手前の表示限界
	m_farclip = 1000.0f;					// 画面奥の表示限界

	// ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos,m_refpos,m_upvec);
	// 射影行列を生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//==================================
//*関数の概要　デストラクタ
//*引数[]
//*戻り値
//==================================
Camera::~Camera()
{

}

//==================================
//*関数の概要　更新処理
//*引数[]
//*戻り値
//==================================
void Camera::Update()
{
	// ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// 射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//==================================
//*関数の概要　ビュー行列を取得
//*引数[]
//*戻り値　ビュー行列
//==================================
const DirectX::SimpleMath::Matrix& Camera::GetVeiw()
{
	return m_view;
}

//==================================
//*関数の概要　射影行列を取得
//*引数[]
//*戻り値　射影行列
//==================================
const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

//==================================
//*関数の概要　視点座標をセット
//*引数[Vector3]　視点座標
//*戻り値
//==================================
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}

//==================================
//*関数の概要　注視点をセット
//*引数[Vector3]　注視点座標
//*戻り値
//==================================
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

//==================================
//*関数の概要　上方向ベクトルをセット
//*引数[Vector3]　上方向ベクトル
//*戻り値
//==================================
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

//==================================
//*関数の概要　垂直方向視野角をセット
//*引数[float]　視野角
//*戻り値
//==================================
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

//==================================
//*関数の概要　画面比率(アスペクト比)をセット
//*引数[float]　比率
//*戻り値
//==================================
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//==================================
//*関数の概要　手前の表示限界をセット
//*引数[float]　表示限界値
//*戻り値
//==================================
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

//==================================
//*関数の概要　奥の表示限界をセット
//*引数[float]　表示限界値
//*戻り値
//==================================
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
