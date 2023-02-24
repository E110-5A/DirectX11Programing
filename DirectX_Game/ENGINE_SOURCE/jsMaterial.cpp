#include "jsMaterial.h"

namespace js::graphics
{
	Material::Material()
		: Resource(eResourceType::Material)
	{
	}
	Material::~Material()
	{
	}
	HRESULT Material::Load(const std::wstring& strPath)
	{
		return E_NOTIMPL;
	}
	void Material::SetData(eGPUParam param, void* data)
	{
        switch (param)
        {
        case eGPUParam::Int:
            mCB.iData = *static_cast<int*>(data);
            break;
        case eGPUParam::Float:
            mCB.fData = *static_cast<float*>(data);
            break;
        case eGPUParam::Vector2:
            mCB.xy = *static_cast<Vector2*>(data);
            break;
        case eGPUParam::Vector3:
            mCB.xyz = *static_cast<Vector3*>(data);
            break;
        case eGPUParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case eGPUParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
        default:
            break;
        }
	}
	void Material::Bind()
	{
        ConstantBuffer* pConstantBuffer = renderer::constantBuffers[(UINT)eCBType::Material];
        pConstantBuffer->Bind(&mCB);
        pConstantBuffer->SetPipline(eShaderStage::VS);
        pConstantBuffer->SetPipline(eShaderStage::PS);

        mShader->Binds();
	}
}