package fi.jukkaboyar.colorpong.game;

import com.badlogic.gdx.utils.Array;

import java.util.Arrays;

import fi.jukkaboyar.colorpong.Constants;


public class Player {

	private int id;
	private Paddle paddle;
	private Wall wall;
	private int[] ballsLeft;
	
	public Player(int id, int startBalls) {
		this.id = id;
		if(id == Constants.PLAYER_1){
			paddle = new Paddle(id, Constants.WIDTH/2- Constants.PADDLE_WIDTH/2, Constants.PADDLE_Y_MARGIN- Constants.PADDLE_HEIGHT/2);
			wall = new Wall(id, 0, Constants.PADDLE_Y_MARGIN- Constants.WALL_HEIGHT/2);
		}else if(id == Constants.PLAYER_2){
			paddle = new Paddle(id, Constants.WIDTH/2- Constants.PADDLE_WIDTH/2, Constants.HEIGHT- Constants.PADDLE_Y_MARGIN- Constants.PADDLE_HEIGHT/2);
			wall = new Wall(id, 0, Constants.HEIGHT- Constants.PADDLE_Y_MARGIN- Constants.WALL_HEIGHT/2);
		}
		ballsLeft = new int[Constants.BALL_COUNT];
		Arrays.fill(ballsLeft, startBalls);
	}
	
	public int getId() {
		return id;
	}
	
	public Paddle getPaddle() {
		return paddle;
	}
	
	public Wall getWall() {
		return wall;
	}
	
	public int[] getBallsLeft() {
		return ballsLeft;
	}
	
	public void subBall(int id){
		if(ballsLeft[id] > 0)
			ballsLeft[id]--;
	}
	
	public boolean noBallsLeft(){
		for(int value : ballsLeft){
			if(value > 0)
				return false;
		}
		return true;
	}
	
	public float aiMove(int diff, Array<Ball> balls) {
		float xValue = paddle.getX()+paddle.getWidth()/2;
		boolean allSticky = true;
		Ball closestBall = balls.get(0);
		for(Ball ball : balls){
			if(ball.getYdir() > 0 && !ball.isSticky()){
				allSticky = false;
				if(ball.getY() > closestBall.getY() && ball.getY() < paddle.getY()+ Constants.BALL_HEIGHT*2){
					closestBall = ball;
				}
			}
		}
		if(!allSticky){
			if((int)(paddle.getX()+paddle.getWidth()/2) < (int)(closestBall.getX()+closestBall.getWidth()/2)){
				int temp = (int)(closestBall.getX()+closestBall.getWidth()/2)-(int)(paddle.getX()+paddle.getWidth()/2);
				xValue += (temp < (diff+1)*2) ? temp : (diff+1)*2;
			}else if((int)(paddle.getX()+paddle.getWidth()/2) > (int)(closestBall.getX()+closestBall.getWidth()/2)){
				int temp = (int)(paddle.getX()+paddle.getWidth()/2)-(int)(closestBall.getX()+closestBall.getWidth()/2);
				xValue -= (temp < (diff+1)*2) ? temp : (diff+1)*2;
			}
		}
		return xValue;
	}
	
}
