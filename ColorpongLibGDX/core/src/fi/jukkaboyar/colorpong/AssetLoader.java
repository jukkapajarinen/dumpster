package fi.jukkaboyar.colorpong;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class AssetLoader {
	
	public static TextureAtlas atlas;
	public static TextureRegion logo, share, questionMark, musicOff, musicOn, dashLine, wall1, wall2;
	public static TextureRegion paddle1, paddle2, item1, item2, item3, item4, item5, item6, item7, item8, item9;
	public static TextureRegion ball1, ball2, ball3, ball4, ball5, ball6, hud1, hud2;
	public static BitmapFont fontSmall, fontMedium, fontLarge;
	public static Music bgMusic;
	public static Sound goalSound, bounceSound, itemSound, stickySound;
	
	public static void load(){
		atlas = new TextureAtlas(Gdx.files.internal("packs/game.pack"));
		logo = atlas.findRegion("logo");
		share = atlas.findRegion("share");
		questionMark = atlas.findRegion("questionMark");
		musicOff = atlas.findRegion("musicOff");
		musicOn = atlas.findRegion("musicOn");
		dashLine = atlas.findRegion("dashLine");
		wall1 = atlas.findRegion("wall1");
		wall2 = atlas.findRegion("wall2");
		paddle1 = atlas.findRegion("paddle1");
		paddle2 = atlas.findRegion("paddle2");
		item1 = atlas.findRegion("item1");
		item2 = atlas.findRegion("item2");
		item3 = atlas.findRegion("item3");
		item4 = atlas.findRegion("item4");
		item5 = atlas.findRegion("item5");
		item6 = atlas.findRegion("item6");
		item7 = atlas.findRegion("item7");
		item8 = atlas.findRegion("item8");
		item9 = atlas.findRegion("item9");
		ball1 = atlas.findRegion("ball1");
		ball2 = atlas.findRegion("ball2");
		ball3 = atlas.findRegion("ball3");
		ball4 = atlas.findRegion("ball4");
		ball5 = atlas.findRegion("ball5");
		ball6 = atlas.findRegion("ball6");
		hud1 = atlas.findRegion("hud1");
		hud2 = atlas.findRegion("hud2");
		fontSmall = new BitmapFont(Gdx.files.internal("fonts/8bitwonder-small.fnt"));
		fontMedium = new BitmapFont(Gdx.files.internal("fonts/8bitwonder-medium.fnt"));
		fontLarge = new BitmapFont(Gdx.files.internal("fonts/8bitwonder-large.fnt"));
		bgMusic = Gdx.audio.newMusic(Gdx.files.internal("sounds/bg.mp3"));
		goalSound = Gdx.audio.newSound(Gdx.files.internal("sounds/goal.mp3"));
		bounceSound = Gdx.audio.newSound(Gdx.files.internal("sounds/bounce.mp3"));
		itemSound = Gdx.audio.newSound(Gdx.files.internal("sounds/item.mp3"));
		stickySound = Gdx.audio.newSound(Gdx.files.internal("sounds/sticky.mp3"));
	}
	
	public static void playSound(Sound sound) {
		sound.play();
	}
	
	public static void musicOn(Music music){
		if(!music.isPlaying()){
			music.setLooping(true);
			music.play();
		}
	}
	
	public static void musicOff(Music music){
		if(music.isPlaying()){
			music.stop();
		}		
	}
	
	public static void dispose() {
		fontSmall.dispose();
		fontMedium.dispose();
		fontLarge.dispose();
		bgMusic.dispose();
		goalSound.dispose();
		bounceSound.dispose();
		itemSound.dispose();
		stickySound.dispose();
		atlas.dispose();
	}
	
}
