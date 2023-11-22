package fi.jukkaboyar.colorpong.game;

import com.badlogic.gdx.graphics.g2d.Sprite;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Constants;

public class Ball extends Sprite{

	private int id;
	private float xdir, ydir;
	private boolean sticky;
	private Paddle stickyPaddle;
	private float stickyPos;

	public Ball(int id, float xdir, float ydir, float x, float y) {
		this.id = id;
		this.xdir = xdir;
		this.ydir = ydir;
		sticky = false;
		stickyPaddle = null;
		stickyPos = 0;
		setX(x);
		setY(y);
		setSize(Constants.BALL_WIDTH, Constants.BALL_HEIGHT);
		switch (id) {
		case Constants.BALL_1:
			setRegion(AssetLoader.ball1);
			break;
		case Constants.BALL_2:
			setRegion(AssetLoader.ball2);
			break;
		case Constants.BALL_3:
			setRegion(AssetLoader.ball3);
			break;
		case Constants.BALL_4:
			setRegion(AssetLoader.ball4);
			break;
		case Constants.BALL_5:
			setRegion(AssetLoader.ball5);
			break;
		case Constants.BALL_6:
			setRegion(AssetLoader.ball6);
			break;
		}
	}
	
	public int getId() {
		return id;
	}
	public float getXdir() {
		return xdir;
	}
	public void setXdir(float xdir) {
		this.xdir = xdir;
	}
	public float getYdir() {
		return ydir;
	}
	public void setYdir(float ydir) {
		this.ydir = ydir;
	}
	public boolean isSticky() {
		return sticky;
	}
	public Paddle getStickyPaddle() {
		return stickyPaddle;
	}
	public float getStickyPos() {
		return stickyPos;
	}

	public void sticky(boolean sticky, Paddle stickyPaddle, float stickyPos) {
		this.sticky = sticky;
		this.stickyPaddle = stickyPaddle;
		this.stickyPos = stickyPos;
	}
	
	public void move(float speed) {
		if(!sticky){
			setX(getX()+xdir*speed);
			setY(getY()+ydir*speed);
		}
	}
	
}
