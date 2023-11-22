package fi.jukkaboyar.colorpong.game;

import com.badlogic.gdx.graphics.g2d.Sprite;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Constants;

public class Item extends Sprite{

	private int id;
	private float ydir;
	private boolean used;
	private int holder;
	private long duration;
	private String text;
	
	public Item(int id, float ydir, float x, float y) {
		this.id = id;
		this.ydir = ydir;
		used = false;
		holder = Constants.PLAYER_NONE;
		duration = -1;
		setX(x);
		setY(y);
		setSize(Constants.ITEM_WIDTH, Constants.ITEM_HEIGHT);
		switch (id) {
		case Constants.ITEM_BIG_PADDLE:
			setRegion(AssetLoader.item1);
			text = Constants.STR_ITEM_BIG_PADDLE;
			break;
		case Constants.ITEM_SMALL_PADDLE:
			setRegion(AssetLoader.item2);
			text = Constants.STR_ITEM_SMALL_PADDLE;
			break;
		case Constants.ITEM_FLASH:
			setRegion(AssetLoader.item3);
			text = Constants.STR_ITEM_FLASH;
			break;
		case Constants.ITEM_EXTRA_BALLS:
			setRegion(AssetLoader.item4);
			text = Constants.STR_ITEM_EXTRA_BALLS;
			break;
		case Constants.ITEM_SLOW_MO:
			setRegion(AssetLoader.item5);
			text = Constants.STR_ITEM_SLOW_MO;
			break;
		case Constants.ITEM_FAST_MO:
			setRegion(AssetLoader.item6);
			text = Constants.STR_ITEM_FAST_MO;
			break;
		case Constants.ITEM_STICKY:
			setRegion(AssetLoader.item7);
			text = Constants.STR_ITEM_STICKY;
			break;
		case Constants.ITEM_WALL:
			setRegion(AssetLoader.item8);
			text = Constants.STR_ITEM_WALL;
			break;
		case Constants.ITEM_TSUNAMI:
			setRegion(AssetLoader.item9);
			text = Constants.STR_ITEM_TSUNAMI;
			break;
		}
	}
	
	public int getId() {
		return id;
	}
	public float getYdir() {
		return ydir;
	}
	public void setYdir(float ydir) {
		this.ydir = ydir;
	}
	public boolean isUsed() {
		return used;
	}
	public void setUsed(boolean used) {
		this.used = used;
	}
	public int getHolder() {
		return holder;
	}
	public void setHolder(int holder) {
		this.holder = holder;
	}
	public long getDuration() {
		return duration;
	}
	public void setDuration(long duration) {
		this.duration = duration;
	}
	public String getText() {
		return text;
	}

	public void move(float speed) {
		if(!used){
			setY(getY()+ydir*speed);
		}
	}
	
}
