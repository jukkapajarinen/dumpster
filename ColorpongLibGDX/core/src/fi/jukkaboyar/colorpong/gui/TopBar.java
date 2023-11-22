package fi.jukkaboyar.colorpong.gui;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.ui.Button.ButtonStyle;
import com.badlogic.gdx.scenes.scene2d.ui.ImageButton;
import com.badlogic.gdx.scenes.scene2d.ui.ImageButton.ImageButtonStyle;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.badlogic.gdx.utils.Align;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Colorpong;
import fi.jukkaboyar.colorpong.Constants;

public class TopBar extends Table{

    final Colorpong game;
    final int screen;

    Skin skin;
    ImageButtonStyle shareStyle;
    ImageButtonStyle howStyle;
    ImageButtonStyle muteStyle;
    ImageButton shareBtn;
    ImageButton howBtn;
    ImageButton muteBtn;

    public TopBar(final Colorpong game, final int screen) {
        this.game = game;
        this.screen = screen;

        skin = new Skin(Gdx.files.internal("packs/uiskin.json"), new TextureAtlas("packs/uiskin.pack"));
        this.setFillParent(true);
        this.pad(Constants.FG_MARGIN);
        this.align(Align.top+Align.left);
        shareStyle = new ImageButtonStyle(skin.get(ButtonStyle.class));
        shareStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.share));
        shareBtn = new ImageButton(shareStyle);
        howStyle = new ImageButtonStyle(skin.get(ButtonStyle.class));
        howStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.questionMark));
        howBtn = new ImageButton(howStyle);
        muteStyle = new ImageButtonStyle(skin.get(ButtonStyle.class));
        if(game.prefs.getBoolean("musicOn", true)){
            muteStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.musicOff));
        }else{
            muteStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.musicOn));
        }
        muteBtn = new ImageButton(muteStyle);
        muteBtn.addListener(new ClickListener(){
            @Override
            public void clicked(InputEvent event, float x, float y) {
                if(game.prefs.getBoolean("musicOn", true)){
                    game.prefs.putBoolean("musicOn", false);
                }else{
                    game.prefs.putBoolean("musicOn", true);
                }
                game.prefs.flush();
                update();
            }
        });
        this.add(muteBtn).minSize(Constants.MENU_BUTTON_TINY_HEIGHT, Constants.MENU_BUTTON_TINY_HEIGHT).pad(Constants.MENU_PADDING);
        this.add(howBtn).minSize(Constants.MENU_BUTTON_TINY_HEIGHT, Constants.MENU_BUTTON_TINY_HEIGHT).pad(Constants.MENU_PADDING);
        this.add(shareBtn).minSize(Constants.MENU_BUTTON_TINY_WIDTH, Constants.MENU_BUTTON_TINY_HEIGHT).pad(Constants.MENU_PADDING).expandX().align(Align.right);
    }

    public void update() {
        if(game.prefs.getBoolean("musicOn", true)){
            muteStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.musicOff));
            muteBtn.setStyle(muteStyle);
            AssetLoader.musicOn(AssetLoader.bgMusic);
        }else{
            muteStyle.imageUp = new TextureRegionDrawable(new TextureRegionDrawable(AssetLoader.musicOn));
            muteBtn.setStyle(muteStyle);
            AssetLoader.musicOff(AssetLoader.bgMusic);
        }
    }

    public void setColors(float r, float g, float b, float a) {
        shareBtn.setColor(r, g, b, a);
        howBtn.setColor(r, g, b, a);
        muteBtn.setColor(r, g, b, a);
    }

}