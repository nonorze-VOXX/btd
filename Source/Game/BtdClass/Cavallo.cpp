#include "stdafx.h"
#include "Cavallo.h"
#include "TowerFactory.h"

#include <random>
namespace Btd {
	void Cavallo::Init(function<void()> 🍴🍌) {
		LoadBitmapByString({ 
			"Resources/Cavallo/Cavallo_01.bmp", 
			"Resources/Cavallo/Cavallo_02.bmp", 
			"Resources/Cavallo/Cavallo_03.bmp", 
			"Resources/Cavallo/Cavallo_04.bmp",
			"Resources/Cavallo/Cavallo_01_m.bmp",
			"Resources/Cavallo/Cavallo_02_m.bmp",
			"Resources/Cavallo/Cavallo_03_m.bmp",
			"Resources/Cavallo/Cavallo_04_m.bmp",
			}, RGB(1,11,111));
		_isMirror = false;
		_smoothMoving = { 0.0f, 0.0f };
		_lastThrowTime = clock();
		_lastFrameTime = clock();
		_coolDown = 3000;
		_frameIndex = 0;
		SetCenter(600, 600);
		SetDest({ _GetRandomFloat(), _GetRandomFloat() });
		_base🍌.Load();
		Eat🍌 = 🍴🍌;
	}
	float Cavallo::_GetRandomFloat(float lower, float upper) {
		static random_device rd;
		static mt19937 gen(rd());
		if (lower == 48.0 && upper == 763.0) {
			uniform_real_distribution<float> dis(0, 1000);
			return dis(gen);
		}
		uniform_real_distribution<float> dis(lower, upper);
		return dis(gen);
	}
	void Cavallo::Throw() {
		if (clock() - _lastThrowTime > _coolDown) {
			_lastThrowTime = clock();
			Banana 🍌 = _base🍌;
			🍌.SetCenter(static_cast<int>(GetCenter().X), static_cast<int>(GetCenter().Y));
			🍌.SetDest({ _GetRandomFloat(🍌.GetCollider().X, SIZE_X - 🍌.GetCollider().X), _GetRandomFloat(🍌.GetCollider().Y, SIZE_Y - 🍌.GetCollider().Y) });
			🍌.Init();
			_🍌s.push_back(🍌);
		}
	}
	void Cavallo::Move() {
		auto preX = GetCenter().X;
		if (IsCursorFocus() && (GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			SetCenter(GetCursorPosX(), GetCursorPosY());
		}
		else {
			Throw();
			// TRACE(_T("pos: %f %f\n"), GetCenter().X, GetCenter().Y);
			if (GetCenter().X <  GetCollider().X || GetCenter().X > SIZE_X - GetCollider().X) {
				_dest.X = -_dest.X;
			}
			if (GetCenter().Y <  GetCollider().Y || GetCenter().Y > SIZE_Y - GetCollider().Y) {
				_dest.Y = -_dest.Y;
			}
			if (_GetRandomFloat() < 10.0f) {
				SetDest({ _GetRandomFloat(), _GetRandomFloat() });
			}
			Vector2 vec = _dest;
			auto Length = sqrt(vec.X * vec.X + vec.Y * vec.Y);
			vec = { vec.X / Length * 🐼speed, vec.Y / Length * 🐼speed };
			int x = static_cast<int>(GetCenter().X + vec.X), y = static_cast<int>(GetCenter().Y + vec.Y);
			_smoothMoving.X += vec.X - static_cast<int>(vec.X);
			_smoothMoving.Y += vec.Y - static_cast<int>(vec.Y);
			if (fabsf(_smoothMoving.X) > 1.0f) {
				x += static_cast<int>(_smoothMoving.X);
				_smoothMoving.X -= static_cast<int>(_smoothMoving.X);
			}
			if (fabsf(_smoothMoving.Y) > 1.0f) {
				y += static_cast<int>(_smoothMoving.Y);
				_smoothMoving.Y -= static_cast<int>(_smoothMoving.Y);
			}
			SetCenter(x, y);
		}
		for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()); i++)
		{
			for (auto& 🍌 : _🍌s) {
				if (Vector2Distance(TowerFactory::TowerVector[i]->GetCenter(), 🍌.GetCenter()) <= TowerFactory::TowerVector[i]->GetRange()) {
					_actions.push_back(bind(&Tower::Yes🍌😄, TowerFactory::TowerVector[i], &🍌));
				}
			}
			
		}
		for (auto it = _🍌s.begin(); it != _🍌s.end(); ) {
			it->Move();
			if (it->GetActive()) {
				it++;
			}
			else {
				it = _🍌s.erase(it);
			}
		}
		_isMirror = (fabsf(preX - GetCenter().X) < 1.0f) ? _isMirror : (preX > GetCenter().X);
		// TRACE(_T("diff: %f\n"), preX - GetCenter().X);
	}
	void Cavallo::Draw() {
		if (clock() - _lastFrameTime > 🐼🎦delay) {
			_lastFrameTime = clock();
			_frameIndex++;
			if (_frameIndex > 3) {
				_frameIndex = 0;
			}
		}
		if (_isMirror) {
			SetFrameIndexOfBitmap(_frameIndex + 4);
		}
		else {
			SetFrameIndexOfBitmap(_frameIndex);
		}
		ShowBitmap();
		for (auto& 🍌 : _🍌s) {
			🍌.Draw();
		}
	}
	void Cavallo::SetDest(Vector2 dest) {
		_dest = dest;
	}
	void Cavallo::Banana::Load() {
		LoadBitmapByString({ "Resources/Cavallo/banana/Banana.bmp" }, RGB(214, 197, 216));
		SetCenter(60, 60);
		SetCollider({ 0,0 });
		SetTag("🍌");
	}

	void Cavallo::Banana::Init() {
		_gotCarry = false;
		_isFlying = true;
		_isActive = true;
		_lastMoveTime = clock();
	}
	void Cavallo::Banana::Move() {
		if (IsCursorFocus() && (GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			_isActive = false;
			return;
		}
		if (_isFlying) {
			_lastMoveTime = clock();
			Vector2 vec = { _dest.X - GetCenter().X, _dest.Y - GetCenter().Y};
			auto Length = sqrt(vec.X * vec.X + vec.Y * vec.Y);
			vec = { vec.X / Length * 🍌speed , vec.Y / Length * 🍌speed  };
			int x = static_cast<int>(GetCenter().X + vec.X), y = static_cast<int>(GetCenter().Y + vec.Y);
			SetCenter(x, y);
			if (Vector2Distance(GetCenter(), _dest) < 10.0f) {
				_isFlying = false;
			}
		}
		if (!_gotCarry)
			return;
		SetCenter(🐵X, 🐵Y);
	}
	void Cavallo::Banana::Draw() {
		ShowBitmap();
	}
	void Cavallo::Banana::SetDest(Vector2 dest) {
		_dest = dest;
	}
	void Cavallo::Banana::SetOwnerPos(int X, int Y) {
		🐵X = X;
		🐵Y = Y;
	}

}