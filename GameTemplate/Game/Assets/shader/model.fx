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
//�g�D�[�������_�[
Texture2D<float4> toonRender : register(t3);

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

/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
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
	float4 posInProj	: TEXCOORD3;	//�ˉe��Ԃł̍��W�B
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

/// <summary>
/// �g�D�[�������_�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
/// </summary>
struct PSInput_ToonRender {
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

	psInput.posInProj = pos;
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
	
	psInput.worldPos = pos;

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = In.Normal;

	psInput.posInProj = pos;
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
		lig += max(0.0f, dot(In.Normal, directionLight.directionCb[i] * -1.0f)) * directionLight.colorCb[i];
	}
		//�A���x�h�J���[�����������Ă���B
		float4 albedo = albedoTexture.Sample(Sampler, In.TexCoord);

		//�e�̐���
		if (isShadowReciever == 1) {
			//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾�B
			float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
			float2 shadowOffset = abs(shadowMapUV);
			shadowOffset = 1.0f - pow(shadowOffset, 5.0f);
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
			//�V���h�E�}�b�v�͈͓̔�������
			if (shadowMapUV.x < 1.0f && shadowMapUV.x > 0.0f && shadowMapUV.y < 1.0f && shadowMapUV.y > 0.0f)
			{
				//LVP��Ԃł̐[�x�l���v�Z�B
				float zInLVP = In.posInLVP.z / In.posInLVP.w;
				//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
				float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

				if (zInLVP > zInShadowMap + 0.001f) {
					//�e�������Ă���̂ŁA�����キ����B
					float t = lerp(1.0f, 0.5f, shadowOffset.x);
					t = max(t, lerp(1.0f, 0.5f, shadowOffset.y));
					lig *= t;
				}
			}
		}

		//�g�D�[���V�F�[�_�[
		//�X�N���[���̍����(0,0)�A�E����(1,1)�Ƃ�����W�n�ɕϊ�����B
		float2 screenPos = (In.posInProj.xy / In.posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
		float2 offset = float2(1.25f / 1280.0f, 1.25f / 720.0f);

		float depth_0 = toonRender.Sample(Sampler, screenPos).x;

		float2 offsetTbl[] = {
			float2(-offset.x, -offset.y),		//����
			float2(0.0f, 	   -offset.y),		//��
			float2(offset.x, -offset.y),		//�E��
			float2(offset.x,  0.0f),			//�E
			float2(-offset.x, 0.0f),			//��
			float2(-offset.x, +offset.y),		//����
			float2(0.0f, 	   +offset.y),		//��
			float2(offset.x,  +offset.y),		//�E��
		};
		for (int i = 0; i < 8; i++) {
			float2 screenPos2 = screenPos + offsetTbl[i];

			float depth_1 = toonRender.Sample(Sampler, screenPos2).x;
			if (abs(depth_1 - depth_0 > 0.0025f)) {
				//�G�b�W�̐F��Ԃ��B
				return 0.0f;
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

/// <summary>
/// �X�L���Ȃ����f���̃g�D�[�������_�[�p�̒��_�V�F�[�_�[
/// </summary>
PSInput_ToonRender VSMain_ToonRender(VSInputNmTxVcTangent In)
{
	PSInput_ToonRender psInput = (PSInput_ToonRender)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// �X�L�����胂�f���̃g�D�[�������_�[�p�̒��_�V�F�[�_�[
/// </summary>
PSInput_ToonRender VSMainSkin_ToonRender(VSInputNmTxWeights In)
{
	PSInput_ToonRender psInput = (PSInput_ToonRender)0;
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
/// �g�D�[�������_�[�p�̃s�N�Z���V�F�[�_�[
/// </summary>
float4 PSMain_ToonRender(PSInput_ToonRender In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return pow(In.Position.z, 5.0f);
}