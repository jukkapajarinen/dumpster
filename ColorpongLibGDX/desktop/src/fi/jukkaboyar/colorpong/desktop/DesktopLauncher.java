package fi.jukkaboyar.colorpong.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import fi.jukkaboyar.colorpong.Colorpong;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.title = "Colorpong";
		config.useGL30 = false;
		config.width = 384;
		config.height = 640;
		new LwjglApplication(new Colorpong(), config);
	}
}
