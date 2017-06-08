#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Player::Player()
{
	m_angle = 0.0f;

	m_cycle = 0.0f;
	m_wingPcycle = 0.0f;
	m_wingNcycle = 0.0f;

	m_keyboard = nullptr;

}


Player::~Player()
{

}

void Player::Initiarize()
{
	// プレイヤーパーツのロード
	m_obj.resize(NUM);
	m_obj[FRFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[FLFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BRFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BLFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BODY].LoadModel(L"Resources/body.cmo");
	m_obj[HEAD].LoadModel(L"Resources/head.cmo");
	m_obj[RWING].LoadModel(L"Resources/wing.cmo");
	m_obj[LWING].LoadModel(L"Resources/wing.cmo");
	m_obj[TAIL].LoadModel(L"Resources/tail.cmo");
	m_obj[STAR].LoadModel(L"Resources/star.cmo");

	// 親子関係をつける
	m_obj[FLFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[FRFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[BLFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[BRFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[HEAD].SetObjParent(&m_obj[BODY]);
	m_obj[STAR].SetObjParent(&m_obj[BODY]);
	m_obj[RWING].SetObjParent(&m_obj[BODY]);
	m_obj[LWING].SetObjParent(&m_obj[BODY]);
	m_obj[TAIL].SetObjParent(&m_obj[BODY]);

	// 本体の位置の調整
	m_obj[BODY].SetScale(Vector3(1.0f, 1.0f, 0.7f));
	m_obj[BODY].SetRotation(Vector3(0.3f, 0.0f, 0.0f));
	m_obj[BODY].SetTransration(Vector3(0.0f, 5.0f, 0.0f));

	// 親からのずれ===
	// 左前足
	m_obj[FLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[FLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_obj[FLFOOT].SetTransration(Vector3(0.15f, -0.2f, -0.4f));
	// 右前足
	m_obj[FRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[FRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_obj[FRFOOT].SetTransration(Vector3(-0.15f, -0.2f, -0.4f));
	// 左後ろ足
	m_obj[BLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[BLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_obj[BLFOOT].SetTransration(Vector3(0.15f, -0.3f, 0.4f));
	// 右後ろ足
	m_obj[BRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[BRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_obj[BRFOOT].SetTransration(Vector3(-0.15f, -0.3f, 0.4f));
	// 頭
	m_obj[HEAD].SetScale(Vector3(0.8f, 0.8f, 1.1f));
	m_obj[HEAD].SetRotation(Vector3(-0.2f, 0.0f, 0.0f));
	m_obj[HEAD].SetTransration(Vector3(0.0f, 0.5f, -0.5f));
	// しっぽ
	m_obj[TAIL].SetTransration(Vector3(0.0f, 0.0f, 0.6f));
	// 右はね
	m_obj[RWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_obj[RWING].SetRotation(Vector3(-0.5f, 0.3f, 0.0f));
	m_obj[RWING].SetTransration(Vector3(0.3f, 0.3f, 0.0f));
	// 左はね
	m_obj[LWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_obj[LWING].SetRotation(Vector3(-0.5f, -0.3f, 0.0f));
	m_obj[LWING].SetTransration(Vector3(-0.3f, 0.3f, 0.0f));
	// 星
	m_obj[STAR].SetScale(Vector3(2.0f, 2.0f, 2.0f));
	m_obj[STAR].SetTransration(Vector3(0.0f, 1.0f, 0.0f));

	// 回転角の情報を保存
	m_tailRota = m_obj[TAIL].GetRotation();
	m_RwingRota = m_obj[RWING].GetRotation();
	m_LwingRota = m_obj[LWING].GetRotation();

}

void Player::Update()
{
	m_angle += 0.05f;
	m_cycle += 0.05;
	m_wingPcycle += 0.1;
	m_wingNcycle -= 0.1;

	// キーボードの状態を取得する
	Keyboard::State key = m_keyboard->GetState();

	if (key.A)
	{
		float angleX = m_obj[BODY].GetRotation().x;
		float angleY = m_obj[BODY].GetRotation().y;
		m_obj[BODY].SetRotation(Vector3(angleX, angleY + 0.03f, 0.0f));
	}
	if (key.D)
	{
		float angleX = m_obj[BODY].GetRotation().x;
		float angleY = m_obj[BODY].GetRotation().y;
		m_obj[BODY].SetRotation(Vector3(angleX, angleY - 0.03f, 0.0f));
	}

	if (key.W)
	{
		// 移動ベクトル
		Vector3 move(0.0f, 0.0f, -0.1f);
		// 今の角度に合わせて移動ベクトルを回転させる===========
		// ワールド行列を移動ベクトルにかける
		//move = Vector3::TransformNormal(move, m_worldRobbot);
		// 回転行列を移動ベクトルにかける
		float angle = m_obj[BODY].GetRotation().y;
		Matrix rotation = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotation);
		// 自機の座標を移動
		m_pos = m_obj[BODY].GetTransration();
		m_pos += move;
		m_obj[BODY].SetTransration(m_pos);
	}
	if (key.S)
	{
		// 移動ベクトル
		Vector3 move(0, 0, 0.1f);
		// 回転行列
		float angle = m_obj[BODY].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotmat);
		// 自機の座標を移動
		m_pos = m_obj[BODY].GetTransration();
		m_pos += move;
		m_obj[BODY].SetTransration(m_pos);
	}

	// 動物の上下の動き
	m_pos.y = (0.5f * sinf(m_cycle)) + 1.0f;
	m_obj[BODY].SetTransration(m_pos);

	// しっぽの回転
	m_tailRota.z += 0.5f;
	m_obj[TAIL].SetRotation(m_tailRota);

	// 羽根の動き
	m_RwingRota.y = (0.3f * sinf(m_wingPcycle)) + 0.4;
	m_obj[RWING].SetRotation(m_RwingRota);

	m_LwingRota.y = (0.3f * sinf(m_wingNcycle)) - 0.4;
	m_obj[LWING].SetRotation(m_LwingRota);

	// 星の動き
	m_obj[STAR].SetRotation(Vector3(0.0f, m_angle, m_cycle));
	m_obj[STAR].SetTransration(Vector3(cosf(m_cycle), (sinf(m_cycle + m_cycle)) + 0.5f, 0.0f));


	for (std::vector<Obj3D>::iterator it = m_obj.begin();
		it != m_obj.end();
		it++)
	{
		it->Obj3D::Update();
	}

}

void Player::Rebder()
{
	// プレイヤの描画
	for (std::vector<Obj3D>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		it->Obj3D::Render();
	}

}

void Player::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}