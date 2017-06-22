#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
// 静的メンバ変数の実体====
Camera* Obj3D::m_pCamera;		
std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;
Microsoft::WRL::ComPtr<ID3D11Device> Obj3D::m_d3dDevice;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3D::m_d3dContext;
std::unique_ptr<DirectX::EffectFactory> Obj3D::m_factory;
std::map<std::wstring, std::unique_ptr<DirectX::Model>> Obj3D::m_modelarray;

void Obj3D::InitializeStatic(Camera * pCamera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_pCamera = pCamera;
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	//　ステートの設定
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	// エフェクトファクトリの設定
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_factory->SetDirectory(L"Resources");

}

Obj3D::Obj3D()
{
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_objParent = nullptr;

	// デフォルトではクォータニオンを使わない
	m_useQuate = false;
}

void Obj3D::LoadModel(const wchar_t * fileName)
{
	assert(m_factory);

	// 同じ名前のモデルを読み込み済みでなければひｔ
	if (m_modelarray.count(fileName) == 0)
	{
		// モデルを読み込み、コンテナに登録（キーはファイル名）
		m_modelarray[fileName] = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
	}
	m_model = m_modelarray[fileName].get();
}

void Obj3D::Update()
{
	// 行列を計算する処理=======
	// スケーリング行列
	Matrix scaling = Matrix::CreateScale(m_scale);
	Matrix rotation;
	if (m_useQuate)
	{
		rotation = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// オイラー角から回転行列を計算（Z→X→Y）
		Matrix rotaZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotaX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotaY = Matrix::CreateRotationY(m_rotation.y);
		rotation = rotaZ * rotaX * rotaY;
	}
	// 平行移動行列
	Matrix transrate = Matrix::CreateTranslation(m_translation);
	// ワールド行列を合成
	m_world = scaling * rotation * transrate;
	if (m_objParent)
	{
		m_world *= m_objParent->GetWorld();
	}
}

void Obj3D::Render()
{
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_pCamera->GetVeiw(), m_pCamera->GetProj());
	}
}

void Obj3D::DisableLighting()
{
	if (m_model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();
		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// 自己発光を最大値に
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// エフェクトに含む全ての平行光源分について処理する
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ライトを無効にする
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}
