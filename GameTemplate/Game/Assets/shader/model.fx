/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウマップ
Texture2D<float4> shadowMap : register(t2);
//トゥーンレンダー
Texture2D<float4> toonRender : register(t3);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//ライトビュー行列
	float4x4 mLightView;	//ライトビュー行列
	float4x4 mLightProj;	//ライトプロジェクション行列
	int isShadowReciever;	//シャドウレシーバーフラグ
};

/// <summary>
/// ディレクションライト
/// </summary>
struct SDirectionLight {
	float3 directionCb[4];
	float4 colorCb[4];
};

/*!
* @brief	ライト用の定数バッファ。
*/
cbuffer LightCb : register(b1) {
	SDirectionLight directionLight;
	float3 eyePos;
}

/// <summary>
/// シャドウマップ用の定数バッファ
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション行列
	float4 posInProj	: TEXCOORD3;	//射影空間での座標。
};

/// <summary>
/// シャドウマップ用のピクセルシェーダーへの入力構造体
/// </summary>
struct PSInput_ShadowMap {
	float4 Position		: SV_POSITION; //座標
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
};

/// <summary>
/// トゥーンレンダ用のピクセルシェーダーへの入力構造体
/// </summary>
struct PSInput_ToonRender {
	float4 Position		: SV_POSITION; //座標
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
};

/*!
 *@brief	スキン行列を計算。
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
 * @brief	スキンなしモデル用の頂点シェーダー。
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
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
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
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		//ディレクションライトの拡散反射光を計算する。
		lig += max(0.0f, dot(In.Normal, directionLight.directionCb[i] * -1.0f)) * directionLight.colorCb[i];
	}
		//アルベドカラーを引っ張ってくる。
		float4 albedo = albedoTexture.Sample(Sampler, In.TexCoord);

		//影の生成
		if (isShadowReciever == 1) {
			//LVP空間から見た時の最も手前の深度値をシャドウマップから取得。
			float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
			float2 shadowOffset = abs(shadowMapUV);
			shadowOffset = 1.0f - pow(shadowOffset, 5.0f);
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
			//シャドウマップの範囲内か判定
			if (shadowMapUV.x < 1.0f && shadowMapUV.x > 0.0f && shadowMapUV.y < 1.0f && shadowMapUV.y > 0.0f)
			{
				//LVP空間での深度値を計算。
				float zInLVP = In.posInLVP.z / In.posInLVP.w;
				//シャドウマップに書き込まれている深度値を取得。
				float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

				if (zInLVP > zInShadowMap + 0.001f) {
					//影が落ちているので、光を弱くする。
					float t = lerp(1.0f, 0.5f, shadowOffset.x);
					t = max(t, lerp(1.0f, 0.5f, shadowOffset.y));
					lig *= t;
				}
			}
		}

		//トゥーンシェーダー
		//スクリーンの左上を(0,0)、右下を(1,1)とする座標系に変換する。
		float2 screenPos = (In.posInProj.xy / In.posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
		float2 offset = float2(1.25f / 1280.0f, 1.25f / 720.0f);

		float depth_0 = toonRender.Sample(Sampler, screenPos).x;

		float2 offsetTbl[] = {
			float2(-offset.x, -offset.y),		//左上
			float2(0.0f, 	   -offset.y),		//上
			float2(offset.x, -offset.y),		//右上
			float2(offset.x,  0.0f),			//右
			float2(-offset.x, 0.0f),			//左
			float2(-offset.x, +offset.y),		//左下
			float2(0.0f, 	   +offset.y),		//下
			float2(offset.x,  +offset.y),		//右下
		};
		for (int i = 0; i < 8; i++) {
			float2 screenPos2 = screenPos + offsetTbl[i];

			float depth_1 = toonRender.Sample(Sampler, screenPos2).x;
			if (abs(depth_1 - depth_0 > 0.0025f)) {
				//エッジの色を返す。
				return 0.0f;
			}
		}

	//ライトの光とアルベドカラーを乗算して最終カラーとする。
	float3 final;
	final.xyz = albedo.xyz * lig;
	return float4(final.xyz, 1.0f);
}

/// <summary>
/// スキンなしモデルのシャドウマップ用の頂点シェーダー
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
/// スキンありモデルのシャドウマップ用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
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
/// シャドウマップ用のピクセルシェーダー
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}

/// <summary>
/// スキンなしモデルのトゥーンレンダー用の頂点シェーダー
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
/// スキンありモデルのトゥーンレンダー用の頂点シェーダー
/// </summary>
PSInput_ToonRender VSMainSkin_ToonRender(VSInputNmTxWeights In)
{
	PSInput_ToonRender psInput = (PSInput_ToonRender)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
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
/// トゥーンレンダー用のピクセルシェーダー
/// </summary>
float4 PSMain_ToonRender(PSInput_ToonRender In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return pow(In.Position.z, 5.0f);
}