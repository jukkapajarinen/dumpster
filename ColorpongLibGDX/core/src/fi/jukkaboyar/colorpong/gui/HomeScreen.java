package fi.jukkaboyar.colorpong.gui;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.utils.Align;
import com.badlogic.gdx.utils.viewport.StretchViewport;

import fi.jukkaboyar.colorpong.Colorpong;
import fi.jukkaboyar.colorpong.Constants;

public class HomeScreen implements Screen{

    final Colorpong game;
    Stage stage;
    Skin skin;
    Label logo;
    TextButton singleBtn, multiBtn, settBtn, removeAdsBtn, exitBtn;
    Table mainTable, btnTable;
    TopBar topBar;

    public HomeScreen(final Colorpong game) {
        this.game = game;

        stage = new Stage(new StretchViewport(Constants.WIDTH, Constants.HEIGHT));
        Gdx.input.setInputProcessor(stage);
        skin = new Skin(Gdx.files.internal("packs/uiskin.json"), new TextureAtlas("packs/uiskin.pack"));
        logo = new Label("Colorpong", skin);
        singleBtn = new TextButton(Constants.STR_MAIN_SINGLE, skin);
        singleBtn.addListener(new ClickListener(){
            @Override
            public void clicked(InputEvent event, float x, float y) {
                game.prefs.putInteger("playMode", Constants.MODE_SINGLE);
                game.prefs.flush();
                game.setScreen(new GameScreen(game));
            }
        });
        multiBtn = new TextButton(Constants.STR_MAIN_MULTI, skin);
        multiBtn.addListener(new ClickListener(){
            @Override
            public void clicked(InputEvent event, float x, float y) {
                game.prefs.putInteger("playMode", Constants.MODE_MULTI);
                game.prefs.flush();
                game.setScreen(new GameScreen(game));
            }
        });
        settBtn = new TextButton("More Games", skin);
        removeAdsBtn = new TextButton("Remove Ads", skin);
        exitBtn = new TextButton(Constants.STR_MAIN_EXIT, skin);
        exitBtn.addListener(new ClickListener(){
            @Override
            public void clicked(InputEvent event, float x, float y) {
                Gdx.app.exit();
            }
        });
        mainTable = new Table();
        mainTable.setSize(Constants.MENU_WIDTH, Constants.MENU_HEIGHT);
        mainTable.setPosition(Constants.MENU_POS_X, Constants.MENU_POS_Y);
        mainTable.pad(Constants.FG_MARGIN);
        mainTable.align(Align.top);
        mainTable.add(logo).minSize(Constants.MENU_LOGO_WIDTH, Constants.MENU_LOGO_HEIGHT);
        mainTable.row();
        btnTable = new Table();
        btnTable.add(singleBtn).minSize(Constants.MENU_BUTTON_WIDTH, Constants.MENU_BUTTON_HEIGHT).pad(Constants.MENU_PADDING);
        btnTable.row();
        btnTable.add(multiBtn).minSize(Constants.MENU_BUTTON_WIDTH, Constants.MENU_BUTTON_HEIGHT).pad(Constants.MENU_PADDING);
        btnTable.row();
        btnTable.add(settBtn).minSize(Constants.MENU_BUTTON_WIDTH, Constants.MENU_BUTTON_HEIGHT).pad(Constants.MENU_PADDING);
        btnTable.row();
        btnTable.add(removeAdsBtn).minSize(Constants.MENU_BUTTON_WIDTH, Constants.MENU_BUTTON_HEIGHT).pad(Constants.MENU_PADDING);
        mainTable.add(btnTable).expandY();
        mainTable.row();
        mainTable.add(exitBtn).minSize(Constants.MENU_BUTTON_SMALL_WIDTH, Constants.MENU_BUTTON_SMALL_HEIGHT);
        topBar = new TopBar(game, Constants.SCREEN_MENU);
        stage.addActor(mainTable);
        stage.addActor(topBar);
    }

    @Override
    public void render(float delta) {
        singleBtn.setColor(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        multiBtn.setColor(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        settBtn.setColor(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        removeAdsBtn.setColor(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        exitBtn.setColor(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        topBar.setColors(game.fgColor[0], game.fgColor[1], game.fgColor[2], 1);
        game.sb.begin();
        stage.draw();
        game.sb.end();

        if(Gdx.input.isKeyPressed(Keys.BACK) || Gdx.input.isKeyPressed(Keys.ESCAPE)){
            Gdx.app.exit();
        }
    }

    @Override
    public void resize(int width, int height) {}

    @Override
    public void show() {}

    @Override
    public void hide() {}

    @Override
    public void pause() {}

    @Override
    public void resume() {}

    @Override
    public void dispose() {
        stage.dispose();
        skin.dispose();
    }

}