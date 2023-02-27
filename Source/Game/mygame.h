/*
 * mygame.h: ¥»ÀÉ®×Àx¹CÀ¸¥»¨­ªºclassªºinterface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


namespace game_framework
{
    /////////////////////////////////////////////////////////////////////////////
    // Constants
    /////////////////////////////////////////////////////////////////////////////

    enum AUDIO_ID
    {
        // ©w¸q¦UºØ­µ®Äªº½s¸¹
        AUDIO_DING,
        // 0
        AUDIO_LAKE,
        // 1
        AUDIO_NTUT // 2
    };

    /////////////////////////////////////////////////////////////////////////////
    // ³o­Óclass¬°¹CÀ¸ªº¹CÀ¸¶}ÀYµe­±ª«¥ó
    // ¨C­ÓMember functionªºImplementation³£­n§ËÀ´
    /////////////////////////////////////////////////////////////////////////////

    class CGameStateInit : public CGameState
    {
    public:
        CGameStateInit(CGame* g);
        void OnInit() override; // ¹CÀ¸ªºªì­È¤Î¹Ï§Î³]©w
        void OnBeginState() override; // ³]©w¨C¦¸­«ª±©Ò»ÝªºÅÜ¼Æ
        void OnKeyUp(UINT, UINT, UINT) override; // ³B²zÁä½LUpªº°Ê§@
        void OnLButtonDown(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@
    protected:
        void OnShow() override; // Åã¥Ü³o­Óª¬ºAªº¹CÀ¸µe­±
    private:
        void load_background();
        void draw_text();
        CMovingBitmap background;
    };

    /////////////////////////////////////////////////////////////////////////////
    // ³o­Óclass¬°¹CÀ¸ªº¹CÀ¸°õ¦æª«¥ó¡A¥D­nªº¹CÀ¸µ{¦¡³£¦b³o¸Ì
    // ¨C­ÓMember functionªºImplementation³£­n§ËÀ´
    /////////////////////////////////////////////////////////////////////////////

    class CGameStateRun : public CGameState
    {
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun() override;
        void OnBeginState() override; // ³]©w¨C¦¸­«ª±©Ò»ÝªºÅÜ¼Æ
        void OnInit() override; // ¹CÀ¸ªºªì­È¤Î¹Ï§Î³]©w
        void OnKeyDown(UINT, UINT, UINT) override;
        void OnKeyUp(UINT, UINT, UINT) override;
        void OnLButtonDown(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@
        void OnLButtonUp(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@
        void OnMouseMove(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@ 
        void OnRButtonDown(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@
        void OnRButtonUp(UINT nFlags, CPoint point) override; // ³B²z·Æ¹«ªº°Ê§@
    protected:
        void OnMove() override; // ²¾°Ê¹CÀ¸¤¸¯À
        void OnShow() override; // Åã¥Ü³o­Óª¬ºAªº¹CÀ¸µe­±
    private:
        int phase = 1;
        int sub_phase = 1;
        CMovingBitmap background;
        CMovingBitmap character;
        CMovingBitmap chest_and_key;
        CMovingBitmap bee;
        CMovingBitmap ball;
        CMovingBitmap door[3];
        void show_image_by_phase();
        void show_text_by_phase();
        bool validate_phase_1();
        bool validate_phase_2();
        bool validate_phase_3();
        bool validate_phase_4();
        bool validate_phase_5();
        bool validate_phase_6();
    };

    /////////////////////////////////////////////////////////////////////////////
    // ³o­Óclass¬°¹CÀ¸ªºµ²§ôª¬ºA(Game Over)
    // ¨C­ÓMember functionªºImplementation³£­n§ËÀ´
    /////////////////////////////////////////////////////////////////////////////

    class CGameStateOver : public CGameState
    {
    public:
        CGameStateOver(CGame* g);
        void OnBeginState() override; // ³]©w¨C¦¸­«ª±©Ò»ÝªºÅÜ¼Æ
        void OnInit() override;
        void OnKeyDown(UINT, UINT, UINT) override;

    protected:
        void OnMove() override; // ²¾°Ê¹CÀ¸¤¸¯À
        void OnShow() override; // Åã¥Ü³o­Óª¬ºAªº¹CÀ¸µe­±
    private:
        CMovingBitmap background;
        void load_background();
    };
}
