import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.util.Random;

public class PictureForm {
    private JPanel mainPanel;
    private JSpinner Diam;
    private JSpinner anglesNum;
    private CanvasPanel canvasPanel;

    private final static int X = 100;
    private final static int Y = 100;

    private void createUIComponents() {
        canvasPanel = new CanvasPanel();
    }

    public static class CanvasPanel extends JPanel{
        private int angles = 3;
        private int diam = 10;

        public void setAngles(int a){
            angles = a;
            repaint();
        }

        public void setDiam(int d) {
            diam = d;
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int n = angles;
            int[] x = new int [n];//координаты точек
            int[] y = new int [n];//
            int i = 0;

            //цикл создающий массив из точек
            while(i < n){
                x[i] = X + (int)((diam / 2)*Math.cos(2*Math.PI * i / n));
                y[i] = Y + (int)((diam / 2)*Math.sin(2*Math.PI * i / n));
                i++;
            }

            int j = n - 1;		//цикл передающий координаты для прорисовки грани
            while(j >= 0){
                if(j > 0){
                    g.drawLine(x[j], y[j],  x[j - 1], y[j - 1]);
                } else {
                    g.drawLine(x[j], y[j], x[n - 1], y[n - 1]);
                }
                j--;
            }

            for (int k = 0; k < n - 1; k++) {
                Random rand = new Random();
                float r = rand.nextFloat();
                float gg = rand.nextFloat();
                float b = rand.nextFloat();
                g.setColor(new Color(r, gg, b));
                g.drawPolygon(new int[]{X, x[k], x[k + 1]}, new int[]{Y, y[k],y[k + 1]}, 3);
                g.fillPolygon(new int[]{X, x[k], x[k + 1]}, new int[]{Y, y[k],y[k + 1]}, 3);
            }
            Random rand = new Random();
            float r = rand.nextFloat();
            float gg = rand.nextFloat();
            float b = rand.nextFloat();
            g.setColor(new Color(r, gg, b));
            g.drawPolygon(new int[]{X, x[n-1], x[0]}, new int[]{Y, y[n-1],y[0]}, 3);
            g.fillPolygon(new int[]{X, x[n-1], x[0]}, new int[]{Y, y[n-1],y[0]}, 3);
        }
    }

    public PictureForm(){
        anglesNum.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int angles = (Integer)anglesNum.getValue();
                canvasPanel.setAngles(angles);
            }
        });
        anglesNum.setValue(3);

        Diam.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int diam = (Integer)Diam.getValue();
                canvasPanel.setDiam(diam);
            }
        });
        Diam.setValue(130);
    }



    public static void main(String[] args) {
        JFrame frame = new JFrame("Рисульки");
        frame.setSize(500, 500);
        frame.setContentPane(new PictureForm().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
