//#pragma once
//#include <stack>
//
//class stateManager
//{
//public:
//	stateManager();
//	~stateManager();
//
//	virtual void Init() = 0;
//	virtual void Cleanup() = 0;
//
//	virtual void Pause() = 0;
//	virtual void Resume() = 0;
//
//	virtual void HandleEvents() = 0;
//	virtual void Update() = 0;
//	virtual void Draw() = 0;
//
//	void ChangeState();
//
//	int stateSize() { return stateStack.size(); };
//
//private:
//	std::stack<int> stateStack;
//
//};
//
