#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
// �ÓI�����o�ϐ��̎���====
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
	//�@�X�e�[�g�̐ݒ�
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	// �G�t�F�N�g�t�@�N�g���̐ݒ�
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_factory->SetDirectory(L"Resources");

}

Obj3D::Obj3D()
{
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_objParent = nullptr;

	// �f�t�H���g�ł̓N�H�[�^�j�I�����g��Ȃ�
	m_useQuate = false;
}

void Obj3D::LoadModel(const wchar_t * fileName)
{
	assert(m_factory);

	// �������O�̃��f����ǂݍ��ݍς݂łȂ���΂Ђ�
	if (m_modelarray.count(fileName) == 0)
	{
		// ���f����ǂݍ��݁A�R���e�i�ɓo�^�i�L�[�̓t�@�C�����j
		m_modelarray[fileName] = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
	}
	m_model = m_modelarray[fileName].get();
}

void Obj3D::Update()
{
	// �s����v�Z���鏈��=======
	// �X�P�[�����O�s��
	Matrix scaling = Matrix::CreateScale(m_scale);
	Matrix rotation;
	if (m_useQuate)
	{
		rotation = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// �I�C���[�p�����]�s����v�Z�iZ��X��Y�j
		Matrix rotaZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotaX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotaY = Matrix::CreateRotationY(m_rotation.y);
		rotation = rotaZ * rotaX * rotaY;
	}
	// ���s�ړ��s��
	Matrix transrate = Matrix::CreateTranslation(m_translation);
	// ���[���h�s�������
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
		// ���f�����̑S���b�V������
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();
		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// ���b�V�����̑S���b�V���p�[�c����
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// ���b�V���p�[�c�ɃZ�b�g���ꂽ�G�t�F�N�g��BasicEffect�Ƃ��Ď擾
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// ���Ȕ������ő�l��
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// �G�t�F�N�g�Ɋ܂ޑS�Ă̕��s�������ɂ��ď�������
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ���C�g�𖳌��ɂ���
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}
