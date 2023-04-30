#pragma once
#include "../../Library/gameutil.h"
#include "Throwable.h"
#include "Tower.h"
#include <cmath>

namespace Btd {
	class DartMonkey : public  Tower{
	public:
		DartMonkey();
		void Shoot(Vector2 target) override;
        void PushThrowablePool();
		void Upgrade(int level) override;
	private:
		bool _isPenetrate;
	};

}