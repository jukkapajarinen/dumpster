package fi.jukkaboyar.colorpong.gui;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.GlyphLayout;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.TimeUtils;

import java.util.ArrayList;

import fi.jukkaboyar.colorpong.AssetLoader;
import fi.jukkaboyar.colorpong.Colorpong;
import fi.jukkaboyar.colorpong.Constants;
import fi.jukkaboyar.colorpong.game.Ball;
import fi.jukkaboyar.colorpong.game.Item;
import fi.jukkaboyar.colorpong.game.Player;

public class GameScreen implements Screen{

	final Colorpong game;
	boolean itemsCheck;
	boolean musicOn;
	boolean gameOver;
	int mode, diff, startBalls, maxBalls;
	float speed;
	long lastBallTime, lastItemTime, lastItemUsedTime;
	Player p1, p2;
	Array<Ball> balls;
	Item item;
	Vector3 touchPos;
	
	public GameScreen(final Colorpong game) {
		this.game = game;
		gameOver = false;
		mode = game.prefs.getInteger("playMode", Constants.MODE_SINGLE);
		diff = game.prefs.getInteger("difficulty", Constants.DIFF_NORMAL);
		startBalls = game.prefs.getInteger("startBalls", Constants.START_BALLS);
		itemsCheck = game.prefs.getBoolean("itemsOn", true);
		musicOn = game.prefs.getBoolean("musicOn", true);
		maxBalls = 20 * (diff+1); // 20 | 40 | 60
		speed = Constants.SPEED_NORMAL;
		p1 = new Player(Constants.PLAYER_1, startBalls);
		p2 = new Player(Constants.PLAYER_2, startBalls);
		balls = new Array<Ball>();
		makeBall(true);
		if(itemsCheck){
			makeItem(true);
		}
		touchPos = new Vector3();
	}
	
	private void makeBall(boolean initTime) {
		if(initTime){
			lastBallTime = TimeUtils.nanoTime();
		}
		if(balls.size < maxBalls){
			int[] p1ballsLeft = p1.getBallsLeft();
			int[] p2ballsLeft = p2.getBallsLeft();
			ArrayList<Integer> ids = new ArrayList<Integer>();
			for(int i = 0; i < Constants.BALL_COUNT; i++){
				if(p1ballsLeft[i] > 0 || p2ballsLeft[i] > 0){
					ids.add(i);
				}
			}
			int r = game.rand.nextInt(ids.size());
			balls.add(new Ball(ids.get(r), 0, game.rand.nextBoolean() ? 1 : -1,
				game.rand.nextFloat()*(Constants.WIDTH- Constants.BALL_WIDTH-2* Constants.FG_MARGIN)+ Constants.FG_MARGIN,
				Constants.HEIGHT/2- Constants.BALL_HEIGHT/2));
		}
	}
	
	private void makeItem(boolean initTime) {
		if(itemsCheck){
			if(initTime){
				lastItemTime = TimeUtils.nanoTime();
			}
			ArrayList<Integer> possibleItems = new ArrayList<Integer>();
			possibleItems.add(Constants.ITEM_BIG_PADDLE);
			possibleItems.add(Constants.ITEM_SMALL_PADDLE);
			possibleItems.add(Constants.ITEM_FLASH);
			possibleItems.add(Constants.ITEM_EXTRA_BALLS);
			possibleItems.add(Constants.ITEM_SLOW_MO);
			possibleItems.add(Constants.ITEM_FAST_MO);
			possibleItems.add(Constants.ITEM_STICKY);
			possibleItems.add(Constants.ITEM_WALL);
			possibleItems.add(Constants.ITEM_TSUNAMI);
			int id = possibleItems.get(game.rand.nextInt(possibleItems.size()));
			item = new Item(id, game.rand.nextBoolean() ? 1 : -1,
				game.rand.nextFloat()*(Constants.WIDTH- Constants.ITEM_WIDTH-2* Constants.FG_MARGIN)+ Constants.FG_MARGIN,
				Constants.HEIGHT/2- Constants.ITEM_HEIGHT/2);
		}
	}
	
