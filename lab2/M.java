import java.io.*;
import java.util.*;

public class M {
    String fileName = "";

    class Pair {
        int first, second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    ArrayList<Pair>[] a;
    int[] s;

    boolean check() {
        for(int i = 0; i < a.length; i++) {
            for (Pair p : a[i]) {
                int x = s[p.first];
                int y = s[p.second];
                s[p.first] = Math.min(x, y);
                s[p.second] = Math.max(x, y);
            }
        }
        for (int i = 1; i < s.length; i++) {
            if (s[i] < s[i - 1]) {
                return false;
            }
        }
        return true;
    }

    public void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        int k = nextInt();
        a = new ArrayList[k];
        for (int i = 0; i < k; i++) {
            int r = nextInt();
            a[i] = new ArrayList<>();
            for (int j = 0; j < r; j++) {
                int x = nextInt() - 1;
                int y = nextInt() - 1;
                a[i].add(new Pair(Math.min(x, y), Math.max(x, y)));
            }
        }
        s = new int[n];
        boolean flag = true;
        for (int i = 0; i < (1 << n); i++) {
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) > 0) {
                    s[j] = 1;
                } else {
                    s[j] = 0;
                }
            }
            flag = flag & check();
        }
        if (flag) {
            out.println("Yes");
        } else {
            out.println("No");
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
        new M().run();
    }

}