package fi.jukkaboyar.colorpong.game;

import com.badlogic.gdx.graphics.g2d.Sprite;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Constants;

public class Paddle extends Sprite{
	
	public Paddle(int id, float x, float y) {
		setX(x);
		setY(y);
		setSize(Constants.PADDLE_WIDTH, Constants.PADDLE_HEIGHT);
		switch (id) {
		case Constants.PLAYER_1:
			setRegion(AssetLoader.paddle1);
			break;
		case Constants.PLAYER_2:
			setRegion(AssetLoader.paddle2);
			break;
		}
	}
	
	public void move(float x) {
		setX(x);
	}
	
}
