import java.io.*;
import java.util.*;

public class D {
    String fileName = "garland";

    double[] a;
    int n;

    boolean check(double x) {
        a[1] = x;
        if (a[1] < 1e-12) {
            return false;
        }
        for (int i = 2; i < n; i++) {
            a[i] = 2 * a[i - 1] - a[i - 2] + 2;
            if (a[i] < 1e-12) {
                return false;
            }
        }
        return true;
    }

    public void solve() throws IOException {
        n = nextInt();
        a = new double[n];
        a[0] = nextDouble();
        double l = 0;
        double r = 10000;
        while (r - l > 1e-12) {
            double m = (l + r) / 2;
            if (check(m)) {
                r = m;
            } else {
                l = m;
            }
        }
        out.println(a[n - 1]);
    }

    public void run() {
        try {
            if ("".equals(fileName)) {
                br = new BufferedReader(new InputStreamReader(System.in));
                out = new PrintWriter(System.out);
            } else {
                br = new BufferedReader(new FileReader(fileName + ".in"));
                out = new PrintWriter(fileName + ".out");
            }
            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        new D().run();
    }

}