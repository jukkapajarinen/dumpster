package fi.jukkaboyar.colorpong;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.TimeUtils;

import java.util.Random;

import fi.jukkaboyar.colorpong.gui.HomeScreen;

public class Colorpong extends Game {

	public SpriteBatch sb;
	public OrthographicCamera cam;
	public Random rand;
	public Preferences prefs;
	public float hue;
	public float[] bgColor;
	public float[] fgColor;
	public long lastHueTime;
	
	@Override
	public void create () {
        AssetLoader.load();
        sb = new SpriteBatch();
        cam = new OrthographicCamera();
        cam.setToOrtho(false, Constants.WIDTH, Constants.HEIGHT);
        rand = new Random();
        prefs = Gdx.app.getPreferences("fi.jukkaboyar.colorpong.prefs");
        Gdx.input.setCatchBackKey(true);
        lastHueTime = TimeUtils.nanoTime();
        hue = Constants.START_HUE;
        bgColor = Helpers.HSBtoRGB(hue, 0.7f, 0.65f);
        fgColor = Helpers.HSBtoRGB(hue+0.05f, 0.7f, 1f);
        if(prefs.getBoolean("musicOn", true))
            AssetLoader.musicOn(AssetLoader.bgMusic);
        this.setScreen(new HomeScreen(this));
	}

	@Override
	public void render () {
        if(TimeUtils.nanoTime() - lastHueTime > 10000000l){
            lastHueTime = TimeUtils.nanoTime();
            hue += 0.0005f;
            bgColor = Helpers.HSBtoRGB(hue, 0.7f, 0.65f);
            fgColor = Helpers.HSBtoRGB(hue+0.05f, 0.7f, 1f);
        }
        Gdx.gl.glClearColor(bgColor[0], bgColor[1], bgColor[2], 1f);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        cam.update();
        sb.setProjectionMatrix(cam.combined);
        sb.begin();
        sb.end();
        super.render();
	}
	
	@Override
	public void dispose () {
		sb.dispose();
        AssetLoader.dispose();
	}
}
