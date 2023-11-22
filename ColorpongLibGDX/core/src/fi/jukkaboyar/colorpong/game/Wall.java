package fi.jukkaboyar.colorpong.game;

import com.badlogic.gdx.graphics.g2d.Sprite;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Constants;

public class Wall extends Sprite{

	public Wall(int id, float x, float y) {
		setX(x);
		setY(y);
		setSize(Constants.WALL_WIDTH, Constants.WALL_HEIGHT);
		switch (id) {
		case Constants.PLAYER_1:
			setRegion(AssetLoader.wall1);
			break;
		case Constants.PLAYER_2:
			setRegion(AssetLoader.wall2);
			break;
		}
	}
	
}
