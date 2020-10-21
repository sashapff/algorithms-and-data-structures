import java.io.*;
import java.util.*;

public class Interactive {
    String fileName = "";

    long ask(long k) throws IOException {
        out.println("? " + k);
        out.flush();
        return nextLong();
    }

    void print(long k) {
        out.println("! " + k);
        out.flush();
        System.exit(0);
    }

    public void solve() throws IOException {
        long x = nextLong();
        long m = nextLong();
        long n = (long) 1e18 - m;
        long first = ask(1);
        if (first == x) {
            print(1);
        }
        x = x - (first - 1);
        if (x <= 0) {
            x += (long) 1e18;
        }
        long l = Math.max(x - m - 1, 0);
        long r = Math.min(x + 1, n + 1);
        while (r - l > 1) {
            long mid = (l + r) / 2;
            long t = ask(mid);
            t -= first - 1;
            if (t <= 0) {
                t += (long) 1e18;
            }
            if (t == x) {
                print(mid);
            }
            if (t >= x) {
                r = mid;
            } else {
                l = mid;
            }
        }
        print(-1);
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
        new Interactive().run();
    }

}