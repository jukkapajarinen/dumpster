package fi.jukkaboyar.colorpong;

public class Constants {

	public static final int MODE_SINGLE = 0;
	public static final int MODE_MULTI = 1;
	public static final int PLAYER_NONE = -1;
	public static final int PLAYER_1 = 0;
	public static final int PLAYER_2 = 1;
	public static final int START_BALLS = 5;
	public static final int DIFF_EASY = 0;
	public static final int DIFF_NORMAL = 1;
	public static final int DIFF_HARD = 2;
	public static final int ITEM_BIG_PADDLE = 0;
	public static final int ITEM_SMALL_PADDLE = 1;
	public static final int ITEM_FLASH = 2;
	public static final int ITEM_EXTRA_BALLS = 3;
	public static final int ITEM_SLOW_MO = 4;
	public static final int ITEM_FAST_MO = 5;
	public static final int ITEM_STICKY = 6;
	public static final int ITEM_WALL = 7;
	public static final int ITEM_TSUNAMI = 8;
	public static final int BALL_1 = 0;
	public static final int BALL_2 = 1;
	public static final int BALL_3 = 2;
	public static final int BALL_4 = 3;
	public static final int BALL_5 = 4;
	public static final int BALL_6 = 5;
	public static final int BALL_COUNT = 6;
	public static final int SPEED_SLOW = 1;
	public static final int SPEED_NORMAL = 5;
	public static final int SPEED_FAST = 9;
	public static final float START_HUE = 0.5f;
	
	public static final float WIDTH = 480;
	public static final float HEIGHT = 800;
	public static final float FG_STRIPE_HEIGHT = 3;
	public static final float PADDLE_WIDTH = 120;
	public static final float PADDLE_BIG_WIDTH = 240;
	public static final float PADDLE_SMALL_WIDTH = 60;
	public static final float PADDLE_HEIGHT = 25;
	public static final float WALL_WIDTH = 480;
	public static final float WALL_HEIGHT = 3;
	public static final float BALL_WIDTH = 21;
	public static final float BALL_HEIGHT = 21;
	public static final float ITEM_WIDTH = 26;
	public static final float ITEM_HEIGHT = 26;
	public static final float HUD_WIDTH = 231;
	public static final float HUD_HEIGHT = 21;
	public static final float HUD_B_WIDTH = 21;
	public static final float HUD_B_HEIGHT = 21;
	public static final float FG_MARGIN = 13;
	public static final float PADDLE_Y_MARGIN = 120;
	public static final float TEXT_Y_MARGIN = 280;
	public static final float HUD_Y_MARGIN = 40;
	public static final float HUD_TEXT_Y_MARGIN = 60;
	public static final float DIA_WIDTH = 250;
	public static final float DIA_HEIGHT = 100;
	
	public static final float MENU_WIDTH = 480;
	public static final float MENU_HEIGHT = 520;
	public static final float MENU_POS_X = 0;
	public static final float MENU_POS_Y = 140;
	public static final float MENU_PADDING = 5;
	public static final float MENU_TITLE_PADDING = 30;
	public static final float MENU_LOGO_WIDTH = 396;
	public static final float MENU_LOGO_HEIGHT = 37;
	public static final float MENU_BUTTON_WIDTH = 440;
	public static final float MENU_BUTTON_HEIGHT = 60;
	public static final float MENU_BUTTON_SMALL_WIDTH = 264;
	public static final float MENU_BUTTON_SMALL_HEIGHT = 60;
	public static final float MENU_BUTTON_TINY_WIDTH = 60;
	public static final float MENU_BUTTON_TINY_HEIGHT = 60;

	public static final int SCREEN_GAME = 1;
	public static final int SCREEN_MENU = 2;
	public static final int SCREEN_SETT = 3;
	public static final int SCREEN_HOW = 4;
	
	public static final String STR_ITEM_BIG_PADDLE = "BIG PADDLE";
	public static final String STR_ITEM_SMALL_PADDLE = "SMALL PADDLE";
	public static final String STR_ITEM_FLASH = "COLOR FLASH";
	public static final String STR_ITEM_EXTRA_BALLS = "EXTRA BALLS";
	public static final String STR_ITEM_SLOW_MO = "SLOW MOTION";
	public static final String STR_ITEM_FAST_MO = "FAST MOTION";
	public static final String STR_ITEM_STICKY = "STICKY PADDLE";
	public static final String STR_ITEM_WALL = "COLOR WALL";
	public static final String STR_ITEM_TSUNAMI = "TSUNAMI";
	
	public static final String STR_DIA_GO_TITLE = "Game Over";
	public static final String STR_DIA_GO_1P_WON = "Player 1 won";
	public static final String STR_DIA_GO_2P_WON = "Player 2 won";
	public static final String STR_DIA_GO_DRAW = "It's a draw";
	public static final String STR_DIA_GO_REMATCH = "Rematch";
	public static final String STR_DIA_GO_EXIT = "Exit";
	public static final String STR_DIA_E_TITLE = "Exit";
	public static final String STR_DIA_E_YES = "Yes";
	public static final String STR_DIA_E_NO = "No";
	public static final String STR_DIA_I_TITLE = "Choose items";
	public static final String STR_DIA_I_OK = "OK";
	public static final String STR_DIA_I_CANCEL = "Cancel";
	public static final String STR_DIA_SHARE_TITLE = "Share this app";
	public static final String STR_SHARE_CONTENT = "Check out this App - https://play.google.com/store/apps/details?id=fi.jukkaboyar.colorpong";

	public static final String STR_MAIN_TITLE = "Colorpong";
	public static final String STR_MAIN_SINGLE = "Singleplayer";
	public static final String STR_MAIN_MULTI = "Multiplayer";
	public static final String STR_MAIN_SETT = "Settings";
	public static final String STR_MAIN_EXIT = "Exit";
	
	public static final String STR_SETT_TITLE = "Settings";
	public static final String STR_SETT_START_BALLS = "Start balls";
	public static final String STR_SETT_DIFFICULTY = "Difficulty";
	public static final String STR_SETT_DIFF_EASY = "Easy";
	public static final String STR_SETT_DIFF_NORMAL = "Normal";
	public static final String STR_SETT_DIFF_HARD = "Hard";
	public static final String STR_SETT_ITEMS = "Items";
	public static final String STR_SETT_CHOOSE = "Choose...";
	public static final String STR_SETT_RESET = "Reset Settings";
	public static final String STR_SETT_REMOVE_ADS = "Remove ads";
	
	public static final String STR_HOW_TITLE = "How to play?";
	public static final String STR_HOW_OBJECTIVE = "Try to reduce opponents balls to zero while guarding your own";
	public static final String STR_HOW_EXAMPLE = "For example green ball is reduced from the Player 2 if it goes to Player 2s goal.";
	public static final String STR_HOW_ITEMS = "Try to catch these items during a game.";
	public static final String STR_HOW_CLOSURE = "That's all.";
}