	private void checkCollision() {
		for(Ball ball : balls){
			if(ball.getX() <= 0){
				if(musicOn && !ball.isSticky())
					AssetLoader.playSound(AssetLoader.bounceSound);
				ball.setX(0);
				ball.setXdir(ball.getXdir()*-1);
			}
			if(ball.getX() >= Constants.WIDTH - ball.getWidth()){
				if(musicOn && !ball.isSticky())
					AssetLoader.playSound(AssetLoader.bounceSound);
				ball.setX(Constants.WIDTH - ball.getWidth());
				ball.setXdir(ball.getXdir()*-1);
			}
			if(ball.getY() <= 0 - ball.getHeight()){
				if(musicOn)
					AssetLoader.playSound(AssetLoader.goalSound);
				p1.subBall(ball.getId());
				balls.removeValue(ball, false);
				if(balls.size < 1){
					makeBall(true);
				}
				break;
			}
			if(ball.getY() >= Constants.HEIGHT){
				if(musicOn)
					AssetLoader.playSound(AssetLoader.goalSound);
				p2.subBall(ball.getId());
				balls.removeValue(ball, false);
				if(balls.size < 1){
					makeBall(true);
				}
				break;
			}
			
			if(ball.getBoundingRectangle().overlaps(p1.getPaddle().getBoundingRectangle())){
				if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_STICKY && item.getHolder() == Constants.PLAYER_1){
					if(musicOn)
						AssetLoader.playSound(AssetLoader.stickySound);
					ball.setY(p1.getPaddle().getY()+p1.getPaddle().getHeight());
					ball.sticky(true, p1.getPaddle(), ball.getX() - p1.getPaddle().getX());
					makeBall(true);
				}else{
					if(musicOn)
						AssetLoader.playSound(AssetLoader.bounceSound);
					ball.setY(p1.getPaddle().getY()+p1.getPaddle().getHeight());
					ball.setYdir(ball.getYdir()*-1);
					ball.setXdir((((ball.getX() < p1.getPaddle().getX() ? p1.getPaddle().getX() : ball.getX())-p1.getPaddle().getX())/p1.getPaddle().getWidth())*2-1);
				}
			}else if(ball.getBoundingRectangle().overlaps(p2.getPaddle().getBoundingRectangle())){
				if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_STICKY && item.getHolder() == Constants.PLAYER_2){
					if(musicOn)
						AssetLoader.playSound(AssetLoader.stickySound);
					ball.setY(p2.getPaddle().getY()-ball.getHeight());
					ball.sticky(true, p2.getPaddle(), ball.getX() - p2.getPaddle().getX());
					makeBall(true);
				}else{
					if(musicOn)
						AssetLoader.playSound(AssetLoader.bounceSound);
					ball.setY(p2.getPaddle().getY()-p2.getPaddle().getHeight());
					ball.setYdir(ball.getYdir()*-1);
					ball.setXdir((((ball.getX() < p2.getPaddle().getX() ? p2.getPaddle().getX() : ball.getX())-p2.getPaddle().getX())/p2.getPaddle().getWidth())*2-1);
				}
			}
			
