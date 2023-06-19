import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;

public class Main {
    public static void main(String[] args) throws Exception {
        JFrame frame = new JFrame("");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(360, 180);
        JPanel jrp = new JPanel();
        jrp.setVisible(true);
        JPanel jfp = new JPanel();
        jfp.setVisible(true);
        JTextPane label = new JTextPane();
        label.setVisible(true);
        label.setSize(150,50);
        label.setMargin(new Insets(0,0,0,0));
        label.setBackground(new Color(0xEEEEEE));
        label.setFont(new Font("Consolas",0,20));
        jfp.add(label);
        frame.getContentPane().add(jrp);
        frame.getContentPane().add(jfp, BorderLayout.EAST);
        frame.setVisible(true);
        while (true) {
            Point p = MouseInfo.getPointerInfo().getLocation();
            Robot r = new Robot();
            Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
            Rectangle screenRectangle = new Rectangle(screenSize);
            BufferedImage bfi = r.createScreenCapture(screenRectangle);
            Color color = new Color(bfi.getRGB(p.x, p.y));
            jrp.setBackground(color);
            label.setText("#" + (Integer.toHexString(color.getRed()) + Integer.toHexString(color.getGreen()) + Integer.toHexString(color.getBlue())).toUpperCase());
            Thread.sleep(10);
        }
    }
}