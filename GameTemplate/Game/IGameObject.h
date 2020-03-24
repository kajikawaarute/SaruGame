#pragma once
class IGameObject
{
public:
	/// <summary>
	/// 
	/// </summary>
	virtual bool Start()
	{
		return true;
	};

	/// <summary>
	/// 更新関数
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画関数
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 削除リクエストを行う
	/// </summary>
	void RequestDelete()
	{
		isRequestDelete = true;
	}

	/// <summary>
	/// 削除リクエストを受けているか調べる
	/// </summary>
	/// trueが帰ってきたら受けている
	bool IsRequestDelete()
	{
		return isRequestDelete;
	}

private:
	bool isRequestDelete = false;	//削除リクエスト
};

