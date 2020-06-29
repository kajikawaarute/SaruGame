/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�V���h�E�}�b�v
Texture2D<float4> shadowMap : register(t2);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//���C�g�r���[�s��
	float4x4 mLightView;	//���C�g�r���[�s��
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O
};

struct SDirectionLight {
	float3 directionCb[4];
	float4 colorCb[4];
};

/*!
* @brief	���C�g�p�̒萔�o�b�t�@�B
*/
cbuffer LightCb : register(b1) {
	SDirectionLight directionLight;
	float3 eyePos;

}

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//���[���h���W�B
	float4 posInLVP		: TEXCOORD2;	//���C�g�r���[�v���W�F�N�V�����s��
};

/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
/// </summary>
struct PSInput_ShadowMap {
	float4 Position		: SV_POSITION; //���W
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//���[���h���W�B
};

/*!
 *@brief	�X�L���s����v�Z�B
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	psInput.worldPos = pos;

	if (isShadowReciever == 1) {
		psInput.posInLVP = mul(mLightView, pos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
	}

	if (isShadowReciever == 1) {
		psInput.posInLVP = mul(mLightView, pos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = In.Normal;
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	/*float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	float3 lig = 0.0f;

	float3 lig = max(0.0f, dot(In.Normal * -1.0f ,directionCb)) * colorCb;
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;*/

	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
		lig += max(0.0f, dot(In.Normal, directionLight.directionCb[i] * -1.0f)) * directionLight.colorCb[i];
	}
		//�A���x�h�J���[�����������Ă���B
		float4 albedo = albedoTexture.Sample(Sampler, In.TexCoord);
		//�@�@���˃x�N�g��R�����߂�B
		//float3 R = directionLight.directionCb[i] + 2 * dot(In.Normal, -directionLight.directionCb[i]) * In.Normal;

		//�A�@���_���烉�C�g�����Ă镨�̂ɐL�т�x�N�g��E�����߂�B
		//float3 E = normalize(In.worldPos - eyePos);

		// �@�ƇA�ŋ��܂����x�N�g���̓��ς��v�Z���āA�X�y�L�������˂̋��������߂�B
		//float specPower = max(0, dot(R, -E));

		//�B�X�y�L�������˂����C�g�ɉ��Z����B
		//lig += directionLight.color.xyz * pow(specPower * specPow);
		//lig += directionLight.colorCb[i].xyz * pow(specPower, specPow);

		if (isShadowReciever == 1) {
			//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾�B
			float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
			//�V���h�E�}�b�v�͈͓̔�������
			if (shadowMapUV.x < 1.0f && shadowMapUV.x > 0.0f && shadowMapUV.y < 1.0f && shadowMapUV.y > 0.0f)
			{
				//LVP��Ԃł̐[�x�l���v�Z�B
				float zInLVP = In.posInLVP.z / In.posInLVP.w;
				//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
				float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

				if (zInLVP > zInShadowMap + 0.01f) {
					//�e�������Ă���̂ŁA�����キ����B
					lig *= 0.5f;
				}
			}
		}

	//���C�g�̌��ƃA���x�h�J���[����Z���čŏI�J���[�Ƃ���B
	float3 final;
	final.xyz = albedo.xyz * lig;
	return float4(final.xyz, 1.0f);
}

/// <summary>
/// �X�L���Ȃ����f���̃V���h�E�}�b�v�p�̒��_�V�F�[�_�[
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// �X�L�����胂�f���̃V���h�E�}�b�v�p�̒��_�V�F�[�_�[
/// </summary>
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = In.Normal;
	return psInput;
}

/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}