			if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_WALL && item.getHolder() == Constants.PLAYER_1){
				if(ball.getBoundingRectangle().overlaps(p1.getWall().getBoundingRectangle())){
					if(musicOn)
						AssetLoader.playSound(AssetLoader.bounceSound);
					ball.setY(p1.getWall().getY()+p1.getWall().getHeight());
					ball.setYdir(ball.getYdir()*-1);
				}
			}else if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_WALL && item.getHolder() == Constants.PLAYER_2){
				if(ball.getBoundingRectangle().overlaps(p2.getWall().getBoundingRectangle())){
					if(musicOn)
						AssetLoader.playSound(AssetLoader.bounceSound);
					ball.setY(p2.getWall().getY()-ball.getHeight());
					ball.setYdir(ball.getYdir()*-1);
				}
			}
		}
		
		if(itemsCheck && !item.isUsed()){
			if(item.getBoundingRectangle().overlaps(p1.getPaddle().getBoundingRectangle())){
				if(musicOn)
					AssetLoader.playSound(AssetLoader.itemSound);
				item.setY(0 - Constants.ITEM_HEIGHT);
				useItem(p1);
			}else if(item.getBoundingRectangle().overlaps(p2.getPaddle().getBoundingRectangle())){
				if(musicOn)
					AssetLoader.playSound(AssetLoader.itemSound);
				item.setY(Constants.HEIGHT);
				useItem(p2);
			}
		}
	}
	
	private void useItem(Player player) {
		if(itemsCheck){
			item.setUsed(true);
			item.setHolder(player.getId());
			lastItemUsedTime = TimeUtils.nanoTime();
			switch (item.getId()) {
			case Constants.ITEM_BIG_PADDLE:
				item.setDuration(8000000000l);
				player.getPaddle().setSize(Constants.PADDLE_BIG_WIDTH, player.getPaddle().getHeight());
				player.getPaddle().setX(player.getPaddle().getX()-(Constants.PADDLE_BIG_WIDTH/2 - Constants.PADDLE_WIDTH/2));
				if(player.getPaddle().getX() > Constants.WIDTH - player.getPaddle().getWidth()){
					player.getPaddle().move(Constants.WIDTH - player.getPaddle().getWidth());
				}else if(player.getPaddle().getX() < 0){
					player.getPaddle().setX(0);
				}
				break;
			case Constants.ITEM_SMALL_PADDLE:
				item.setDuration(8000000000l);
				player.getPaddle().setSize(Constants.PADDLE_SMALL_WIDTH, player.getPaddle().getHeight());
				player.getPaddle().setX(player.getPaddle().getX()+(Constants.PADDLE_WIDTH/2 - Constants.PADDLE_SMALL_WIDTH/2));
				break;
			case Constants.ITEM_FLASH:
				item.setDuration(1000000000l);
				break;
			case Constants.ITEM_EXTRA_BALLS:
				item.setDuration(-1);
				for(int i = 0 ; i < 3 ; i++){
					makeBall(false);
				}
				break;
			case Constants.ITEM_SLOW_MO:
				item.setDuration(5000000000l);
				speed = Constants.SPEED_SLOW;
				break;
			case Constants.ITEM_FAST_MO:
				item.setDuration(5000000000l);
				speed = Constants.SPEED_FAST;
				break;
			case Constants.ITEM_STICKY:
				item.setDuration(5000000000l);
				break;
			case Constants.ITEM_WALL:
				item.setDuration(8000000000l);
				break;
			case Constants.ITEM_TSUNAMI:
				item.setDuration(-1);
				while(balls.size < 50){
					float startY = Constants.HEIGHT/2- Constants.BALL_HEIGHT/2 + (game.rand.nextFloat()*(Constants.PADDLE_Y_MARGIN*2)- Constants.PADDLE_Y_MARGIN);
					balls.add(new Ball(game.rand.nextInt(6),
						0,
						startY <= Constants.HEIGHT/2 ? -1 : 1,
						game.rand.nextFloat()*(Constants.WIDTH- Constants.BALL_WIDTH-2* Constants.FG_MARGIN)+ Constants.FG_MARGIN,
						startY));
				}
				break;
			}
		}
	}
	
	@Override
	public void render(float delta) {		
		if(!gameOver){
			if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_FLASH){
				Gdx.gl.glClearColor(game.rand.nextFloat(), game.rand.nextFloat(), game.rand.nextFloat(), 1f);
				Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
				game.cam.update();
				game.sb.setProjectionMatrix(game.cam.combined);
			}
		}
		game.cam.update();
		game.sb.setProjectionMatrix(game.cam.combined);
		game.sb.begin();		
		game.sb.draw(AssetLoader.dashLine, 0, Constants.HEIGHT/2- Constants.FG_STRIPE_HEIGHT/2, Constants.WIDTH, Constants.FG_STRIPE_HEIGHT);
		
		game.sb.draw(AssetLoader.hud1, Constants.WIDTH/2- Constants.HUD_WIDTH/2, Constants.HUD_Y_MARGIN- Constants.HUD_HEIGHT/2, Constants.HUD_WIDTH, Constants.HUD_HEIGHT);
		for(int i = 0 ; i < p1.getBallsLeft().length ; i++){
			AssetLoader.fontSmall.draw(game.sb, ""+p1.getBallsLeft()[i],
					Constants.WIDTH/2- Constants.HUD_WIDTH/2+(i*2* Constants.HUD_B_WIDTH)+ Constants.HUD_B_WIDTH/2-((""+p1.getBallsLeft()[i]).length()* AssetLoader.fontLarge.getSpaceWidth())/2,
					Constants.HUD_TEXT_Y_MARGIN+ AssetLoader.fontLarge.getLineHeight()/2);
		}
		if(mode == Constants.MODE_SINGLE){
			game.sb.draw(AssetLoader.hud1, Constants.WIDTH/2 - Constants.HUD_WIDTH/2, Constants.HEIGHT- Constants.HUD_Y_MARGIN- Constants.HUD_HEIGHT/2, Constants.HUD_WIDTH, Constants.HUD_HEIGHT);
			for(int i = 0 ; i < p2.getBallsLeft().length ; i++){
				AssetLoader.fontSmall.draw(game.sb, ""+p2.getBallsLeft()[i],
						Constants.WIDTH/2- Constants.HUD_WIDTH/2+(i*2* Constants.HUD_B_WIDTH)+ Constants.HUD_B_WIDTH/2-((""+p2.getBallsLeft()[i]).length()* AssetLoader.fontLarge.getSpaceWidth())/2,
						Constants.HEIGHT- Constants.HUD_TEXT_Y_MARGIN+ AssetLoader.fontLarge.getLineHeight()/2-6); //-6 pixels to make it right
			}
		}else if(mode == Constants.MODE_MULTI){
			game.sb.draw(AssetLoader.hud2, Constants.WIDTH/2 - Constants.HUD_WIDTH/2, Constants.HEIGHT- Constants.HUD_Y_MARGIN- Constants.HUD_HEIGHT/2, Constants.HUD_WIDTH, Constants.HUD_HEIGHT);
			AssetLoader.fontSmall.getData().setScale(-1);
			for(int i = 0 ; i < p2.getBallsLeft().length ; i++){
				AssetLoader.fontSmall.draw(game.sb, ""+p2.getBallsLeft()[i],
						Constants.WIDTH/2+ Constants.HUD_WIDTH/2-(i*2* Constants.HUD_B_WIDTH)- Constants.HUD_B_WIDTH/2+((""+p2.getBallsLeft()[i]).length()* AssetLoader.fontLarge.getSpaceWidth())/2,
						Constants.HEIGHT- Constants.HUD_TEXT_Y_MARGIN- AssetLoader.fontLarge.getLineHeight()/2);
			}
			AssetLoader.fontSmall.getData().setScale(1);
		}
		
		if(itemsCheck && item.isUsed()  && item.getId() == Constants.ITEM_WALL && item.getHolder() == Constants.PLAYER_1){
			game.sb.draw(p1.getWall(), p1.getWall().getX(), p1.getWall().getY(), p1.getWall().getWidth(), p1.getWall().getHeight());
		}
		if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_WALL && item.getHolder() == Constants.PLAYER_2){
			game.sb.draw(p2.getWall(), p2.getWall().getX(), p2.getWall().getY(), p2.getWall().getWidth(), p2.getWall().getHeight());
		}
		game.sb.draw(p1.getPaddle(), p1.getPaddle().getX(), p1.getPaddle().getY(), p1.getPaddle().getWidth(), p1.getPaddle().getHeight());
		game.sb.draw(p2.getPaddle(), p2.getPaddle().getX(), p2.getPaddle().getY(), p2.getPaddle().getWidth(), p2.getPaddle().getHeight());

		if(itemsCheck && !item.isUsed()){
			game.sb.draw(item, item.getX(), item.getY(), item.getWidth(), item.getHeight());
		}
		
		for(Ball ball : balls){
			game.sb.draw(ball, ball.getX(), ball.getY(), ball.getWidth(), ball.getHeight());
		}

		if(TimeUtils.nanoTime() - lastItemUsedTime < 1000000000l && itemsCheck){
			if(item.getHolder() == Constants.PLAYER_1){
				AssetLoader.fontLarge.draw(game.sb, item.getText(),
						Constants.WIDTH/2 - (new GlyphLayout(AssetLoader.fontLarge, item.getText())).width/2,
						Constants.TEXT_Y_MARGIN+(new GlyphLayout(AssetLoader.fontLarge, item.getText())).height/2);
			}else if(item.getHolder() == Constants.PLAYER_2){
				if(mode == Constants.MODE_SINGLE){
					AssetLoader.fontLarge.draw(game.sb, item.getText(),
							Constants.WIDTH/2 - (new GlyphLayout(AssetLoader.fontLarge, item.getText())).width/2,
							Constants.HEIGHT- Constants.TEXT_Y_MARGIN+(new GlyphLayout(AssetLoader.fontLarge, item.getText())).height/2);
				}else if(mode == Constants.MODE_MULTI){
					AssetLoader.fontLarge.getData().setScale(-1);
					AssetLoader.fontLarge.draw(game.sb, item.getText(),
							Constants.WIDTH/2 - (new GlyphLayout(AssetLoader.fontLarge, item.getText())).width/2,
							Constants.HEIGHT- Constants.TEXT_Y_MARGIN+(new GlyphLayout(AssetLoader.fontLarge, item.getText())).height/2);
					AssetLoader.fontLarge.getData().setScale(1);
				}
			}
		}
		game.sb.end();
		
		if(gameOver){
			game.setScreen(new HomeScreen(game));
		}
		
		if(!gameOver){
			if(p1.noBallsLeft() || p2.noBallsLeft()){
				gameOver = true;
			}
			if(Gdx.input.isKeyPressed(Keys.BACK) || Gdx.input.isKeyPressed(Keys.ESCAPE)){
				game.setScreen(new HomeScreen(game));
				return;
			}
			if(TimeUtils.nanoTime() - lastBallTime > 5000000000l){
				makeBall(true);
			}
			if(TimeUtils.nanoTime() - lastItemTime > 8000000000l && itemsCheck && !item.isUsed()){
				makeItem(true);
			}
			if(itemsCheck && item.isUsed()){
				if(item.getDuration() != -1 ? TimeUtils.nanoTime() - lastItemUsedTime > item.getDuration() : false){
					if(item.getId() == Constants.ITEM_BIG_PADDLE || item.getId() == Constants.ITEM_SMALL_PADDLE){
						if(item.getHolder() == Constants.PLAYER_1){
							p1.getPaddle().setSize(Constants.PADDLE_WIDTH, p1.getPaddle().getHeight());
							p1.getPaddle().setX((item.getId() == Constants.ITEM_BIG_PADDLE) ?
									p1.getPaddle().getX() + (Constants.PADDLE_BIG_WIDTH/2 - Constants.PADDLE_WIDTH/2) :
										p1.getPaddle().getX() - (Constants.PADDLE_WIDTH/2- Constants.PADDLE_SMALL_WIDTH/2));
							if(p1.getPaddle().getX() > Constants.WIDTH - p1.getPaddle().getWidth()){
								p1.getPaddle().move(Constants.WIDTH - p1.getPaddle().getWidth());
							}else if(p1.getPaddle().getX() < 0){
								p1.getPaddle().move(0);
							}
						}else if(item.getHolder() == Constants.PLAYER_2){
							p2.getPaddle().setSize(Constants.PADDLE_WIDTH, p2.getPaddle().getHeight());
							p2.getPaddle().setX((item.getId() == Constants.ITEM_BIG_PADDLE) ?
									p2.getPaddle().getX() + (Constants.PADDLE_BIG_WIDTH/2 - Constants.PADDLE_WIDTH/2) :
										p2.getPaddle().getX() - (Constants.PADDLE_WIDTH/2- Constants.PADDLE_SMALL_WIDTH/2));
							if(p2.getPaddle().getX() > Constants.WIDTH - p2.getPaddle().getWidth()){
								p2.getPaddle().move(Constants.WIDTH - p2.getPaddle().getWidth());
							}else if(p2.getPaddle().getX() < 0){
								p2.getPaddle().move(0);
							}
						}
					}else if(item.getId() == Constants.ITEM_SLOW_MO || item.getId() == Constants.ITEM_FAST_MO){
						speed = Constants.SPEED_NORMAL;
					}else if(item.getId() == Constants.ITEM_STICKY){
						for(Ball ball : balls){
							if(ball.isSticky()){
								ball.sticky(false, null, 0);
							}
						}
					}
					item.setUsed(false);
				}else if(item.getDuration() == -1){
					item.setUsed(false);
				}
			}
			for(int i = 0 ; i < 2 ; i++){
				if(Gdx.input.isTouched(i)) {
					touchPos.set(Gdx.input.getX(i), Gdx.input.getY(i), 0);
					game.cam.unproject(touchPos);
					if(touchPos.y <= Constants.HEIGHT/2){
						if(touchPos.x < p1.getPaddle().getWidth()/2){
							p1.getPaddle().move(0);
						}else if(touchPos.x > Constants.WIDTH-p1.getPaddle().getWidth()/2){
							p1.getPaddle().move(Constants.WIDTH-p1.getPaddle().getWidth());
						}else{
							p1.getPaddle().move(touchPos.x-p1.getPaddle().getWidth()/2);
						}
					}else if(touchPos.y > Constants.HEIGHT/2 && mode == Constants.MODE_MULTI){
						if(touchPos.x < p2.getPaddle().getWidth()/2){
							p2.getPaddle().move(0);
						}else if(touchPos.x > Constants.WIDTH-p2.getPaddle().getWidth()/2){
							p2.getPaddle().move(Constants.WIDTH-p2.getPaddle().getWidth());
						}else{
							p2.getPaddle().move(touchPos.x-p2.getPaddle().getWidth()/2);
						}
					}
				}
			}
			if(mode == Constants.MODE_SINGLE){
				float aiX = p2.aiMove(diff, balls);
				if(aiX < p2.getPaddle().getWidth()/2){
					p2.getPaddle().move(0);
				}else if(aiX > Constants.WIDTH-p2.getPaddle().getWidth()/2){
					p2.getPaddle().move(Constants.WIDTH-p2.getPaddle().getWidth());
				}else{
					p2.getPaddle().move(aiX-p2.getPaddle().getWidth()/2);
				}
			}
			if(itemsCheck && item.isUsed() && item.getId() == Constants.ITEM_STICKY){
				for(Ball ball : balls){
					if(ball.isSticky()){
						ball.setX(ball.getStickyPaddle().getX() + ball.getStickyPos());
					}
				}
			}
			for(Ball ball : balls){
				ball.move(speed);
			}
			if(itemsCheck){
				item.move(speed);
			}
			checkCollision();
		}
	}
	
	@Override
	public void resize(int width, int height) {}

	@Override
	public void show() {}

	@Override
	public void hide() {}

	@Override
	public void pause() {
		game.setScreen(new HomeScreen(game));
	}

	@Override
	public void resume() {}

	@Override
	public void dispose() {
		game.setScreen(new HomeScreen(game));
	}
	
}
