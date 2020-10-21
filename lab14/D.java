import java.io.*;
import java.math.BigInteger;
import java.util.Locale;
import java.util.Random;
import java.util.StringTokenizer;

public class B {
    String fileName = "";

    BigInteger mod;
    BigInteger mod1;
    BigInteger two = BigInteger.valueOf(2);
    BigInteger one = BigInteger.valueOf(1);
    BigInteger zero = BigInteger.valueOf(0);

    boolean check(long n, long x, long s, int k) {
        BigInteger y = BigInteger.valueOf(x);
        y = y.modPow(BigInteger.valueOf(s), mod);
        for (int j = 0; j < k; j++) {
            BigInteger yy = y;
            yy = yy.modPow(two, mod);
            if (yy.equals(one)) {
                if (!y.equals(mod1) && !y.equals(one)) {
                    return false;
                }
                break;
            }
            y = yy;
        }
        return (y.equals(mod1) || y.equals(one));
    }

    private Random random = new Random(1000007 * 239);

    boolean test(long n, int t) {
        if (n == 1) {
            return false;
        }
        long s = n - 1;
        int k = 0;
        while (s % 2 == 0) {
            s /= 2;
            k++;
        }
        for (int i = 0; i < t; i++) {
            long x = (Math.abs(random.nextLong())% (n - 3)) + 2;
            if (!check(n, x, s, k)) {
                return false;
            }
        }
        return true;
    }

    public void solve() throws IOException {
        long n = nextInt();
        for (int i = 0; i < n; i++) {
            long x = nextLong();
            mod = BigInteger.valueOf(x);
            mod1 = BigInteger.valueOf(x - 1);
            out.println((x == 2 || x == 3 || test(x, 100)) ? "YES" : "NO");
        }
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
        new B().run();
    }

}