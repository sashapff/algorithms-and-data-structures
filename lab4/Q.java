import java.io.*;
import java.math.BigInteger;
import java.util.Locale;
import java.util.StringTokenizer;

public class Q {
    String fileName = "nice3";
    BigInteger n;
    int m, mod;
    long[][] dp;
    int sz;

    public void solve() throws IOException {
        n = new BigInteger(nextToken());
        m = nextInt();
        mod = nextInt();
        sz = (1 << m);
        if (n.equals(BigInteger.ONE)) {
            out.println(sz % mod);
        } else {
            long[][] a = new long[sz][1];
            dp = new long[sz][sz];
            for (int i = 0; i < sz; i++) {
                a[i][0] = 1;
            }
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    dp[i][j] = check(i, j);
                }
            }
            long s = 0;
            long[][] ans = pow(dp, n.subtract(BigInteger.valueOf(1)));
            for (int i = 0; i < (int) ans.length; i++) {
                for (int j = 0; j < ans[i].length; j++) {
                    s += ans[i][j];
                    s %= mod;
                }
            }
            out.println(s);
        }
    }

    int check(int a, int b) {
        for (int i = 1; i < m; i++) {
            if ((a & (1 << i)) != 0 && (a & (1 << (i - 1))) != 0 && (b & (1 << i)) != 0 && (b & (1 << (i - 1))) != 0) {
                return 0;
            }
            if ((a & (1 << i)) == 0 && (a & (1 << (i - 1))) == 0 && (b & (1 << i)) == 0 && (b & (1 << (i - 1))) == 0) {
                return 0;
            }
        }
        return 1;
    }

    long[][] mul(long[][] a, long[][] b) {
        long[][] c = new long[a.length][b[0].length];
        for (int i = 0; i < (int) a.length; i++) {
            for (int j = 0; j < (int) a[0].length; j++) {
                for (int k = 0; k < (int) b[0].length; k++) {
                    c[i][k] += a[i][j] * b[j][k];
                    c[i][k] %= mod;
                }
            }
        }
        return c;
    }

    long[][] pow(long[][] a, BigInteger n) {
        if (n.compareTo(BigInteger.ONE) == 0) {
            return a;
        }
        long[][] cur = pow(a, n.divide(BigInteger.valueOf(2)));
        if (n.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ZERO) == 0) {
            return mul(cur, cur);
        }
        return mul(mul(cur, cur), a);
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
        new Q().run();
    }

}