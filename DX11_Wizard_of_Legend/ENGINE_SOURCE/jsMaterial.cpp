#include "jsMaterial.h"

namespace js::graphics
{
    Material::Material()
        : Resource(eResourceType::Material)
        , mMode(eRenderingMode::Opaque)
    {

    }

    Material::~Material()
    {

    }

    HRESULT Material::Load(const std::wstring& path)
    {
        
        
        
        return E_NOTIMPL;
    }

    void Material::SetData(eGpuParam param, void* data)
    {
        switch (param)
        {
        case js::graphics::eGpuParam::Int:
            mCB.iData = *static_cast<int*>(data);
            break;
        case js::graphics::eGpuParam::Float:
            mCB.fData = *static_cast<float*>(data);
            break;
        case js::graphics::eGpuParam::Vector2:
            mCB.xy = *static_cast<Vector2*>(data);
            break;
        case js::graphics::eGpuParam::Vector3:
            mCB.xyz = *static_cast<Vector3*>(data);
            break;
        case js::graphics::eGpuParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case js::graphics::eGpuParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
        default:
            break;
        }

    }

    void Material::Bind()
    {
        for (size_t slot = 0; slot < (UINT)eTextureSlot::End; slot++)
        {
            if (nullptr == mTexture[(UINT)slot])
                continue;

            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::VS, 0);
            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::HS, 0);
            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::DS, 0);
            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::GS, 0);
            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::PS, 0);
            mTexture[(UINT)slot]->BindShaderResource(eShaderStage::CS, 0);
        }
        

        ConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
        pCB->SetData(&mCB);
        pCB->Bind(eShaderStage::VS);
        pCB->Bind(eShaderStage::GS);
        pCB->Bind(eShaderStage::PS);

        mShader->Binds();
    }

    void Material::Clear()
    {
        for (size_t slot = 0; slot < (UINT)eTextureSlot::End; slot++)
        {
            if (nullptr == mTexture[(UINT)slot])
                continue;

            mTexture[(UINT)slot]->Clear();
        }
    }
}