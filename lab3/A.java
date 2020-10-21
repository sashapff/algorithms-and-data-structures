import java.io.*;
import java.util.*;

public class IsHeap {
    String fileName = "";

    public void solve() throws IOException {
        int n = nextInt();
        int[] a = new int[n + 1];
        boolean flag = true;
        a[0] = -Integer.MAX_VALUE;
        for (int i = 1; i <= n; i++) {
            a[i] = nextInt();
            if (a[i] < a[i / 2]) {
                flag = false;
            }
        }
        if (flag) {
            out.println("YES");
        } else {
            out.println("NO");
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
        new IsHeap().run();
    }

}