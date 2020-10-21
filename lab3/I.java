import java.io.*;
import java.util.Locale;
import java.util.StringTokenizer;

public class I {
    String fileName = "";

    public void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        if (n == 1) {
            for (int i = 0; i < m; i++) {
                out.println("0 1 1");
            }
        }
        if (n == 2) {
            out.println("1 1 2");
            for (int i = 0; i < m - 1; i++) {
                out.println("0 1 2");
            }
        }
        if (n == 3) {
            if (m == 1) {
                out.println("0 1 2");
            } else if (m == 2) {
                out.println("1 1 2");
                out.println("0 1 2");
            } else {
                out.println("1 1 2");
                out.println("1 1 3");
                for (int i = 0; i < m - 2; i++) {
                    out.println("0 " + ((i % 3) + 1) + " " + (((i + 1) % 3) + 1));
                }
            }
        }
        if (n >= 4) {
            if (m == 1) {
                out.println("0 1 2");
            } else if (m == 2) {
                out.println("1 1 2");
                out.println("0 1 2");
            } else if (m == 3) {
                out.println("1 1 2");
                out.println("0 1 2");
                out.println("0 2 3");
            } else {
                out.println("1 3 1");
                out.println("1 3 2");
                int cnt = 4;
                int tmp = 2;
                while (cnt <= n && tmp < m) {
                    out.println("1 " + cnt + " " + (cnt - 1));
                    tmp++;
                    for (int i = 1; i < (cnt - 2) && tmp < m; i += 2) {
                        out.println("0 " + (i) + " " + (i + 1));
                        tmp++;
                    }
                    cnt++;
                }
                for (int i = 0; i < m - tmp; i++) {
                    out.println("0 " + ((i % n) + 1) + " " + (((i + n) % 3) + 1));
                }
            }
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
        new I().run();
    }

}