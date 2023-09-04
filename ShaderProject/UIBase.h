#pragma once
#include <DirectXMath.h>
#include <memory>
#include <map>
#include <string>
#include <Windows.h>

class UIObjBase
{
public:
	virtual ~UIObjBase() {}
	virtual void Draw() = 0;
	virtual void SetPos(DirectX::XMFLOAT2 oldpos, DirectX::XMFLOAT2 newpos) = 0;
};

template<class T>
struct UIStatus
{
	std::shared_ptr<T> m_Obj;
};

template<class T>
class UIObj : public UIObjBase
{
public:
	UIObj(std::shared_ptr<T> ptr)
	{
		m_pUI.m_Obj = ptr;
	}
	virtual ~UIObj() {}
	UIStatus<T> m_pUI;

	void Draw() override
	{
		m_pUI.m_Obj->Draw();
	}

	void SetPos(DirectX::XMFLOAT2 oldpos, DirectX::XMFLOAT2 newpos) override
	{
		DirectX::XMFLOAT2 pos = m_pUI.m_Obj->GetPos();
		DirectX::XMFLOAT2 dif = DirectX::XMFLOAT2(pos.x - oldpos.x, pos.y - oldpos.y);
		m_pUI.m_Obj->SetPos(DirectX::XMFLOAT2(newpos.x + dif.x, newpos.y + dif.y));
	}
};

class UIBase
{
private:
	using UI = std::map<std::string, std::shared_ptr<UIObjBase>>;

public:
	UIBase();
	~UIBase();
	void Update();
	void Draw();

	template<class T> T* CreateUI(const char* name)
	{
#ifdef _DEBUG
		// デバッグ中のみ、名称ダブりがないかチェック
		UI::iterator it = m_pUIList.find(name);
		if (it != m_pUIList.end()) {
			static char buf[256];
			sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
			MessageBox(NULL, buf, "Error", MB_OK);
			return nullptr;
		}
#endif // _DEBUG

		std::shared_ptr<T> ptr = std::make_shared<T>();
		m_pUIList.insert(std::pair<std::string, std::shared_ptr<UIObjBase>>(name, std::make_shared<UIObj<T>>(ptr)));
		return ptr.get();
	}
	template<class T> T* GetUI(const char* name)
	{
		// オブジェクトの探索
		UI::iterator it = m_pUIList.find(name);
		if (it == m_pUIList.end()) return nullptr;

		// 型変換
		std::shared_ptr<UIObj<T>> ptr = std::reinterpret_pointer_cast<UIObj<T>>(it->second);
		return ptr->m_pUI.m_Obj.get();
	}

	void SetPos(DirectX::XMFLOAT2 pos)
	{
		for (const auto& uiPair : m_pUIList)
		{
			uiPair.second->SetPos(m_Pos, pos);
		}
		m_Pos = pos;
	}
	void SetActive(bool flag) { m_Use = flag;
	}

protected:	
	bool m_Use;
	DirectX::XMFLOAT2 m_Pos;
	UI m_pUIList;
};

