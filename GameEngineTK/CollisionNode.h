//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　あたり判定ノード
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once

#include "Collision.h"
#include "Obj3D.h"

// あたり判定ノード
class CollisionNode
{
public:
	virtual void Initiarize() = 0;
	virtual void Updete() = 0;
	virtual void Render() = 0;
	// 親をセット
	void SetParent(Obj3D* parent);
	// 親からのオフセットをセット
	void SetTranslation(const DirectX::SimpleMath::Vector3& trans) { m_translation = trans; }

	// デバッグ表示のON/OFFを設定
	static void SetDebugVisible(bool flag) { m_DebugVisible = flag; }
	// デバッグ表示のON/OFFを取得
	static bool GetDebugVisible(void) { return m_DebugVisible; }
private:
	// デバッグ表示のON/OFFフラグ
	static bool m_DebugVisible;
protected:
	// デバック表示オブジェクト
	Obj3D m_obj;
	// 親からのオフセット
	DirectX::SimpleMath::Vector3 m_translation;
};


// あたり判定球ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	void Initiarize();
	void Updete();
	void Render();
	// ローカル半径をセット
	void SetLocalRadius(float radus) { m_localRadius = radus; }
protected:
	// ローカル半径
	float m_localRadius;

};

