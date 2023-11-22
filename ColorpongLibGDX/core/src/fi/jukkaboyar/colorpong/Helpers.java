package fi.jukkaboyar.colorpong;

public class Helpers {

    public static float[] HSBtoRGB(float hue, float sat, float bri){
        float[] rgb = {0, 0, 0};
        hue = (hue-(float)Math.floor(hue))*360;
        if(sat == 0){
            rgb[0] = rgb[1] = rgb[2] = bri;
        }else{
            float c = bri * sat;
            float hi = hue/60;
            float x = c*(1-Math.abs(hi%2-1));
            if(0 <= hi && hi < 1){
                rgb[0] = c+bri-c;
                rgb[1] = x+bri-c;
                rgb[2] = 0+bri-c;
            }else if(1 <= hi && hi < 2){
                rgb[0] = x+bri-c;
                rgb[1] = c+bri-c;
                rgb[2] = 0+bri-c;
            }else if(2 <= hi && hi < 3){
                rgb[0] = 0+bri-c;
                rgb[1] = c+bri-c;
                rgb[2] = x+bri-c;
            }else if(3 <= hi && hi < 4){
                rgb[0] = 0+bri-c;
                rgb[1] = x+bri-c;
                rgb[2] = c+bri-c;
            }else if(4 <= hi && hi < 5){
                rgb[0] = x+bri-c;
                rgb[1] = 0+bri-c;
                rgb[2] = c+bri-c;
            }else if(5 <= hi && hi < 6){
                rgb[0] = c+bri-c;
                rgb[1] = 0+bri-c;
                rgb[2] = x+bri-c;
            }
        }
        return rgb;
    }
}
