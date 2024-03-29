import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.StringTokenizer;

public class Tratata {
    private BufferedReader in;
    @SuppressWarnings("StandardVariableNames")
    private StringTokenizer str;
    @SuppressWarnings("FieldCanBeLocal")
    private PrintWriter out;
    @SuppressWarnings({"FieldCanBeLocal", "NonConstantFieldWithUpperCaseName"})
    private String SK;

    String next() throws IOException {
        while ((str == null) || !str.hasMoreTokens()) {
            SK = in.readLine();
            if (SK == null) {
                return null;
            }
            str = new StringTokenizer(SK);
        }
        return str.nextToken();
    }

    long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    @SuppressWarnings({"ComparableImplementedButEqualsNotOverridden", "NonStaticInnerClassInSecureContext"})
    private class Point1 implements Comparable<Point1> {
        @SuppressWarnings("UnusedDeclaration")
        private final int x;
        private final int y;

        private Point1(int x1, int y1) {
            x = x1;
            y = y1;
        }

        @SuppressWarnings({"CompareToUsesNonFinalVariable", "SubtractionInCompareTo"})
        @Override
        public int compareTo(Point1 o) {
            return y - o.y;
        }

    }
    
    @SuppressWarnings({"ComparableImplementedButEqualsNotOverridden", "NonStaticInnerClassInSecureContext"})
    public class Point implements Comparable<Point> {
        private int x;
        private int y;

        public Point(int x1, int y1) {
            x = x1;
            y = y1;
        }

        @SuppressWarnings({"CompareToUsesNonFinalVariable", "SubtractionInCompareTo"})
        @Override
        public int compareTo(Point o) {
            return x - o.x;
        }

    }

    private int res;

    @SuppressWarnings({"OverlyComplexMethod", "OverlyLongMethod", "AccessingNonPublicFieldOfAnotherObject"})
    private void solvcn(int lx, int ly, int rx, int ry, Point[] x) {
        if ((lx > rx) || (ly > ry)) {
            return;
        }
        if (x.length == 0) {
            return;
        }
        if ((lx == rx) || (ly == ry)) {
            res += x.length;
            return;
        }
        int n = x.length;
        int midx = (lx + rx) / 2;
        int t1x = 0;
        int t2x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x < midx) {
                t1x++;
            }
            if (x[i].x > midx) {
                t2x++;
            }

        }
        @SuppressWarnings("CStyleArrayDeclaration") int zany[] = new int[ry - ly + 1];
        for (int i = 0; i < n; i++) {
            zany[x[i].y - ly] = 1;
        }
        for (int i = 0; i < ry - ly + 1; i++) {
            res += zany[i];
        }
        @SuppressWarnings("CStyleArrayDeclaration") Point a[] = new Point[t1x];
        t1x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x < midx) {
                a[t1x] = x[i];
                t1x++;
            }
        }
        solvcn(lx, ly, midx - 1, ry, a);

        a = new Point[t2x];
        t2x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x > midx) {
                a[t2x] = x[i];
                t2x++;
            }
        }
        solvcn(midx + 1, ly, rx, ry, a);
    }

    @SuppressWarnings("CStyleArrayDeclaration")
    private int resx[];

    @SuppressWarnings("CStyleArrayDeclaration")
    private int resy[];
    
    public static void main(String[] args) throws IOException {
        new Tratata().run();
    }

    @SuppressWarnings({"OverlyLongMethod", "AccessingNonPublicFieldOfAnotherObject"})
    void solve() throws IOException {
        int n = nextInt();
        resx = new int[n];
        resy = new int[n];
        Point[] x = new Point[n];
        Point1[] y = new Point1[n];
        for (int i = 0; i < n; i++) {
            x[i] = new Point(nextInt(), nextInt());
            y[i] = new Point1(x[i].x, x[i].y);
        }
        HashMap<Integer, Integer> ab = new HashMap<>();
        Arrays.sort(x);
        Arrays.sort(y);
        int tx = 0;
        int ty = 0;
        int last = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            if (x[i].x != last) {
                resx[tx] = x[i].x;
                tx++;
                last = x[i].x;
            }
            x[i].x = tx - 1;
        }
        last = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            if (y[i].y != last) {
                resy[ty] = y[i].y;
                ty++;
                last = y[i].y;
                ab.put(y[i].y, ty - 1);
            }
        }
        for (int i = 0; i < n; i++) {
            x[i].y = ab.get(x[i].y);
        }
        solvcn(0, 0, tx, ty, x);
        System.out.println(res);
        solvout(0, 0, tx, ty, x);
    }

    void run() throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        solve();
        out.close();
    }

    @SuppressWarnings({"OverlyComplexMethod", "OverlyLongMethod", "AccessingNonPublicFieldOfAnotherObject", "CStyleArrayDeclaration"})
    void solvout(int lx, int ly, int rx, int ry, Point[] x) {
        if ((lx > rx) || (ly > ry)) {
            return;
        }
        if (x.length == 0) {
            return;
        }
        if ((lx == rx) || (ly == ry)) {
            for (int i = 0; i < x.length; i++) {
                System.out.println(resx[x[i].x] + " " + resy[x[i].y]);
            }
            return;
        }
        int n = x.length;
        int midx = (lx + rx) / 2;
        int t1x = 0;
        int t2x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x < midx) {
                t1x++;
            }
            if (x[i].x > midx) {
                t2x++;
            }

        }
        int zany[] = new int[ry - ly + 1];
        for (int i = 0; i < n; i++) {
            zany[x[i].y - ly] = 1;
        }
        for (int i = 0; i < ry - ly + 1; i++) {
            if (zany[i] == 1) {
                System.out.println(resx[midx] + " " + resy[i + ly]);
            }
        }
        Point a[] = new Point[t1x];
        t1x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x < midx) {
                a[t1x] = x[i];
                t1x++;
            }
        }
        solvout(lx, ly, midx - 1, ry, a);

        a = new Point[t2x];
        t2x = 0;
        for (int i = 0; i < n; i++) {
            if (x[i].x > midx) {
                a[t2x] = x[i];
                t2x++;
            }
        }
        solvout(midx + 1, ly, rx, ry, a);
    }
}
