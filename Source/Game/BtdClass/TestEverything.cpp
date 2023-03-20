#include "stdafx.h"
#include "TestEverything.h"

#include "TowerFactory.h"

namespace Btd
{
    void TestEverything::UnitInit()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.LoadEmptyBitmap(100, 100);
            _throwable.SetTopLeft(0, 0);
            _throwable.SetSpeed(2);
            _throwable.SetMoveDirection(1, 1);
        // break;
        case DartMonkeyShoot:
            _dartMonkey.LoadBitmapByString({"Resources/towers/monkey/tower_monkey_1.bmp"},RGB(0, 0, 0));
            _dartMonkey.SetTopLeft(100, 100);
            _dartMonkey.SetShootDeltaTime(1);
        case BalloonMoveTest:
            _balloon.LoadEmptyBitmap(30, 30);
            _balloon.SetTopLeft(10, 10);
            _balloon.SetActive(false);
            _balloon.SetNowRouteTarget(0);
            _balloon.Setspeed(3);
        case BalloonVectorMoveTest:
            BALLOONS.push_back(_balloon);
        case NailMachineShoot:
            _nailMachine.SetThrowablePath({"resources/towers/nail/nail.bmp"});
            _nailMachine.LoadBitmapByString({"Resources/towers/nail/tower_nail.bmp"},RGB(0, 0, 0));
            _nailMachine.SetTopLeft(500, 500);
            _nailMachine.SetShootDeltaTime(1);
        case BallonPop:
            _cannon.LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
            _cannon.SetTopLeft(500, 500);
            _cannon.SetShootDeltaTime(3);
            TowerFactory::MakeTower(bomb);
            TowerFactory::TowerVector[0]->SetIsMove(false);
            TowerFactory::TowerVector[0]->SetTopLeft(200, 200);
            TowerFactory::TowerVector[0]->SetShootDeltaTime(3);
            TowerFactory::TowerVector[0]->SetActive(true);
            _balloonFactory.MakeBallon(yelllow);
            BallonFactory::BallonVector[0].SetTopLeft(120, 120);
            _balloonFactory.MakeBallon(blue);
            BallonFactory::BallonVector[1].SetTopLeft(600, 400);
            _balloonFactory.MakeBallon(black);
            BallonFactory::BallonVector[2].SetTopLeft(400, 400);
            break;
            
        default:
            break;
        }
    }

    void TestEverything::UnitTest()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.Move();
            if (_throwable.GetTop() > 10)
            {
                _unitTestState = BalloonMoveTest;
            }
            break;
        case DartMonkeyShoot:
            _dartMonkey.Update();
        //shoot test
            break;
        case BalloonMoveTest:
            _balloon.Move({{500, 500}});
            if (_balloon.GetTop() > 30)
            {
                _unitTestState = BalloonVectorMoveTest;
            }
            break;
        case BalloonVectorMoveTest:
            BALLOONS[0].Move({{500, 500}});
            if (BALLOONS[0].GetLeft() > 100)
            {
                _unitTestState = BalloonFactoryTest;
            }
            break;
        case BalloonFactoryTest:
            if (_balloonFactory.BallonVector.size() < 10)
            {
                _balloonFactory.MakeBallon(red);
            }
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Move({{500, 500}});
            }
            if (_balloonFactory.BallonVector.size() > 5)
            {
                _unitTestState = NailMachineShoot;
            }

            break;
        case TowerFocus:
            _dartMonkey.Update();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Update();
            }
            break;
        case NailMachineShoot:
            _nailMachine.Update();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Update();
            }
            BallonFactory::handlePopBalloon();
            break;
        case BallonPop:
            for (int i=0; i<(int)TowerFactory::TowerVector.size(); i++)
            {
                TowerFactory::TowerVector[i]->Update();
            }
            BallonFactory::handlePopBalloon();
            break;
        default: ;
        }
    }

    void TestEverything::UnitShow()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.ShowBitmap();
            break;
        case DartMonkeyShoot:
            break;
        case BalloonMoveTest:
            _balloon.ShowBitmap();
            break;
        case BalloonVectorMoveTest:
            BALLOONS[0].ShowBitmap();
            break;
        case BalloonFactoryTest:
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }

            break;
        case TowerFocus:
            _dartMonkey.TowerShow();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }
            break;
        case NailMachineShoot:
            _nailMachine.TowerShow();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }
            break;
        case BallonPop:
            for (Tower *tower : TowerFactory::TowerVector)
            {
                tower->TowerShow();
            }
            _cannon.TowerShow();
            for (auto b : BallonFactory::BallonVector)
            {
                b.ShowBitmap();
            }
            break;
        default:
            break;
        }
    }
}
